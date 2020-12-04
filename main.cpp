// Headers
#include <vector>
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include "Display.h"
#include "ShaderProgram.h"
#include "math_utils.h"

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    Display disp {"OpenGL Playground",1280,720};
    
    
    glewExperimental = GL_TRUE;
    glewInit();

    // Create Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLfloat vertices[] = {
        //  Position      Color             Texcoords
        -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // Top-right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f // Bottom-left
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create an element array
    GLuint ebo;
    glGenBuffers(1, &ebo);

    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0};

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    ShaderProgram sp;
    
    // Create and compile the vertex shader
    sp.loadShader("./shaders/vertex.glsl",GL_VERTEX_SHADER);
    
    // Create and compile the fragment shader
    sp.loadShader("./shaders/fragment.glsl",GL_FRAGMENT_SHADER);
    
    // Link the vertex and fragment shader into a shader program
    sp.linkProgram();
    glBindFragDataLocation(sp.getProgramID(), 0, "outColor");
    glLinkProgram(sp.getProgramID());
    glUseProgram(sp.getProgramID());

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(sp.getProgramID(), "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);

    GLint colAttrib = glGetAttribLocation(sp.getProgramID(), "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));

    GLint texAttrib = glGetAttribLocation(sp.getProgramID(), "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *)(5 * sizeof(GLfloat)));

    auto uniTransform = glGetUniformLocation(sp.getProgramID(), "transform");
    math_utils::mat4 rotation = math_utils::rotate(1.0f, 0.0f, 0.0f, 0.0f);
	math_utils::mat4 scaling = math_utils::scale(disp.getRatio(), 1.0f, 1.0f);
	math_utils::mat4 translation = math_utils::translate(0.0f, 0.0f, 0.0f);
	math_utils::mat4 global_transform = translation.product(scaling.product(rotation));

    // Load texture
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    int width, height;
    SDL_Surface *tmp = IMG_Load("fish.png");
    int Mode = GL_RGB;

    if (tmp->format->BytesPerPixel == 4)
    {
        Mode = GL_RGBA;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, Mode, tmp->w, tmp->h, 0, Mode, GL_UNSIGNED_BYTE, tmp->pixels);
    SDL_FreeSurface(tmp);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    bool running = true;
    SDL_Event windowEvent;
    uint64_t lastTime = 0;
    float obX = 0.0f;
	float obY = 0.0f;
    float sc = 1.0f;
    while (running)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
                break;
        }
        	auto keys = SDL_GetKeyboardState(NULL);
		if (keys[SDL_SCANCODE_DOWN])
		{
			obY -= 0.05f;
		}
		if (keys[SDL_SCANCODE_UP])
		{
			obY += 0.05f;
		}
		if (keys[SDL_SCANCODE_RIGHT])
		{
			obX += 0.05f;
		}
		if (keys[SDL_SCANCODE_LEFT])
		{
			obX -= 0.05f;
		}
		if (keys[SDL_SCANCODE_ESCAPE])
		{
			break;
		}
        if(keys[SDL_SCANCODE_E]&& sc<10){
            sc += 0.2f;
        }
        if(keys[SDL_SCANCODE_D] && sc>0){
            sc -= 0.2f;
        }
        // Clear the screen to black
        disp.clear(0.0f,0.0f,0.0f,0.0f);

        //Set transformation matrix
        translation = math_utils::translate(obX, obY, 0.0f);
        rotation = math_utils::rotate(0.0f, 0.0f, 1.0f, 0.002f * lastTime);
        scaling = math_utils::scale(sc*disp.getRatio(), sc, 1.0f);
		global_transform = translation.product(rotation.product(scaling));
        glUniformMatrix4fv(uniTransform, 1, GL_FALSE, global_transform.getm());
        
        // Draw a rectangle from the 2 triangles using 6 indices
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap buffers
        disp.update();
        //Control frame rate
        auto dt = (SDL_GetTicks() - lastTime);
		if (dt < 16)
		{
			SDL_Delay(16 - dt);
		}

		lastTime = SDL_GetTicks();
    }

    glDeleteTextures(1, &tex);

  
    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);

    glDeleteVertexArrays(1, &vao);

    
    SDL_Quit();

    return 0;
}
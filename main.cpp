// Headers
#include <vector>
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include "Display.h"
#include "ShaderProgram.h"
#include "math_utils.h"
#include "model2D.h"

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    Display disp {"OpenGL Playground",1280,720};
    
    
    glewExperimental = GL_TRUE;
    glewInit();



    GLfloat vertices[] = {
        //  Position      Color             Texcoords
        -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,     0.0f, 0.0f, // Top-left
         0.5f,  0.5f,  0.0f, 1.0f, 0.0f,     1.0f, 0.0f,  // Top-right
         0.5f, -0.5f,  0.0f, 0.0f, 1.0f,     1.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,     0.0f, 1.0f // Bottom-left
    };

    math_utils::mat4 rotation = math_utils::rotateZ(0.0f);
	math_utils::mat4 scaling = math_utils::scale(disp.getRatio(), 1.0f, 1.0f);
	math_utils::mat4 translation = math_utils::translate(0.0f, 0.0f, 0.0f);
	math_utils::mat4 global_transform = translation.product(rotation.product(scaling));


    int width, height;
    SDL_Surface *tmp = IMG_Load("fish.png");
    int Mode = GL_RGB;

    if (tmp->format->BytesPerPixel == 4)
    {
        Mode = GL_RGBA;
    }
    
    auto m2d = Model2D(vertices,tmp);

    SDL_FreeSurface(tmp);
    bool running = true;
    SDL_Event windowEvent;
    uint64_t lastTime = 0;
    float obX = 0.0f;
	float obY = 0.0f;
    float sc = 1.0f;
    float ang = 0.0f;
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
        if(keys[SDL_SCANCODE_E]&& sc<5.0f){
            sc += 0.1f;
        }
        if(keys[SDL_SCANCODE_D] && sc>0.4f){
            sc -= 0.1f;
        }
        if(keys[SDL_SCANCODE_R]){
            ang += 0.01f;
        }
        if(keys[SDL_SCANCODE_F]){
            ang -= 0.01f;
        }
        
        // Clear the screen to black
        disp.clear(0.0f,0.0f,0.0f,0.0f);

        //Set transformation matrix
        translation = math_utils::translate(obX, obY, 0.0f);
        
        rotation = math_utils::rotateZ(ang);
        
        scaling = math_utils::scale(sc*disp.getRatio(), sc, 1.0f);
		global_transform = translation.product(rotation.product(scaling));
        m2d.setTransform(global_transform);
        
        
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


    
    SDL_Quit();

    return 0;
}
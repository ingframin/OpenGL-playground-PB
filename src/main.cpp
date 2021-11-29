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
#include "Vertex.h"

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    Display disp {"OpenGL Playground",1280,720};
    
    auto vertices_v = std::vector<Vertex>();
    vertices_v.push_back({-0.5f, 0.5f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f});
    vertices_v.push_back({ 0.5f, 0.5f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f});
    vertices_v.push_back({ 0.5f, -0.5f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f});
    vertices_v.push_back({-0.5f, -0.5f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f});

    GLfloat vertices[] = {
        //  Position      Color             Texcoords
        -0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,0.0f, 0.0f, // Top-left
         0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f,1.0f, 0.0f,  // Top-right
         0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.0f,1.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f,0.0f, 1.0f // Bottom-left
    };

    math_utils::mat4 rotation = math_utils::rotateZ(0.0f);
	math_utils::mat4 scaling = math_utils::scale(1.0f, 1.0f, 1.0f);
	math_utils::mat4 translation = math_utils::translate(0.0f, 0.0f, -1.0f);
    
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
    float obZ = 0.0f;
    float sc = 1.0f;
    float ang = 0.0f;
    float angX = 0.0f;
    auto projection = math_utils::perspective(90,100.0f,0.5f,disp.getRatio());
    auto m = projection.getM();
    for(int i = 0; i<4;i++){
        printf("%.4f,%.4f,%.4f,%.4f\n",m[4*i],m[4*i+1],m[4*i+2],m[4*i+3]);
    }
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
        if(keys[SDL_SCANCODE_D] && sc>0.25f){
            sc -= 0.1f;
        }
        if(keys[SDL_SCANCODE_R]){
            ang += 0.01f;
        }
        if(keys[SDL_SCANCODE_F]){
            ang -= 0.01f;
        }
        if(keys[SDL_SCANCODE_Y]&&obZ<0){
            obZ += 0.1f;
            if(obZ>0){
                obZ = 0;
            }
            printf("%.3f\n",obZ);
        }
        if(keys[SDL_SCANCODE_H]&&obZ>-5){
            obZ -= 0.1f;
            printf("%.3f\n",obZ);
        }
        // Clear the screen to black
        disp.clear(0.0f,0.0f,0.0f,0.0f);

        //Set transformation matrix
        translation = math_utils::translate(obX, obY, -1+obZ);
        angX++;
        rotation = math_utils::rotateZ(ang).product(math_utils::rotateX(0.01*angX));
        
        scaling = math_utils::scale(sc, sc, 1.0f);
		global_transform = translation.product(rotation.product(scaling));
        m2d.setTransform(projection, global_transform);
        m2d.draw();

        // Swap buffers
        disp.update();
        //Control frame rate
        auto dt = (SDL_GetTicks() - lastTime);
		if (dt < 10)
		{
			SDL_Delay(10 - dt);
		}

		lastTime = SDL_GetTicks();
    }


    
    SDL_Quit();

    return 0;
}
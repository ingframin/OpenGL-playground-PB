#include <vector>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "Display.h"
#include "BallShader.h"
#include "Model.h"
#include "math_utils.h"

using namespace math_utils;

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	////glew init
	
	Display gameDisplay("Monica's Bubbles", 800, 600);

	std::vector<GLfloat> vertices = {
		0.0f,0.0f,
		1.000f,	0.000f,
		0.866f,	0.500f,
		0.500f,	0.866f,
		0.000f,	1.000f,
		-0.500f,0.866f,
		-0.866f,0.500f,
		-1.000f,0.000f,
		-0.866f,-0.500f,
		-0.500f,-0.866f,
		0.000f,-1.000f,
		0.500f,-0.866f,
		0.866f, -0.500f
		
	};

	GLuint elements[] = {
		0, 12, 11, 10,9,8,7,6,5,4,3,2,1,12
	};

	GLuint NumElements = 14;
		
	Model triangles(vertices,26,elements,NumElements);
		
	BallShader& bsp = BallShader("./shaders/vertex.glsl", "./shaders/fragment.glsl");
	
	bsp.enable();
	
	mat4 rotation = rotate(1.0f, 0.0f, 0.0f,0.0f);
	mat4 scaling = scale(gameDisplay.getRatio(), 1.0f, 1.0f);
	
	SDL_Event windowEvent;
	unsigned int lastTime = 0;
	
	while (true)
	{
		
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT) break;
		}
		gameDisplay.clear(1.0f,0.0f,0.0f,1.0f);
	
		triangles.draw();
	
		bsp.setTransform(rotation);
		
		rotation = scaling.product(rotate(0.0f, 0.0f, 1.0f, 0.001f*lastTime).product(rotate(0.0f, 1.0f, 0.0f, 0.001f*lastTime).product(rotate(1.0f, 0.0f, 0.0f, 0.0f))));
		
		gameDisplay.update();
		
		while ((SDL_GetTicks() - lastTime) < 16){
			continue;
		}
		lastTime = SDL_GetTicks();

	}
	
	gameDisplay.dispose();
	
	SDL_Quit();
	return 0;
}
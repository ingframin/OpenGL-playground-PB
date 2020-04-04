#include <vector>
#include <cstdio>
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

	Display gameDisplay("OpenGL Playground", 800, 600);

	std::vector<GLfloat> vertices = {
		-0.5f, -0.5f,
		-0.5f, 0.5f,
		0.5f, 0.5f,
		0.5f, -0.5f

	};

	std::vector<GLuint> elements = {
		0, 1, 2, 3};

	std::vector<GLfloat> tex_coordinates = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f};

	GLuint NumElements = 14;

	Model triangles(vertices, elements, tex_coordinates);
	triangles.loadTexture("fish.png");
	BallShader bsp{"./shaders/vertex.glsl", "./shaders/fragment.glsl"};

	bsp.enable();

	mat4 rotation = rotate(1.0f, 0.0f, 0.0f, 0.0f);
	mat4 scaling = scale(gameDisplay.getRatio(), 1.0f, 1.0f);
	mat4 translation = translate(0.0f, 0.0f, 0.0f);
	mat4 global_transform = translation.product(scaling.product(rotation));

	SDL_Event windowEvent;
	unsigned int lastTime = 0;

	float obX = 0.0f;
	float obY = 0.0f;

	while (true)
	{

		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT)
				break;
		}
		const Uint8 *keys = SDL_GetKeyboardState(NULL);
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

		translation = translate(obX, obY, 0.0f);
		gameDisplay.clear(1.0f, 0.0f, 0.0f, 1.0f);

		rotation = rotate(0.0f, 0.0f, 1.0f, 0.001f * lastTime);
		global_transform = translation.product(rotation.product(scaling));

		bsp.setTransform(global_transform);
		bsp.setColor(1.0f, 1.0f, 0.0f);

		triangles.draw();

		gameDisplay.update();

		while ((SDL_GetTicks() - lastTime) < 16)
		{
			continue;
		}
		lastTime = SDL_GetTicks();
	}

	gameDisplay.dispose();

	SDL_Quit();
	return 0;
}

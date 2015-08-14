#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "Display.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "math_utils.h"


enum AttribIDs{
	vPosition = 0
};



int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	////glew init
	
	Display gameDisplay("Monica's Bubbles", 800, 600);

	GLfloat vertices[26] = {
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
	
	//Init Shader program
	ShaderProgram& shp = ShaderProgram();

	shp.loadShader("./shaders/vertex.glsl", GL_VERTEX_SHADER);
	shp.loadShader("./shaders/fragment.glsl", GL_FRAGMENT_SHADER);

	shp.linkProgram();

	glUseProgram(shp.getProgramID());

	GLuint transform = glGetUniformLocation(shp.getProgramID(), "transform");

	
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE,0,nullptr);
	glEnableVertexAttribArray(vPosition);
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
		//glUniformMatrix4fv(transform, 1, GL_FALSE, glm::value_ptr(trs));
		glFlush();
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
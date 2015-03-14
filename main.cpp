#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "Display.h"
#include "ShaderProgram.h"



int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	

	////glew init
	
	Display gameDisplay("My Puzzle Bubble", 800, 600);

	// Create Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

		GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	GLuint vbo;
	glGenBuffers(1, &vbo);

	GLfloat vertices[] = {
		0.0f, 0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	{//scope of the shader program

	//Init Shader program
	ShaderProgram& shp = ShaderProgram();//I know this is too javish...

	shp.loadShader("./shaders/vertex.glsl", GL_VERTEX_SHADER);
	shp.loadShader("./shaders/fragment.glsl", GL_FRAGMENT_SHADER);

	shp.linkProgram();

	glUseProgram(shp.getProgramID());

	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation(shp.getProgramID(), "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	SDL_Event windowEvent;
	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT) break;
		}
		gameDisplay.clear(0.0f,0.0f,0.0f,1.0f);
		gameDisplay.update();
	}

	}//end scope of the shader program

	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vao);
	
	gameDisplay.dispose();
	
	SDL_Quit();
	return 0;
}
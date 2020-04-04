#include "Model.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Model::Model(std::vector<GLfloat> vertices, std::vector<GLuint> elements, std::vector<GLfloat> tex_coordinates)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &tex_c);
	glBindBuffer(GL_ARRAY_BUFFER, tex_c);
	this->tex_coords = tex_coordinates;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat) * tex_coordinates.size(), &tex_coords[0], GL_STATIC_DRAW);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	this->vertices = vertices;
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	this->elements = elements;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * elements.size(), &elements[0], GL_STATIC_DRAW);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Model::draw() const
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLE_FAN, elements.size(), GL_UNSIGNED_INT, 0);
}

void Model::loadTexture(const string &filename)
{
	SDL_Surface *tmp = IMG_Load(filename.c_str());
	int Mode = GL_RGB;

	if (tmp->format->BytesPerPixel == 4)
	{
		Mode = GL_RGBA;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, Mode, tmp->w, tmp->h, 0, Mode, GL_UNSIGNED_BYTE, tmp->pixels);
	SDL_FreeSurface(tmp);
}

Model::~Model()
{
}

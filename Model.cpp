#include "Model.h"


Model::Model(std::vector<GLfloat> vertices, std::vector<GLuint> elements)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vsize, &vertices[0], GL_STATIC_DRAW);
	this->vertices = vertices;
	this->vsize = vertices.size();

	glGenBuffers(1, &ebo);
	this->esize = elements.size();
	this->elements = elements;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*esize, &elements[0], GL_STATIC_DRAW);


}

void Model::draw() const{
	
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLE_FAN, esize, GL_UNSIGNED_INT, 0);
}



Model::~Model()
{
	
}

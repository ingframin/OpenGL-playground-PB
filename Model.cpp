#include "Model.h"


Model::Model(GLfloat* vertices)
{
	glGenBuffers(1, &m_vbo);
	m_vertices = vertices;
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

}


Model::~Model()
{
	glDeleteBuffers(1, &m_vbo);
}

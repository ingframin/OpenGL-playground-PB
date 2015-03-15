#pragma once
#include<string>
#include <GL/glew.h>

class Model
{
public:
	Model(GLfloat* vertices);
	
	//void rotate(float alpha, float beta, float gamma);
	//void translate(float dx, float dy, float dz);
	
	~Model();

private:

	GLuint m_vbo;
	GLfloat* m_vertices;
	float* m_colors;
	float m_Xcenter;
	float m_Ycenter;

};


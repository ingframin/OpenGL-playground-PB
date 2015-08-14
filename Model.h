#pragma once
#include <GL/glew.h>
#include "math_utils.h"


class Model
{
public:
	Model(GLfloat vertices[], GLuint vsize, GLuint* elements, GLuint esize);
	~Model();
	void draw();
	mat4& rotate(float alpha, float beta, float gamma);
	mat4& translate(float dx, float dy, float dz);
	mat4& scale(float s);

private:
	GLuint vao;

	GLuint ebo;
	GLuint* elements;
	GLuint esize;

	GLuint vbo;
	GLfloat* vertices;
	GLuint vsize;
	

};


#pragma once
#include "Model.h"


Model::Model(GLfloat vertices[], GLuint vsize, GLuint* elements, GLuint esize)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vsize, vertices, GL_STATIC_DRAW);
	this->vertices = vertices;
	this->vsize = vsize;

	glGenBuffers(1, &ebo);
	this->esize = esize;
	this->elements = elements;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*esize, elements, GL_STATIC_DRAW);
}

void Model::draw(){
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLE_FAN, esize, GL_UNSIGNED_INT, 0);
}

mat4& Model::rotate(float alpha, float beta, float gamma){

	float x_rotation_matrix[] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos(alpha), -sin(alpha), 0.0f,
		0.0f, sin(alpha), cos(alpha), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f };

	mat4 xr = mat4(x_rotation_matrix);

	float y_rotation_matrix[] = {
		cos(beta), 0.0f, -sin(beta), 0.0f,
		0.0f, 1.0, 0.0, 0.0f,
		0.0f, sin(alpha), 0.0f, cos(alpha),
		0.0f, 0.0f, 0.0f, 1.0f };
	
	mat4 yr = mat4(y_rotation_matrix);
	
	float z_rotation_matrix[] = {
		cos(gamma), -sin(gamma), 0.0f, 0.0f,
		sin(gamma), cos(gamma), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f };

	mat4 zr = mat4(z_rotation_matrix);

	mat4 result = xr.product(yr);
	result = result.product(zr);
	
	return result;

}

mat4& Model::translate(float dx, float dy, float dz){

	float translation_matrix[] = {
		1.0f, 0.0f, 0.0f, dx,
		0.0f, 1.0f, 0.0f, dy,
		0.0f, 0.0f, 1.0f, dz,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return mat4(translation_matrix);
	
}

Model::~Model()
{
	
}

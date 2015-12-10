#pragma once
#include <vector>
#include <string>
#include <GL/glew.h>
#include "math_utils.h"
#include "ShaderProgram.h"
using namespace std;



class Model
{
public:
	Model(std::vector<GLfloat> vertices, GLuint vsize, GLuint* elements, GLuint esize);
	~Model();
	void loadShaders(const string vertex_shader, const string fragment_shader);
	void draw() const;
	
	

private:
	//Geometry data
	GLuint vao;

	GLuint ebo;
	GLuint* elements;
	GLuint esize;

	GLuint vbo;
	std::vector<GLfloat> vertices;
	GLuint vsize;
	
};


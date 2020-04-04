#ifndef MODEL
#define MODEL
#include <vector>
#include <string>
#include <GL/glew.h>
#include "math_utils.h"
#include "ShaderProgram.h"


using namespace std;



class Model
{
public:
	Model(std::vector<GLfloat> vertices, std::vector<GLuint> elements, std::vector<GLfloat> tex_coordinates);
	~Model();
	void loadShaders(const string& vertex_shader, const string& fragment_shader);
	void loadTexture(const string& filename);
	void draw() const;
	
	

private:
	//Geometry data
	GLuint vao;
	GLuint ebo;
	GLuint vbo;
	GLuint texture;
	GLuint tex_c;//texture coordinates buffer
	

	std::vector<GLuint> elements;
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> tex_coords;
};

#endif
#pragma once
#include <string>
#include <GL/glew.h>
#include <vector>

class ShaderProgram
{
public:
	ShaderProgram(void);
	virtual ~ShaderProgram();
	void loadShader(const std::string& fileName, GLenum shaderType);
	void linkProgram();
	GLuint getProgramID();

private:
	
	
	GLuint m_program;
	std::vector<GLuint> m_shaders;
};


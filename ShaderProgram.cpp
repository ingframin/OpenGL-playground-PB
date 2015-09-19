#include "ShaderProgram.h"
#include <iostream>
#include <fstream>

ShaderProgram::ShaderProgram(void)
{
	m_shaders = std::vector<GLuint>();
	m_program = glCreateProgram();


}

void ShaderProgram::linkProgram()
{
	for (GLuint shd : m_shaders){
		glAttachShader(m_program, shd);
	}
	glLinkProgram(m_program);

}


ShaderProgram::~ShaderProgram()
{
	for (GLuint shd: m_shaders){
		glDetachShader(m_program, shd);
		glDeleteShader(shd);
	}
	glDeleteProgram(m_program);
}

void ShaderProgram::loadShader(const std::string& fileName, const GLenum shaderType)
{
	std::ifstream file;
	file.open((fileName).c_str());
	std::string text;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			text.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
		return;
	}
	
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0){
		std::cerr << "Error: Shader creation failed" << std::endl;
	}

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceLengths[1];

	//TODO: Check errors!!!
	
	shaderSourceStrings[0] = text.c_str();
	shaderSourceLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceLengths);
	glCompileShader(shader);
	
	m_shaders.push_back(shader);

}

GLuint ShaderProgram::getProgramID() const
{
	return m_program;
}
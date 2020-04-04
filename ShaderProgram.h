#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM
#include <string>
#include <GL/glew.h>
#include <vector>

class ShaderProgram
{
public:
	ShaderProgram(void);
	virtual ~ShaderProgram();
	void loadShader(const std::string& fileName, const GLenum shaderType);
	void linkProgram();
	GLuint getProgramID() const;
	inline void useProgram(){ glUseProgram(m_program); }
private:
		
	GLuint m_program;
	std::vector<GLuint> m_shaders;
};

#endif
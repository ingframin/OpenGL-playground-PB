#pragma once
#include <string>
#include "ShaderProgram.h"
#include "math_utils.h"

using namespace std;

class BallShader :
	public ShaderProgram
{
public:
	BallShader(const string vertex_shader, const string fragment_shader);
	void setTransform(const math_utils::mat4 transform);
	void BallShader::enable();
	virtual ~BallShader();
private:
	GLuint vPosition;
	GLuint transform;

};


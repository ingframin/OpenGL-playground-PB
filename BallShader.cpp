#include "BallShader.h"

BallShader::BallShader(const string vertex_shader, const string fragment_shader)
{

	loadShader(vertex_shader, GL_VERTEX_SHADER);
	loadShader(fragment_shader, GL_FRAGMENT_SHADER);
	linkProgram();
	glUseProgram(getProgramID());

	transform = glGetUniformLocation(getProgramID(), "transform");
	in_color = glGetUniformLocation(getProgramID(), "in_color");

	vPosition = 0;
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);

	tCoords = 1;
	glEnableVertexAttribArray(tCoords);
	glVertexAttribPointer(tCoords, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void BallShader::setTransform(const math_utils::mat4 trans_matrix)
{
	glUniformMatrix4fv(transform, 1, GL_FALSE, trans_matrix.getm());
}

void BallShader::setColor(float r, float g, float b)
{
	glUniform3f(in_color, r, g, b);
}
void BallShader::enable()
{
	glUseProgram(getProgramID());
	glEnableVertexAttribArray(vPosition);
}

BallShader::~BallShader()
{
}

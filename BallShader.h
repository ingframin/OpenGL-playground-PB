#ifndef BALL_SHADER
#define BALL_SHADER
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
	void setColor(float r, float g, float b);
	void enable();
	virtual ~BallShader();
private:
	GLuint vPosition;
	GLuint transform;
	GLuint in_color;

};

#endif
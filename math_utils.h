#pragma once
#include <intrin.h>
#include <cmath>


class vec4{
public:
	vec4(float x, float y, float z, float w);
	float* operator[](char i);
	inline float get(unsigned int i);
	inline void set(unsigned int i, float value);
	inline float dot_product(vec4& v);

	~vec4(){};
private:
	float v[4];
};

class mat4{
public:

	mat4(float* mc);
	
	mat4& product(mat4& m);
	vec4& product(vec4& v);
	float get(unsigned int x, unsigned int y);
	void set(unsigned int x, unsigned int y, float v);

private:
	float m[16];

};

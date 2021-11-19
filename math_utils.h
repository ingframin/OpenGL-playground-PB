#ifndef MATH_UTILS
#define MATH_UTILS
#include <cmath>
#include <vector>


namespace math_utils{
	class vec4{
	public:
		vec4(float x, float y, float z, float w);
		vec4();
		float& operator[](int index);
		float& operator[](char index);
		
		const float* getV()const { return v; }
		
		float dot_product(const vec4& v) const;
		float mod();

	private:
		float v[4];
	};

	class mat4{
	public:

		mat4(const float* mc);
		mat4();
		mat4 product(mat4 m);
		vec4 product(vec4 v);
		void transpose();
		float* getM();


	private:
		vec4 row1;
		vec4 row2;
		vec4 row3;
		vec4 row4;

	};

	mat4 rotateX(float ang);
	mat4 rotateY(float ang);
	mat4 rotateZ(float ang);
	mat4 translate(float dx, float dy, float dz);
	mat4 scale(float sx, float sy, float sz);
	mat4 perspective(float fov, float far, float near);
}
#endif

#ifndef MATH_UTILS
#define MATH_UTILS
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include <cmath>
#include <array>


namespace math_utils{
	

	class mat4{
	public:

		mat4(const float mc[16]);
        mat4();
        mat4 product(mat4 m);
		vec4 product(vec4 v);
		void transpose();
		std::array<float,16> getM();


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
	mat4 perspective(float fov, float far, float near, float asp_ratio);
};

#endif

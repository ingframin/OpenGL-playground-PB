#ifndef MATH_UTILS
#define MATH_UTILS
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include <cmath>
#include <vector>


namespace math_utils{
	

	class mat4{
	public:

		mat4(const double* mc);
		mat4();
		mat4 product(mat4 m);
		vec4 product(vec4 v);
		void transpose();
		std::vector<double> getM();


	private:
		vec4 row1;
		vec4 row2;
		vec4 row3;
		vec4 row4;

	};

	mat4 rotateX(double ang);
	mat4 rotateY(double ang);
	mat4 rotateZ(double ang);
	mat4 translate(double dx, double dy, double dz);
	mat4 scale(double sx, double sy, double sz);
	mat4 perspective(double fov, double far, double near, double asp_ratio);
}
#endif

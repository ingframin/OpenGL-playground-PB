#ifndef MATH_UTILS
#define MATH_UTILS
#include <xmmintrin.h>
#include <cmath>
#include <vector>


namespace math_utils{
	class vec4{
	public:
		vec4(float x, float y, float z, float w);
		float get(unsigned int i) const;
		const float* getV()const { return v; }
		void set(unsigned int i, float value);
		float dot_product(const vec4& v) const;

		~vec4(){};
	private:
		float v[4];
	};

	class mat4{
	public:

		mat4(const float* mc);
		mat4();
		mat4 product(const mat4& m) const;
		vec4 product(const vec4& v) const;
		const float get(unsigned int x, unsigned int y) const;
		void set(unsigned int x, unsigned int y, float v);
		const float* getm() const { return m; }


	private:
		float m[16];

	};

	mat4 rotate(float vx, float vy, float vz, float ang);
	mat4 translate(float dx, float dy, float dz);
	mat4 scale(float sx, float sy, float sz);
	mat4 perspective(float fov, float far, float near);
}
#endif

#include "math_utils.h"

namespace math_utils{

	vec4::vec4(float x, float y, float z, float w){
		v[0] = x;
		v[1] = y;
		v[2] = z;
		v[3] = w;

	}


	float vec4::get(unsigned int i) const{
		return this->v[i];
	}

	void vec4::set(unsigned int i, float value){
		this->v[i] = value;
	}

	float vec4::dot_product(const vec4& v2) const{
		__m128 vi1 = _mm_set_ps(v[0], v[1], v[2], v[3]);
		__m128 vi2 = _mm_set_ps(v2.v[0], v2.v[1], v2.v[2], v2.v[3]);
		__m128 res = _mm_mul_ps(vi1, vi2);

		return res.m128_f32[0] + res.m128_f32[1] + res.m128_f32[2] + res.m128_f32[3];

	}


	mat4::mat4(const float* mc){
		for (int i = 0; i < 16; i++){
			m[i] = mc[i];

		}
	}

	mat4::mat4(){
		m[0] = 1.0f;
		m[1] = 0.0f;
		m[2] = 0.0f;
		m[3] = 0.0f;

		m[4] = 0.0f;
		m[5] = 1.0f;
		m[6] = 0.0f;
		m[7] = 0.0f;

		m[8] = 0.0f;
		m[9] = 0.0f;
		m[10] = 1.0f;
		m[11] = 0.0f;

		m[12] = 0.0f;
		m[13] = 0.0f;
		m[14] = 1.0f;
		m[15] = 0.0f;
	}

	mat4 mat4::product(const mat4& m2) const{
		float res[16];
		__m128 row1 = _mm_set_ps(m[0], m[1], m[2], m[3]);
		__m128 row2 = _mm_set_ps(m[4], m[5], m[6], m[7]);
		__m128 row3 = _mm_set_ps(m[8], m[9], m[10], m[11]);
		__m128 row4 = _mm_set_ps(m[12], m[13], m[14], m[15]);

		__m128 col1 = _mm_set_ps(m2.m[0], m2.m[4], m2.m[8], m2.m[12]);
		__m128 col2 = _mm_set_ps(m2.m[1], m2.m[5], m2.m[9], m2.m[13]);
		__m128 col3 = _mm_set_ps(m2.m[2], m2.m[6], m2.m[10], m2.m[14]);
		__m128 col4 = _mm_set_ps(m2.m[3], m2.m[7], m2.m[11], m2.m[15]);

		//First row
		__m128 res1 = _mm_mul_ps(row1, col1);
		__m128 res2 = _mm_mul_ps(row2, col1);
		__m128 res3 = _mm_mul_ps(row3, col1);
		__m128 res4 = _mm_mul_ps(row4, col1);

		res[0] = res1.m128_f32[0] + res1.m128_f32[1] + res1.m128_f32[2] + res1.m128_f32[3];
		res[1] = res2.m128_f32[0] + res2.m128_f32[1] + res2.m128_f32[2] + res2.m128_f32[3];
		res[2] = res3.m128_f32[0] + res3.m128_f32[1] + res3.m128_f32[2] + res3.m128_f32[3];
		res[3] = res4.m128_f32[0] + res4.m128_f32[1] + res4.m128_f32[2] + res4.m128_f32[3];

		//second row
		res1 = _mm_mul_ps(row1, col2);
		res2 = _mm_mul_ps(row2, col2);
		res3 = _mm_mul_ps(row3, col2);
		res4 = _mm_mul_ps(row4, col2);

		res[4] = res1.m128_f32[0] + res1.m128_f32[1] + res1.m128_f32[2] + res1.m128_f32[3];
		res[5] = res2.m128_f32[0] + res2.m128_f32[1] + res2.m128_f32[2] + res2.m128_f32[3];
		res[6] = res3.m128_f32[0] + res3.m128_f32[1] + res3.m128_f32[2] + res3.m128_f32[3];
		res[7] = res4.m128_f32[0] + res4.m128_f32[1] + res4.m128_f32[2] + res4.m128_f32[3];

		//third row
		res1 = _mm_mul_ps(row1, col3);
		res2 = _mm_mul_ps(row2, col3);
		res3 = _mm_mul_ps(row3, col3);
		res4 = _mm_mul_ps(row4, col3);

		res[8] = res1.m128_f32[0] + res1.m128_f32[1] + res1.m128_f32[2] + res1.m128_f32[3];
		res[9] = res2.m128_f32[0] + res2.m128_f32[1] + res2.m128_f32[2] + res2.m128_f32[3];
		res[10] = res3.m128_f32[0] + res3.m128_f32[1] + res3.m128_f32[2] + res3.m128_f32[3];
		res[11] = res4.m128_f32[0] + res4.m128_f32[1] + res4.m128_f32[2] + res4.m128_f32[3];

		//last row
		res1 = _mm_mul_ps(row1, col4);
		res2 = _mm_mul_ps(row2, col4);
		res3 = _mm_mul_ps(row3, col4);
		res4 = _mm_mul_ps(row4, col4);

		res[12] = res1.m128_f32[0] + res1.m128_f32[1] + res1.m128_f32[2] + res1.m128_f32[3];
		res[13] = res2.m128_f32[0] + res2.m128_f32[1] + res2.m128_f32[2] + res2.m128_f32[3];
		res[14] = res3.m128_f32[0] + res3.m128_f32[1] + res3.m128_f32[2] + res3.m128_f32[3];
		res[15] = res4.m128_f32[0] + res4.m128_f32[1] + res4.m128_f32[2] + res4.m128_f32[3];

		return mat4(res);
	}

	vec4 mat4::product(const vec4& v) const{
		float res[4];

		__m128 row1 = _mm_set_ps(m[0], m[1], m[2], m[3]);
		__m128 row2 = _mm_set_ps(m[4], m[5], m[6], m[7]);
		__m128 row3 = _mm_set_ps(m[8], m[9], m[10], m[11]);
		__m128 row4 = _mm_set_ps(m[12], m[13], m[14], m[15]);
		__m128 col1 = _mm_set_ps(v.get(0), v.get(1), v.get(2), v.get(3));

		//First row
		__m128 res1 = _mm_mul_ps(row1, col1);
		__m128 res2 = _mm_mul_ps(row2, col1);
		__m128 res3 = _mm_mul_ps(row3, col1);
		__m128 res4 = _mm_mul_ps(row4, col1);

		res[0] = res1.m128_f32[0] + res1.m128_f32[1] + res1.m128_f32[2] + res1.m128_f32[3];
		res[1] = res2.m128_f32[0] + res2.m128_f32[1] + res2.m128_f32[2] + res2.m128_f32[3];
		res[2] = res3.m128_f32[0] + res3.m128_f32[1] + res3.m128_f32[2] + res3.m128_f32[3];
		res[3] = res4.m128_f32[0] + res4.m128_f32[1] + res4.m128_f32[2] + res4.m128_f32[3];
		vec4 vres = vec4(res[0], res[1], res[2], res[3]);
		return vres;

	}

	mat4 rotate(float vx, float vy, float vz, float ang){
		/*rotation around an axis (vx,vy,vz) of angle ang*/
		float ca = cos(ang);
		float sa = sin(ang);
		float vxq = vx*vx;
		float vyq = vy*vy;
		float vzq = vz*vz;

		float resv[] =
		{ vxq + (1 - vxq)*ca, (1 - ca)*vx*vy - vz*sa, (1 - ca)*vx*vz + vy*sa, 0.0f,
		(1 - ca)*vy*vx + vz*sa, vyq + (1 - vyq)*ca, (1 - ca)*vy*vz - vx*sa, 0.0f,
		(1 - ca)*vz*vx - vy*sa, (1 - ca)*vz*vy + vx*sa, vzq + (1 - vzq)*ca, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		};

		return mat4(resv);

	}

	mat4 translate(float dx, float dy, float dz){

		float translation_matrix[] = {
			1.0f, 0.0f, 0.0f, dx,
			0.0f, 1.0f, 0.0f, dy,
			0.0f, 0.0f, 1.0f, dz,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		return mat4(translation_matrix);

	}

	mat4 scale(float sx, float sy, float sz){
		float scale_matrix[] = {
			1.0f / sx, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f / sy, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f / sz, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		return mat4(scale_matrix);

	}

}

#include "math_utils.h"


float* vec4::operator[](char c){
	switch (c){
	case 'x': return &v[0];
	case 'y': return &v[1];
	case 'z': return &v[2];
	case 'v': return &v[3];
	}
	return NULL;
}

float vec4::get(unsigned int i){
	return this->v[i];
}

void vec4::set(unsigned int i, float value){
	this->v[i] = value;
}

float vec4::dot_product(vec4& v2){
	__m128 vi1 = _mm_set_ps(v[0], v[1], v[2], v[3]);
	__m128 vi2 = _mm_set_ps(*v2['x'], *v2['y'], *v2['z'], *v2['v']);
	__m128 res = _mm_mul_ps(vi1, vi2);

	return res.m128_f32[0] + res.m128_f32[1] + res.m128_f32[2] + res.m128_f32[3];
	
}


mat4::mat4(float* mc){
	for (int i = 0; i < 16; i++){
		m[i] = mc[i];

	}
}

mat4& mat4::product(mat4& m2){
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

vec4& mat4::product(vec4& v){
	float res[4];
	
	__m128 row1 = _mm_set_ps(m[0], m[1], m[2], m[3]);
	__m128 row2 = _mm_set_ps(m[4], m[5], m[6], m[7]);
	__m128 row3 = _mm_set_ps(m[8], m[9], m[10], m[11]);
	__m128 row4 = _mm_set_ps(m[12], m[13], m[14], m[15]);

	__m128 col1 = _mm_set_ps(*v['x'], *v['y'], *v['z'], *v['w']);
	
	//First row
	__m128 res1 = _mm_mul_ps(row1, col1);
	__m128 res2 = _mm_mul_ps(row2, col1);
	__m128 res3 = _mm_mul_ps(row3, col1);
	__m128 res4 = _mm_mul_ps(row4, col1);

	res[0] = res1.m128_f32[0] + res1.m128_f32[1] + res1.m128_f32[2] + res1.m128_f32[3];
	res[1] = res2.m128_f32[0] + res2.m128_f32[1] + res2.m128_f32[2] + res2.m128_f32[3];
	res[2] = res3.m128_f32[0] + res3.m128_f32[1] + res3.m128_f32[2] + res3.m128_f32[3];
	res[3] = res4.m128_f32[0] + res4.m128_f32[1] + res4.m128_f32[2] + res4.m128_f32[3];
	vec4 vres = vec4(res[0],res[1],res[2],res[3]);
	return vres;

}
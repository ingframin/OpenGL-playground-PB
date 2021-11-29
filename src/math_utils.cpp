#include "math_utils.h"
#define _USE_MATH_DEFINES
#include <cmath>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#include <iostream>

namespace math_utils{
	

/**************************************************/

	mat4::mat4(const float mc[16]){
		row1 = {mc[0],mc[1],mc[2],mc[3]};
		row2 = {mc[4],mc[5],mc[6],mc[7]};
		row3 = {mc[8],mc[9],mc[10],mc[11]};
		row4 = {mc[12],mc[13],mc[14],mc[15]};
	}

	mat4::mat4(){
		row1 = {1,0,0,0};
		row2 = {0,1,0,0};
		row3 = {0,0,1,0};
		row4 = {0,0,0,1};
	}
	
	void mat4::transpose(){
		row1 = {row1.X(),row2.X(),row3.X(),row4.X()};
		row2 = {row1.Y(),row2.Y(),row3.Y(),row4.Y()};
		row3 = {row1.Z(),row2.Z(),row3.Z(),row4.Z()};
		row4 = {row1.W(),row2.W(),row3.W(),row4.W()};
	}

	mat4 mat4::product(mat4 m2){
		mat4 res;
		vec4 col1 = {m2.row1.X(),m2.row2.X(),m2.row3.X(),m2.row4.X()};
		vec4 col2 = {m2.row1.Y(),m2.row2.Y(),m2.row3.Y(),m2.row4.Y()};
		vec4 col3 = {m2.row1.Z(),m2.row2.Z(),m2.row3.Z(),m2.row4.Z()};
		vec4 col4 = {m2.row1.W(),m2.row2.W(),m2.row3.W(),m2.row4.W()};
		res.row1={
				row1.dot_product(col1),
				row2.dot_product(col1),
				row3.dot_product(col1),
				row4.dot_product(col1)
					};
		res.row2={
				row1.dot_product(col2),
				row2.dot_product(col2),
				row3.dot_product(col2),
				row4.dot_product(col2)
					};
		res.row3={
				row1.dot_product(col3),
				row2.dot_product(col3),
				row3.dot_product(col3),
				row4.dot_product(col3)
					};
		res.row4={
				row1.dot_product(col4),
				row2.dot_product(col4),
				row3.dot_product(col4),
				row4.dot_product(col4)
					};
		return res;
	}

	vec4 mat4::product(vec4 v){
		
		vec4 res={
				row1.dot_product(v),
				row2.dot_product(v),
				row3.dot_product(v),
				row4.dot_product(v)
					};
	
		return res;

	}

	
	mat4 rotateX(float ang){
		float ca = cos(ang);
		float sa = sin(ang);
		if(ca>1 || ca<-1){
			ca = ca/abs(ca);
		}
		if(sa>1 || sa<-1){
			sa = sa/abs(sa);
		}
		float res[16] = {
			1, 0, 0, 0,
			0, ca, -sa, 0,
			0, sa, ca, 0,
			0,  0, 0, 1
		};
		
		return mat4(res);
	}

	mat4 rotateY(float ang){
		float ca = cos(ang);
		float sa = sin(ang);
		if(ca>1 || ca<-1){
			ca = ca/abs(ca);
		}
		if(sa>1 || sa<-1){
			sa = sa/abs(sa);
		}
		float res[16] = {
			ca,  0, sa, 0,
			 0,  1, 0, 0,
			-sa, 0, ca, 0,
			0,    0, 0, 1
		};
		
		return mat4(res);
	}
	mat4 rotateZ(float ang){
		float ca = cos(ang);
		float sa = sin(ang);
		if(ca>1 || ca<-1){
			ca = ca/abs(ca);
		}
		if(sa>1 || sa<-1){
			sa = sa/abs(sa);
		}
		float res[16] = {
			ca, -sa, 0, 0,
			sa,  ca, 0, 0,
			0,    0, 1, 0,
			0,    0, 0, 1
		};
		
		return mat4(res);
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
			sx, 0.0f, 0.0f, 0.0f,
			0.0f, sy, 0.0f, 0.0f,
			0.0f, 0.0f, sz, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		return mat4(scale_matrix);

	}

	mat4 perspective(float fov, float far, float near, float asp_ratio){
		
		float S = 1.0f/(tan(fov*(M_PI/180)/2));
		float fn = -(far+near)/(far-near);
		float fz = -2*far*near/(far-near);

		float proj_matrix[] = {
			S*asp_ratio, 0.0f, 0.0f,  0.0f,
			0.0f,    S, 0.0f,  0.0f,
			0.0f, 0.0f,   fn,    fz,
			0.0f, 0.0f, -1.0f,  0.0f
		};
		return mat4(proj_matrix);
	}

	std::vector<float> mat4::getM(){
		auto M = std::vector<float>();
		M.push_back(row1.X());
		M.push_back(row1.Y());
		M.push_back(row1.Z());
		M.push_back(row1.W());
		
		M.push_back(row2.X());
		M.push_back(row2.Y());
		M.push_back(row2.Z());
		M.push_back(row2.W());

		M.push_back(row3.X());
		M.push_back(row3.Y());
		M.push_back(row3.Z());
		M.push_back(row3.W());

		M.push_back(row4.X());
		M.push_back(row4.Y());
		M.push_back(row4.Z());
		M.push_back(row4.W());
		return M;
	}

}

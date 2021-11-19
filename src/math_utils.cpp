#include "math_utils.h"
#define _USE_MATH_DEFINES
#include <cmath>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#include <iostream>

namespace math_utils{
	vec4::vec4(){
		v[0]=0;
		v[1]=0;
		v[2]=0;
		v[3]=1;
	}
	vec4::vec4(float x, float y, float z, float w){
		v[0] = x;
		v[1] = y;
		v[2] = z;
		v[3] = w;

	}

	float vec4::mod(){
		return sqrtf(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]+v[3]*v[3]);
	}

	float& vec4::operator[](int index){
		if(index > 3){
			std::cout<<"Index out of bounds!"<<std::endl;
			exit(0);
		}
		return v[index];

	}
	
	float& vec4::operator[](char index){
		float* ret;
		switch(index){
			case 'x': ret= &v[0];
			case 'y': ret= &v[1];
			case 'z': ret= &v[2];
			case 'w': ret= &v[3];
			default:
				std::cout<<"Index out of bounds!"<<std::endl;
				exit(0);
		}
		return *ret;
	}

	
	float vec4::dot_product(const vec4& v2) const{
		
		return v[0]*v2.v[0] + v[1]*v2.v[1] + v[2]*v2.v[2] + v[3]*v2.v[3];

	}

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
		row1 = {row1[0],row2[0],row3[0],row4[0]};
		row2 = {row1[1],row2[1],row3[1],row4[1]};
		row3 = {row1[2],row2[2],row3[2],row4[2]};
		row4 = {row1[3],row2[3],row3[3],row4[3]};
	}

	mat4 mat4::product(mat4 m2){
		mat4 res;
		vec4 col1 = {m2.row1[0],m2.row2[0],m2.row3[0],m2.row4[0]};
		vec4 col2 = {m2.row1[1],m2.row2[1],m2.row3[1],m2.row4[1]};
		vec4 col3 = {m2.row1[2],m2.row2[2],m2.row3[2],m2.row4[2]};
		vec4 col4 = {m2.row1[3],m2.row2[3],m2.row3[3],m2.row4[3]};
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

	mat4 perspective(float fov, float far, float near){
		float S = 1.0f/(tan(fov/2)*(M_PI/180 ));
		float fn = -far/(far-near);
		float proj_matrix[] = {
			S, 0.0f, 0.0f, 0.0f,
			0.0f, S, 0.0f, 0.0f,
			0.0f, 0.0f, fn, -1.0f,
			0.0f, 0.0f, fn*near, 0.0f
		};
		return mat4(proj_matrix);
	}

	float* mat4::getM(){
		auto M = new float[16];
		for(int i=0;i<4;i++){
			M[i] = row1[i];
			M[i+4] = row2[i];
			M[i+8] = row3[i];
			M[i+12] = row4[i];
		}
		return M;
	}

}

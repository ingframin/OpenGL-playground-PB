#include "Vector2.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <emmintrin.h>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif



namespace math_utils{


    vec2::vec2(){
        x = 0;
        y = 0;
    }

    vec2::vec2(float x, float y){
        this->x = x;
        this->y = y;
    }

    vec2 vec2::add(const vec2& v){
        return vec2(x+v.x,y+v.y);
    }

    vec2 vec2::sub(const vec2& v){
        return vec2(x-v.x,y-v.y);
    }
    
    float vec2::mod(){
        return sqrtf(x*x+y*y);
    }

    vec2 vec2::norm(){
        return vec2(x/mod(),y/mod());
    }

    float vec2::distance(const vec2& v){
        return sub(v).mod();
    }

    float vec2::dot_product(const vec2& v){
        return x*v.x+y*v.y;
    }

    vec2 vec2::rotate(float angle){
        __m128 v = _mm_set_ss(mod());
        __m128 n = _mm_div_ss(_mm_set_ss(1.0f), v);
        __m128 xy = _mm_mul_ss(_mm_set_ss(x), n);
        __m128 yy = _mm_mul_ss(_mm_set_ss(y), n);
        __m128 ca = _mm_set_ss(cosf(angle));
        __m128 sa = _mm_set_ss(sinf(angle));
        __m128 x_rotated = _mm_add_ss(_mm_sub_ss(_mm_mul_ss(xy, ca), _mm_mul_ss(yy, sa)), _mm_set_ss(0.0f));
        __m128 y_rotated = _mm_add_ss(_mm_add_ss(_mm_mul_ss(xy, sa), _mm_mul_ss(yy, ca)), _mm_set_ss(0.0f));
        return vec2(_mm_cvtss_f32(x_rotated), _mm_cvtss_f32(y_rotated));
        // auto m = mod();
        // auto tmp = norm();

        // float ca = cos(angle);
		// float sa = sin(angle);
        // if(ca>1 || ca<-1){
		// 	ca = ca/abs(ca);
		// }
		// if(sa>1 || sa<-1){
		// 	sa = sa/abs(sa);
		// }
        // tmp.x = (tmp.x*ca - tmp.y*sa)*m;
        // tmp.y = (tmp.x*sa + tmp.y*ca)*m;
        
        // return tmp;
    }

    vec2 vec2::scale(float kx, float ky){
        return vec2(x*kx,y*ky);
    }

    std::array<float,2> vec2::getV(){
               
        return std::array<float,2>{x,y};
    }
}


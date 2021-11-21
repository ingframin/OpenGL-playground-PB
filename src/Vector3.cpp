#include "Vector3.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

namespace math_utils{
    vec3::vec3(){
        x = 1.0f;
        y = 0.0f;
        z = 0.0f;
    }

    vec3::vec3(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
    
    vec3 vec3::add(const vec3& v){
        return vec3(x+v.x,y+v.y,z+v.z);
    }
    
    vec3 vec3::sub(const vec3& v){
        return vec3(x-v.x,y-v.y,z-v.z);
    }

    float vec3::mod(){
        return sqrtf(x*x+y*y+z*z);
    }

    float vec3::dot_product(const vec3& v){
        return x*v.x + y*v.y + z*v.z;
    }
        
    vec3 vec3::cross_product(const vec3& v){
        float nx = y*v.z - z*v.y; 
        float ny = z*v.x - x*v.z;
        float nz = x*v.y - y*v.x;
        return vec3(nx,ny,nz);
    }
    
    vec3 vec3::norm(){
        auto m = mod();
        float nx = x/m;
        float ny = y/m;
        float nz = z/m;
        return vec3(nx,ny,nz);
    }

    vec3 vec3::rotateX(float angle){
        auto m = mod();
        auto tmp = norm();

        float ca = cos(angle);
		float sa = sin(angle);
        if(ca>1 || ca<-1){
			ca = ca/abs(ca);
		}
		if(sa>1 || sa<-1){
			sa = sa/abs(sa);
		}
        tmp.x *= m;
        tmp.y = (ca*tmp.y-sa*tmp.z)*m;
        tmp.z = (sa*tmp.y+ca*tmp.z)*m;
        return tmp;

    }
    
    vec3 vec3::rotateY(float angle){
        auto m = mod();
        auto tmp = norm();

        float ca = cos(angle);
		float sa = sin(angle);
        if(ca>1 || ca<-1){
			ca = ca/abs(ca);
		}
		if(sa>1 || sa<-1){
			sa = sa/abs(sa);
		}
        tmp.x = (tmp.x*ca+tmp.z*sa)*m;
        tmp.y *= m;
        tmp.z = (-sa*tmp.x+ca*tmp.z)*m;
        return tmp;
    }
    
    vec3 vec3::rotateZ(float angle){
        auto m = mod();
        auto tmp = norm();

        float ca = cos(angle);
		float sa = sin(angle);
        if(ca>1 || ca<-1){
			ca = ca/abs(ca);
		}
		if(sa>1 || sa<-1){
			sa = sa/abs(sa);
		}
        tmp.x = (tmp.x*ca - tmp.y*sa)*m;
        tmp.y = (tmp.x*sa + tmp.y*ca)*m;
        tmp.z *= m;
        return tmp;

    }
    
    float vec3::distance(const vec3& v){
        return sub(v).mod();
    }

    vec3 vec3::scale(float kx, float ky, float kz){
        return vec3(x*kx,y*ky,z*kz);
    }

    std::vector<float> vec3::getV(){
        auto v = std::vector<float>{x,y,z};
        
        return v;
    }

}
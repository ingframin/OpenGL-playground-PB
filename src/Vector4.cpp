#include "Vector4.h"
#include <memory>
#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

namespace math_utils{

    vec4::vec4(){
		x = 0;
		y = 0;
		z = 0;
		w = 1;
	}
	vec4::vec4(float x, float y, float z, float w){
		this->x = x;
	    this->y = y;
		this->z = z;
		this->w = w;

	}

    vec4::vec4(const vec4& v){
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
    }
    
    vec4 vec4::add(const vec4& v){
        float wt = (w+v.w)/2;
        if(wt > 0){
            wt = 1.0;
        }
        else{
            wt = 0;
        }
        return vec4(x+v.x,y+v.y,z+v.z,wt);
    }

    vec4 vec4::sub(const vec4& v){
        float wt = (w+v.w)/2;
        if(wt > 0){
            wt = 1.0;
        }
        else{
            wt = 0;
        }
        return vec4(x-v.x,y-v.y,z-v.z,wt);

    }
        
    float vec4::mod(){
        return sqrtf(x*x+y*y+z*z+w*w);
    }
    
    vec4 vec4::norm(){
        auto m = mod();
        float nx = x/m;
        float ny = y/m;
        float nz = z/m;
        
        return vec4(nx,ny,nz,1.0);
    }
    
    float vec4::distance(const vec4& v){
        return sub(v).mod();
    }

    float vec4::dot_product(const vec4& v){
        return x*v.x+y*v.y+z*v.z+w*v.w;
    }
    
    vec4 vec4::rotateX(float angle){
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
        tmp.w = w;
        return tmp;

    }
    vec4 vec4::rotateY(float angle){
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
        tmp.w = w;
        return tmp;
    }

    vec4 vec4::rotateZ(float angle){
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
        tmp.w = w;
        return tmp;
    }

    vec4 vec4::scale(float kx, float ky, float kz){
        return vec4(x*kx,y*ky,z*kz,w);

    }
        
                
        
		
	std::vector<float> vec4::getV(){
        auto v = std::vector<float>();
        v.push_back(x);
        v.push_back(y);
        v.push_back(z);
        v.push_back(w);
        
        return v;
    }
	

	
}
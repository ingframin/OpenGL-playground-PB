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
	vec4::vec4(double x, double y, double z, double w){
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
        return vec4(x+v.x,y+v.y,z+v.z,w+v.w);
    }

    vec4 vec4::sub(const vec4& v){
        return vec4(x-v.x,y-v.y,z-v.z,w-v.w);

    }
        
    double vec4::mod(){
        return sqrt(x*x+y*y+z*z+w*w);
    }
    
    vec4 vec4::norm(){
        auto m = mod();
        double nx = x/m;
        double ny = y/m;
        double nz = z/m;
        
        return vec4(nx,ny,nz,1.0);
    }
    
    double vec4::distance(const vec4& v){
        return sub(v).mod();
    }

    double vec4::dot_product(const vec4& v){
        return x*v.x+y*v.y+z*v.z+w*v.w;
    }
    
    vec4 vec4::rotateX(double angle){
        auto m = mod();
        auto tmp = norm();

        double ca = cos(angle);
		double sa = sin(angle);
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
    vec4 vec4::rotateY(double angle){
        auto m = mod();
        auto tmp = norm();

        double ca = cos(angle);
		double sa = sin(angle);
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

    vec4 vec4::rotateZ(double angle){
        auto m = mod();
        auto tmp = norm();

        double ca = cos(angle);
		double sa = sin(angle);
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

    vec4 vec4::scale(double kx, double ky, double kz, double kw){
        return vec4(x*kx,y*ky,z*kz,w*kw);

    }
        
                
        
		
	std::vector<double> vec4::getV(){
        auto v = std::vector<double>();
        v.push_back(x);
        v.push_back(y);
        v.push_back(z);
        v.push_back(w);
        
        return v;
    }
	

	
}
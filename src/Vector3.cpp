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

    vec3::vec3(double x, double y, double z){
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

    double vec3::mod(){
        return sqrt(x*x+y*y+z*z);
    }

    double vec3::dot_product(const vec3& v){
        return x*v.x + y*v.y + z*v.z;
    }
        
    vec3 vec3::cross_product(const vec3& v){
        double nx = y*v.z - z*v.y; 
        double ny = z*v.x - x*v.z;
        double nz = x*v.y - y*v.x;
        return vec3(nx,ny,nz);
    }
    
    vec3 vec3::norm(){
        auto m = mod();
        double nx = x/m;
        double ny = y/m;
        double nz = z/m;
        return vec3(nx,ny,nz);
    }

    vec3 vec3::rotateX(double angle){
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
        return tmp;

    }
    
    vec3 vec3::rotateY(double angle){
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
        return tmp;
    }
    
    vec3 vec3::rotateZ(double angle){
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
        return tmp;

    }
    
    double vec3::distance(const vec3& v){
        return sub(v).mod();
    }

    vec3 vec3::scale(double kx, double ky, double kz){
        return vec3(x*kx,y*ky,z*kz);
    }

    std::vector<double> vec3::getV(){
        auto v = std::vector<double>{x,y,z};
        
        return v;
    }

}
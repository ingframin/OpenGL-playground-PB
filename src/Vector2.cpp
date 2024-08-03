#include "Vector2.h"
#define _USE_MATH_DEFINES
#include <cmath>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif



namespace math_utils{


    vec2::vec2(){
        x = 0;
        y = 0;
    }

    vec2::vec2(double x, double y){
        this->x = x;
        this->y = y;
    }

    vec2 vec2::add(const vec2& v){
        return vec2(x+v.x,y+v.y);
    }

    vec2 vec2::sub(const vec2& v){
        return vec2(x-v.x,y-v.y);
    }
    
    double vec2::mod(){
        return sqrt(x*x+y*y);
    }

    vec2 vec2::norm(){
        return vec2(x/mod(),y/mod());
    }

    double vec2::distance(const vec2& v){
        return sub(v).mod();
    }

    double vec2::dot_product(const vec2& v){
        return x*v.x+y*v.y;
    }

    vec2 vec2::rotate(double angle){
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
        
        return tmp;
    }

    vec2 vec2::scale(double kx, double ky){
        return vec2(x*kx,y*ky);
    }

    std::vector<double> vec2::getV(){
        auto v = std::vector<double>();
        v.push_back(x);
        v.push_back(y);
        
        return v;
    }
}


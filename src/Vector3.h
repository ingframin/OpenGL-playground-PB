#pragma once
#include <cmath>

namespace math_utils{

    class vec3{
        public:
        vec3();
        vec3(float x, float y, float z);
        vec3 add(const vec3& v);
        vec3 sub(const vec3& v);
        
        float mod();
        vec3 norm();
        float distance(const vec3& v);

        float dot_product(const vec3& v);
        vec3 cross_product(const vec3& v);
        
        vec3 rotateX(float angle);
        vec3 rotateY(float angle);
        vec3 rotateZ(float angle);
        vec3 scale(float kx, float ky, float kz);
        
                
        float X(){return x;}
        float Y(){return y;}
        float Z(){return z;}

        private:
        float x,y,z;

    };
}


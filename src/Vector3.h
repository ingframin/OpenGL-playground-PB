#pragma once
#include <memory>
#include <vector>

namespace math_utils{

    class vec3{
        public:
        vec3();
        vec3(double x, double y, double z);
        vec3(const vec3& v){x=v.x; y=v.y; z=v.z;};

        vec3 add(const vec3& v);
        vec3 sub(const vec3& v);
        
        double mod();
        vec3 norm();
        double distance(const vec3& v);

        double dot_product(const vec3& v);
        vec3 cross_product(const vec3& v);
        
        vec3 rotateX(double angle);
        vec3 rotateY(double angle);
        vec3 rotateZ(double angle);
        vec3 scale(double kx, double ky, double kz);
        
                
        double X(){return x;}
        double Y(){return y;}
        double Z(){return z;}

        std::vector<double> getV();

        private:
        double x,y,z;

    };
}


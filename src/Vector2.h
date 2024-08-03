#pragma once
#include <memory>
#include <vector>

namespace math_utils{

    class vec2{
        public:
        vec2();
        vec2(double x, double y);
        vec2 add(const vec2& v);
        vec2 sub(const vec2& v);
        
        double mod();
        vec2 norm();
        double distance(const vec2& v);

        double dot_product(const vec2& v);

        vec2 rotate(double angle);
        vec2 scale(double kx, double ky);
        
                
        double X(){return x;}
        double Y(){return y;}

        std::vector<double> getV();

        private:
        double x,y;

    };
}


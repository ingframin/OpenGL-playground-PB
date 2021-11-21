#pragma once
#include <memory>
#include <vector>

namespace math_utils{

    class vec2{
        public:
        vec2();
        vec2(float x, float y);
        vec2 add(const vec2& v);
        vec2 sub(const vec2& v);
        
        float mod();
        vec2 norm();
        float distance(const vec2& v);

        float dot_product(const vec2& v);

        vec2 rotate(float angle);
        vec2 scale(float kx, float ky);
        
                
        float X(){return x;}
        float Y(){return y;}

        std::vector<float> getV();

        private:
        float x,y;

    };
}


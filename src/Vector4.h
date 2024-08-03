#pragma once
#include <memory>
#include <vector>
namespace math_utils{

class vec4{
	public:
		vec4(float x, float y, float z, float w);
		vec4();
        vec4(const vec4& v);
        vec4 add(const vec4& v);
        vec4 sub(const vec4& v);
        
        float mod();
        vec4 norm();
        float distance(const vec4& v);

        float dot_product(const vec4& v);
        vec4 cross_product(const vec4& v);
        
        vec4 rotateX(float angle);
        vec4 rotateY(float angle);
        vec4 rotateZ(float angle);
        vec4 scale(float kx, float ky, float kz, float kw);
        
                
        float X(){return x;}
        float Y(){return y;}
        float Z(){return z;}
        float W(){return w;}
		
		std::vector<float> getV();

	private:
		float x,y,z,w;
	};
}

#pragma once
#include <memory>
#include <vector>
namespace math_utils{

class vec4{
	public:
		vec4(double x, double y, double z, double w);
		vec4();
        vec4(const vec4& v);
        vec4 add(const vec4& v);
        vec4 sub(const vec4& v);
        
        double mod();
        vec4 norm();
        double distance(const vec4& v);

        double dot_product(const vec4& v);
        vec4 cross_product(const vec4& v);
        
        vec4 rotateX(double angle);
        vec4 rotateY(double angle);
        vec4 rotateZ(double angle);
        vec4 scale(double kx, double ky, double kz, double kw);
        
                
        double X(){return x;}
        double Y(){return y;}
        double Z(){return z;}
        double W(){return w;}
		
		std::vector<double> getV();

	private:
		double x,y,z,w;
	};
}

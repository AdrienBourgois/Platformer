#include <cmath>
#include <GL/glew.h>
#include <vector>

#include "maths/utility.h"
#include "maths/vector.h"

namespace id {
namespace maths {

auto degToRad(float angle) -> float
{
	return angle * M_PI / 180.f;
}
auto radToDeg(float angle) -> float
{
	return angle * 180.f / M_PI;	
}

auto calcDistance(Vector3 pPoint, Vector3 pNormal, Vector3 sCenter, float sRayon) -> float
{
	return abs(sqrt(pNormal.dotProduct(sCenter - pPoint))) - sRayon;
}

auto calcDistance(Vector3 s1Center, float s1Rayon, Vector3 s2Center, float s2Rayon) -> float
{
	return (s1Center - s2Center).norm() - (s1Rayon + s2Rayon);
}

std::vector<GLfloat> const Shape::cube{
	-1.0f,-1.0f,-1.0f,		0.f, 0.f,		 0.f, 0.f, 0.f,
	-1.0f,-1.0f, 1.0f,		1.f, 0.f,		 0.f, 0.f, 0.f,
	-1.0f, 1.0f, 1.0f,		1.f, 1.f,		 0.f, 0.f, 0.f,
 
     1.0f, 1.0f,-1.0f,		0.f, 1.f,		 0.f, 0.f, 0.f,
    -1.0f,-1.0f,-1.0f,		1.f, 0.f,		 0.f, 0.f, 0.f,
    -1.0f, 1.0f,-1.0f,		1.f, 1.f,		 0.f, 0.f, 0.f,
 ////////////////////////////////////		 /
	 1.0f,-1.0f, 1.0f,		1.f, 1.f,		 0.f, 0.f, 0.f,
    -1.0f,-1.0f,-1.0f,		0.f, 0.f,		 0.f, 0.f, 0.f,
    1.0f,-1.0f,-1.0f,		1.f, 0.f,		 0.f, 0.f, 0.f,
                                                           
	1.0f, 1.0f,-1.0f,		0.f, 1.f,		 0.f, 0.f, 0.f,
    1.0f,-1.0f,-1.0f,		0.f, 0.f,		 0.f, 0.f, 0.f,
    -1.0f,-1.0f,-1.0f,		1.f, 0.f,		 0.f, 0.f, 0.f,
 ////////////////////////////////////		 /
	-1.0f,-1.0f,-1.0f,		0.f, 0.f,		 0.f, 0.f, 0.f,
    -1.0f, 1.0f, 1.0f,		1.f, 1.f,		 0.f, 0.f, 0.f,
    -1.0f, 1.0f,-1.0f,		0.f, 1.f,		 0.f, 0.f, 0.f,
                                                           
	1.0f,-1.0f, 1.0f,		1.f, 1.f,		 0.f, 0.f, 0.f,
    -1.0f,-1.0f, 1.0f, 		0.f, 1.f,		 0.f, 0.f, 0.f,
    -1.0f,-1.0f,-1.0f,		0.f, 0.f,		 0.f, 0.f, 0.f,
 ////////////////////////////////////		 /  
	-1.0f, 1.0f, 1.0f,		0.f, 1.f,		 0.f, 0.f, 0.f,
    -1.0f,-1.0f, 1.0f,		0.f, 0.f,		 0.f, 0.f, 0.f,
    1.0f,-1.0f, 1.0f,		1.f, 0.f,		 0.f, 0.f, 0.f,
                                                           
	1.0f, 1.0f, 1.0f,		0.f, 1.f,		 0.f, 0.f, 0.f,
    1.0f,-1.0f,-1.0f,		1.f, 0.f,		 0.f, 0.f, 0.f,
    1.0f, 1.0f,-1.0f,		1.f, 1.f,		 0.f, 0.f, 0.f,
 ////////////////////////////////////		 /
	1.0f,-1.0f,-1.0f,		1.f, 0.f,		 0.f, 0.f, 0.f,
    1.0f, 1.0f, 1.0f,		0.f, 1.f,		 0.f, 0.f, 0.f,
    1.0f,-1.0f, 1.0f,		0.f, 0.f,		 0.f, 0.f, 0.f, 
                                                           
	1.0f, 1.0f, 1.0f,		1.f, 0.f,		 0.f, 0.f, 0.f, 
    1.0f, 1.0f,-1.0f,		1.f, 1.f,		 0.f, 0.f, 0.f, 
    -1.0f, 1.0f,-1.0f,		0.f, 1.f,		 0.f, 0.f, 0.f, 
 ////////////////////////////////////		 /   
	1.0f, 1.0f, 1.0f,		1.f, 0.f,		 0.f, 0.f, 0.f, 
    -1.0f, 1.0f,-1.0f,		0.f, 1.f,		 0.f, 0.f, 0.f, 
    -1.0f, 1.0f, 1.0f,		0.f, 0.f,		 0.f, 0.f, 0.f, 
                                                           
	1.0f, 1.0f, 1.0f,		1.f, 1.f,		 0.f, 0.f, 0.f, 
    -1.0f, 1.0f, 1.0f,		0.f, 1.f,		 0.f, 0.f, 0.f, 
    1.0f,-1.0f, 1.0f, 		1.f, 0.f,		 0.f, 0.f, 0.f
};

Color4::Color4(float c1, float c2, float c3, float c4)
{
	this->color[0] = c1/255;
	this->color[1] = c2/255;
	this->color[2] = c3/255;
	this->color[3] = c4/255;
}

} // namespace maths
} // namespace id

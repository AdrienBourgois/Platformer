#include <cmath>

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

auto calcDistance(Vector3 point, Vector4 plan) -> float
{
    return (abs(plan.val[0] * point.val[0] + plan.val[1] * point.val[1] + plan.val[2] * point.val[2] + plan.val[3]) / sqrt(pow(plan.val[0], 2) + pow(plan.val[1], 2) + pow(plan.val[2], 2)));
}

auto cartEquation(Vector3 vec1, Vector3 vec2, Vector3 vec3) -> Vector4
{
    Vector3 AB = vec2 - vec1;
    Vector3 BC = vec3 - vec1;

    Vector3 M = AB.crossProduct(BC);

    int d = -((vec1.val[0] * M.val[0]) + (vec1.val[1] * M.val[1]) + (vec1.val[2] * M.val[2]));

    Vector4 equation;

    equation.val[0] = M.val[0];
    equation.val[1] = M.val[1];
    equation.val[2] = M.val[2];
    equation.val[3] = d;

    return equation;
}

auto isPointInsidePoly(Vector3 point, std::vector<Vector3> poly) -> bool
{
    int j = poly.size();

    bool c = false;

    for (unsigned int i = 0; i < poly.size(); ++i)
    {
        if (((poly[i].val[1] > point.val[1]) != (poly[j].val[1] > point.val[1])) &&
           (point.val[0] < (poly[j].val[0] - poly[i].val[0]) * (point.val[1] - poly[i].val[1] / (poly[j].val[1] - poly[i].val[1] + poly[i].val[0]))))
            c = !c;

        j = i;
    }

    return c;
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

} // namespace maths
} // namespace id

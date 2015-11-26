#include <cmath>
#include <algorithm>
#include <utility>

#include "maths/utility.h"
#include "maths/vector.h"
#include "maths/matrix.h"

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

auto calcDistance(Vector3 point, Vector4 polyhedron) -> float
{
    return (abs(polyhedron.val[0] * point.val[0] + polyhedron.val[1] * point.val[1] + polyhedron.val[2] * point.val[2] + polyhedron.val[3]) / sqrt(pow(polyhedron.val[0], 2) + pow(polyhedron.val[1], 2) + pow(polyhedron.val[2], 2)));
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

auto minCoordRange(std::vector<Vector3> poly, int& x, int& y) -> void
{
    std::vector<float> X;
    std::vector<float> Y;
    std::vector<float> Z;

    for (unsigned int i = 0; i < poly.size(); ++i)
    {
        X.push_back(poly[i].val[0]);
        Y.push_back(poly[i].val[1]);
        Z.push_back(poly[i].val[2]);
    }

    auto minMaxX = std::minmax_element(X.begin(), X.end());
    auto minMaxY = std::minmax_element(Y.begin(), Y.end());
    auto minMaxZ = std::minmax_element(Z.begin(), Z.end());

    float diffX = minMaxX.second - minMaxX.first;
    float diffY = minMaxY.second - minMaxY.first;
    float diffZ = minMaxZ.second - minMaxZ.first;

    float min = std::min(std::min(diffX, diffY), diffZ);

    if (min == diffX)
    {
        x = 1;
        y = 2;
    }
    else if (min == diffY)
    {
        x = 0;
        y = 2;
    }
    else if (min == diffZ)
    {
        x = 0;
        y = 1;
    }
}

auto isPointInsidePoly(Vector3 point, std::vector<Vector3> poly) -> bool
{
    int j = poly.size();

    bool c = false;

    int x = 0;
    int y = 0;

    minCoordRange(poly, x, y);
    for (unsigned int i = 0; i < poly.size(); ++i)
    {
        if (((poly[i].val[y] > point.val[y]) != (poly[j].val[y] > point.val[y])) &&
           (point.val[x] < (poly[j].val[x] - poly[i].val[x]) * (point.val[y] - poly[i].val[y] / (poly[j].val[y] - poly[i].val[y] + poly[i].val[x]))))
				c = !c;

        j = i;
    }
    return c;
}

auto getPointsFromVectorFloat(std::vector<float> shape) -> std::vector<Vector3>
{
	std::vector<Vector3> points;
	Vector3 point;
	float x = 0, y = 0, z = 0;


	for (unsigned int i = 0; i < shape.size(); ++i)
	{
		if (i % 8 == 0)
			x = shape[i];
		else if (i % 8 == 1 )
			y = shape[i];
		else if ( i % 8 == 2 )
		{
			z = shape[i];
			point = {x, y, z};
			points.push_back(point);
		}
	}

	return points;	

}

auto calCoordFromMatrix(std::vector<Vector3> vecPoint, Matrix4x4 matrix) -> std::vector<Vector3>
{
	Vector3 oldPos;

	for (auto&& point : vecPoint)
	{
		oldPos = point;
		matrix *= matrix.translate(point.val[0], point.val[1], point.val[2]);
		point = matrix.getPosition();
		matrix *= matrix.translate(-oldPos.val[0], -oldPos.val[1], -oldPos.val[2]);
	}

	return vecPoint;	
}


std::vector<GLfloat> const Shape::cube{
	-1.0f, -1.0f, -1.0f,	0.f, 0.f,		 0.f, 0.f, 0.f,
	-1.0f, -1.0f, 1.0f,		1.f, 0.f,		 0.f, 0.f, 0.f,
	-1.0f, 1.0f, 1.0f,		1.f, 1.f,		 0.f, 0.f, 0.f,
 
     1.0f, 1.0f, -1.0f,		0.f, 1.f,		 0.f, 0.f, 0.f,
    -1.0f, -1.0f, -1.0f,	1.f, 0.f,		 0.f, 0.f, 0.f,
    -1.0f, 1.0f, -1.0f,		1.f, 1.f,		 0.f, 0.f, 0.f,
 ////////////////////////////////////		 /
	 1.0f, -1.0f, 1.0f,		1.f, 1.f,		 0.f, 0.f, 0.f,
    -1.0f, -1.0f, -1.0f,	0.f, 0.f,		 0.f, 0.f, 0.f,
    1.0f, -1.0f, -1.0f,		1.f, 0.f,		 0.f, 0.f, 0.f,
                                                           
	1.0f, 1.0f, -1.0f,		0.f, 1.f,		 0.f, 0.f, 0.f,
    1.0f, -1.0f, -1.0f,		0.f, 0.f,		 0.f, 0.f, 0.f,
    -1.0f, -1.0f, -1.0f,	1.f, 0.f,		 0.f, 0.f, 0.f,
 ////////////////////////////////////		 /
	-1.0f, -1.0f, -1.0f,	0.f, 0.f,		 0.f, 0.f, 0.f,
    -1.0f, 1.0f, 1.0f,		1.f, 1.f,		 0.f, 0.f, 0.f,
    -1.0f, 1.0f, -1.0f,		0.f, 1.f,		 0.f, 0.f, 0.f,
                                                           
	1.0f, -1.0f, 1.0f,		1.f, 1.f,		 0.f, 0.f, 0.f,
    -1.0f, -1.0f, 1.0f, 	0.f, 1.f,		 0.f, 0.f, 0.f,
    -1.0f, -1.0f, -1.0f,	0.f, 0.f,		 0.f, 0.f, 0.f,
 ////////////////////////////////////		 /  
	-1.0f, 1.0f, 1.0f,		0.f, 1.f,		 0.f, 0.f, 0.f,
    -1.0f, -1.0f, 1.0f,		0.f, 0.f,		 0.f, 0.f, 0.f,
    1.0f, -1.0f, 1.0f,		1.f, 0.f,		 0.f, 0.f, 0.f,
                                                           
	1.0f, 1.0f, 1.0f,		0.f, 1.f,		 0.f, 0.f, 0.f,
    1.0f, -1.0f, -1.0f,		1.f, 0.f,		 0.f, 0.f, 0.f,
    1.0f, 1.0f, -1.0f,		1.f, 1.f,		 0.f, 0.f, 0.f,
 ////////////////////////////////////		 /
	1.0f, -1.0f, -1.0f,		1.f, 0.f,		 0.f, 0.f, 0.f,
    1.0f, 1.0f, 1.0f,		0.f, 1.f,		 0.f, 0.f, 0.f,
    1.0f,-1.0f, 1.0f,		0.f, 0.f,		 0.f, 0.f, 0.f, 
                                                           
	1.0f, 1.0f, 1.0f,		1.f, 0.f,		 0.f, 0.f, 0.f, 
    1.0f, 1.0f, -1.0f,		1.f, 1.f,		 0.f, 0.f, 0.f, 
    -1.0f, 1.0f, -1.0f,		0.f, 1.f,		 0.f, 0.f, 0.f, 
 ////////////////////////////////////		 /   
	1.0f, 1.0f, 1.0f,		1.f, 0.f,		 0.f, 0.f, 0.f, 
    -1.0f, 1.0f, -1.0f,		0.f, 1.f,		 0.f, 0.f, 0.f, 
    -1.0f, 1.0f, 1.0f,		0.f, 0.f,		 0.f, 0.f, 0.f, 
                                                           
	1.0f, 1.0f, 1.0f,		1.f, 1.f,		 0.f, 0.f, 0.f, 
    -1.0f, 1.0f, 1.0f,		0.f, 1.f,		 0.f, 0.f, 0.f, 
    1.0f, -1.0f, 1.0f, 		1.f, 0.f,		 0.f, 0.f, 0.f
};

} // namespace maths
} // namespace id

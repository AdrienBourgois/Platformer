#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <vector>
#include <GL/glew.h>

namespace id {
namespace maths {

class Matrix4x4;
class Vector3;  
class Vector4;  

auto degToRad(float angle) -> float;
auto radToDeg(float angle) -> float;

auto calcDistance(Vector3 pPoint, Vector3 pNormal, Vector3 sCenter, float sRayon) -> float;
auto calcDistance(Vector3 s1Center, float s1Rayon, Vector3 s2center, float s2Rayon) -> float;
auto calcDistance(Vector3 point, Vector4 polyhedron) -> float;

auto cartEquation(Vector3 vec1, Vector3 vec2, Vector3 vec3) -> Vector4;
auto minCoordRange(std::vector<Vector3> poly, int& x, int& y) -> void;
auto isPointInsidePoly(Vector3 point, std::vector<Vector3> poly) -> bool;

auto getPointsFromVectorFloat(std::vector<float> shape) -> std::vector<Vector3>;
auto calCoordFromMatrix(std::vector<Vector3> vec, Matrix4x4 matrix) -> std::vector<Vector3>;

auto collideRayTriangle(const Vector3 V1, const Vector3 V2, const Vector3 V3, const Vector3 O, const Vector3 D) -> bool;


auto less_by_x(const Vector3& point1, const Vector3& point2) -> bool;
auto less_by_y(const Vector3& point1, const Vector3& point2) -> bool;
auto less_by_z(const Vector3& point1, const Vector3& point2) -> bool;
auto more_by_x(const Vector3& point1, const Vector3& point2) -> bool;
auto more_by_y(const Vector3& point1, const Vector3& point2) -> bool;
auto more_by_z(const Vector3& point1, const Vector3& point2) -> bool;

class Shape
{
    public:
        static std::vector<GLfloat>const cube;
};


} // namespace maths
} // namespace id

#endif // UTILITY_H_INCLUDED

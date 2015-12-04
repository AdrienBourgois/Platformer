#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED

namespace id {
namespace maths {

class Vector3;

class Sphere{
	public: 
		Sphere() = default;
		~Sphere() = default;
		Sphere(Sphere const&) = default;
		Sphere(Sphere&&) = default;
		auto operator=(Sphere const&) -> Sphere& = default;
		auto operator=(Sphere&&) -> Sphere& = default;

		auto getCenter() const -> Vector3 { return center; }
		auto getRayon() const -> float { return rayon; }

	private:
		Vector3 center;
		float rayon;
};

} // namespace maths
} // namespace id

#endif // SPHERE_H_INCLUDED
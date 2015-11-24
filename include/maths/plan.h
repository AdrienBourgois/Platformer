#ifndef PLAN_H_INCLUDED
#define PLAN_H_INCLUDED

#include "maths/vector.h"

namespace id {
namespace maths {

class Plan
{
	public:
		Plan(Vector3 vec1 = {1,0,0}, Vector3 vec2 = {0,1,0}, Vector3 vec3 = {0,0,1});
		~Plan();
		Plan(Plan const&) = default;
		Plan(Plan&&) = default;
		auto operator=(Plan const&) -> Plan& = default;
		auto operator=(Plan&&) -> Plan& = default;


		auto getPoints() const -> const Vector3* { return points; }

	private:
		Vector3 points[3];
};

} // namespace maths
} // namespace id

#endif // PLAN_H_INCLUDED

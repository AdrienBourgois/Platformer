#ifndef PLAN_H_INCLUDED
#define PLAN_H_INCLUDED

#include "maths/vector.h"

namespace id {
namespace maths {

class Plan
{
	public:
		Plan() = default;
		~Plan() = default;
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

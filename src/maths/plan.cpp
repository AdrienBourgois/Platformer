#include "maths/plan.h"
#include "txtLogger.h"

namespace { 
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace maths {

Plan::Plan(Vector3 vec1, Vector3 vec2, Vector3 vec3)
:points({vec1,vec2,vec3})
{
	logger->log("Creating plan...", LL_DEBUG);

	logger->log("Plan has been created.");
}

Plan::~Plan()
{
	logger->log("Deleting plan...", LL_DEBUG);

	logger->log("Plan has been deleted.");
}

} // namespace maths
} // namespace id

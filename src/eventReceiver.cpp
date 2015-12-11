#include "device.h"
#include "logger.h"
#include "eventReceiver.h"

namespace id {
namespace event {

EventReceiver::EventReceiver(Device* dev, std::string name)
: dev(dev), name(name)
{
	LOG(L_INFO ,"Creating EventReceiver...");

	LOG(L_INFO ,"EventReceiver created");
}
EventReceiver::~EventReceiver()
{
	LOG(L_INFO ,"Deleting EventReceiver...");

	this->dev = nullptr;

	LOG(L_INFO ,"EventReceiver deleted");
}

} // end namespace event

} // end namespace id

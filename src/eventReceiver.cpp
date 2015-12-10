#include "txtLogger.h"
#include "eventReceiver.h"
#include "device.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace event {

EventReceiver::EventReceiver(Device* dev, std::string name)
: dev(dev), name(name)
{
	logger->log("Creating EventReceiver...", LL_INFO);

	logger->log("EventReceiver created", LL_INFO);
}
EventReceiver::~EventReceiver()
{
	logger->log("Deleting EventReceiver...", LL_INFO);

	this->dev = nullptr;

	logger->log("EventReceiver deleted", LL_INFO);
}

} // end namespace event

} // end namespace id

#include <memory>
#include <vector>
#include <string>

#include "txtLogger.h"
#include "eventManager.h"
#include "eventReceiver.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace event {

EventManager::EventManager()
: currentEvent(nullptr)
{
	logger->log("Creating EventManager...", LL_INFO);

	logger->log("EventManager created", LL_INFO);
}
EventManager::~EventManager()
{
	logger->log("Deleting EventManager...", LL_INFO);

	for (auto it = this->events.begin(); it != this->events.end(); ++it)
		delete *it;

	this->currentEvent = nullptr;

	logger->log("EventManager deleted", LL_INFO);
}
auto EventManager::createEventManager() -> std::unique_ptr<EventManager>
{
	auto* emgr = new (std::nothrow) EventManager();
	if (!emgr)
	{
		logger->log("Failed to create EventManager", LL_ERROR);
        SDL_assert(emgr);
	}
	return std::unique_ptr<EventManager>(emgr);
}
auto EventManager::useEventReceiver(std::string nameEvent) -> void
{
	for (auto it = this->events.begin(); it != this->events.end(); ++it)
	{
		if ((*it)->getName() == nameEvent)
		{
			this->currentEvent = *it;
			return;
		}
	}
}
auto EventManager::currentEventListener() -> void
{
	this->currentEvent->eventListener();
}
auto EventManager::addEventReceiver(EventReceiver* newEvent) -> void
{
	if (this->events.size() == 0)
		this->currentEvent = newEvent;

	this->events.push_back(newEvent);
}
auto EventManager::getEventFromName(std::string const& name) -> EventReceiver*
{
	for (auto it = this->events.begin(); it != this->events.end(); ++it)
	{
		if ((*it)->getName() == name)
			return *it;
	}
	return nullptr;
}

} // end namespace event

} // end namespace id

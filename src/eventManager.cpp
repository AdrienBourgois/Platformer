#include <memory>
#include <vector>
#include <string>

#include "logger.h"
#include "eventManager.h"
#include "eventReceiver.h"

namespace id {
namespace event {

EventManager::EventManager()
: currentEvent(nullptr)
{
	LOG(L_INFO ,"Creating EventManager...");

	LOG(L_INFO ,"EventManager created");
}
EventManager::~EventManager()
{
	LOG(L_INFO ,"Deleting EventManager...");

	for (auto it = this->events.begin(); it != this->events.end(); ++it)
		delete *it;

	this->currentEvent = nullptr;

	LOG(L_INFO ,"EventManager deleted");
}
auto EventManager::createEventManager() -> std::unique_ptr<EventManager>
{
	auto* emgr = new (std::nothrow) EventManager();
	if (!emgr)
	{
		LOG(L_ERROR ,"Failed to create EventManager");
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

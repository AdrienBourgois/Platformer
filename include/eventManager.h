#ifndef EVENT_MANAGER_H_INCLUDED
#define EVENT_MANAGER_H_INCLUDED

#include <memory>
#include <vector>
#include <string>

#include "eventReceiver.h"

namespace id {
namespace event {

class EventManager
{
public:
	~EventManager();
	EventManager(EventManager const&) = delete;
	EventManager(EventManager&&) = delete;
	auto operator=(EventManager const&) = delete;
	auto operator=(EventManager&&) = delete;


	static  auto createEventManager() -> std::unique_ptr<EventManager>;

			auto useEventReceiver(std::string nameEvent) -> void;
			auto currentEventListener() -> void;
			auto addEventReceiver(EventReceiver* newEvent) -> void;

			auto getEventFromName(std::string const& name) -> EventReceiver*;

private:
	EventManager();

	std::vector<EventReceiver*> events;
	EventReceiver* 				currentEvent;
};

} // namespace event
} // namespace id

#endif // EVENT_MANAGER_H_INCLUDED

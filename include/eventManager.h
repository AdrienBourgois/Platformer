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

	static auto createEventManager() -> std::unique_ptr<EventManager>;

	auto useEventReceiver(std::string nameEvent) -> void;
	auto currentEventListener() -> void;
	auto addEventReceiver(EventReceiver* newEvent) -> void;

private:
	EventManager();
	std::vector<EventReceiver*> events;
	EventReceiver* currentEvent;
};

} // end namespace event

} // end namespace id

#endif // EVENT_MANAGER_H_INCLUDED

#ifndef EVENT_RECEIVER_H_INCLUDED
#define EVENT_RECEIVER_H_INCLUDED

#include <string>

namespace id {

class Device;

namespace event {

class EventReceiver
{
public:
	EventReceiver(Device* dev, std::string name);
	virtual ~EventReceiver();
	EventReceiver(EventReceiver const&) = delete;
	EventReceiver(EventReceiver&&) = delete;
	auto operator=(EventReceiver const&) = delete;
	auto operator=(EventReceiver&&) = delete;

	virtual auto eventListener() -> void = 0;
	virtual auto getName() const -> std::string const& { return this->name; }

protected:
	Device* dev;
	std::string name;
};

} // namespace event
} // namespace id

#endif // EVENT_RECEIVER_H_INCLUDED

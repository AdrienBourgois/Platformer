#ifndef EVENT_RECEIVER_H_INCLUDED
#define EVENT_RECEIVER_H_INCLUDED

#include <string>

#include "device.h"

namespace id {
namespace event {

class EventReceiver
{
public:
	EventReceiver(Device* dev, std::string name);
	~EventReceiver();

	virtual auto eventListener() -> void = 0;
	auto getName() const -> std::string const& { return this->name; };

protected:
	Device* dev;
	std::string name;
};

} // end namespace event

} // end namespace id

#endif // EVENT_RECEIVER_H_INCLUDED

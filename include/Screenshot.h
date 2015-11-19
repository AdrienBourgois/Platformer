#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <SDL2/SDL.h>

namespace id {

class Device;

class Screenshot
{
public:
	static auto take(Device* dev) -> void;

private:
	static auto flipVert(SDL_Surface* sfc) -> SDL_Surface*;
};

} // namespace id

#endif

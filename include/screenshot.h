#ifndef SCREENSHOT_H_INCLUDED
#define SCREENSHOT_H_INCLUDED

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

#endif // SCREENSHOT_H_INCLUDED

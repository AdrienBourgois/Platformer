#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <SDL2/SDL.h>

namespace id {

class Window
{
public:
	~Window();

	Window(Window const&) 	= delete;
	Window(Window&&) 		= delete;
	Window&	operator=(Window const&) = delete;
	Window& operator=(Window&&)	= delete;

	static 	auto createWindow(unsigned int width = 400, unsigned int height = 400) 	->std::unique_ptr<Window>;

			auto getWindow() const 	-> SDL_Window* 		{ return _window; }
			auto getWidth() const 	-> unsigned int 	{ return _width; }
			auto getHeight() const 	-> unsigned int 	{ return _height; }
			auto swap() 			-> void;
			auto getSize(int* w, int* h) 				{ *w = _width; *h = _height; }
			auto getSDLWindow() const -> SDL_Window* 	{ return _window; }

private:
	Window(unsigned int width, unsigned int height);

	SDL_Window* 	_window;
	unsigned int 	_width;
	unsigned int 	_height;
};

} // namespace id

#endif

#include "window.h"
#include "logger.h"

namespace id {

Window::Window(unsigned int width, unsigned int height)
: _window(nullptr), _width(0), _height(0)
{
	LOG(L_DEBUG, "Creating window...");

	_width = width;
	_height = height;

	_window = SDL_CreateWindow("Model Viewer - OpenGL 4.2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_OPENGL);
	if (_window == nullptr)
	{
		LOG(L_ERROR, "Failed at initializing window in Window::createWindow(unsigned int, unsigned int)");
		SDL_assert(false);
	}

	LOG(L_DEBUG, "Window has been created.");
}

Window::~Window()
{
	LOG(L_DEBUG, "Deleting window...");
	SDL_DestroyWindow(_window);
	LOG(L_DEBUG, "Window has been deleted.");
}

auto 	Window::createWindow(unsigned int width, unsigned int height) 	-> std::unique_ptr<Window>
{
	auto* win = new(std::nothrow) Window(width, height);
	if (!win)
	{
		LOG(L_ERROR, "Failed at creating window in Window::createWindow(unsigned int, unsigned int)");
		SDL_assert(win && "ERROR window has not been created.");
	}

	return std::unique_ptr<Window>(win);
}

auto Window::swap() -> void
{
	SDL_GL_SwapWindow(_window);
}


} // namespace id

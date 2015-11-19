#include "window.h"
#include "txtLogger.h"

namespace {

	id::TXTLogger* logger = id::TXTLogger::getInstance();

} // namespace

namespace id {

Window::Window(unsigned int width, unsigned int height)
: _window(nullptr), _width(0), _height(0)
{
	logger->log("Creating window...", LL_DEBUG);

	_width = width;
	_height = height;

	_window = SDL_CreateWindow("Model Viewer - OpenGL 4.2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_OPENGL);
	if (_window == nullptr)
	{
		logger->log("Failed at initializing window in Window::createWindow(unsigned int, unsigned int)", LL_WARNING);
		SDL_assert(false);
	}

	logger->log("Window has been created.");
}

Window::~Window()
{
	logger->log("Deleting window...", LL_DEBUG);
	SDL_DestroyWindow(_window);
	logger->log("Window has been deleted.");
}

auto 	Window::createWindow(unsigned int width, unsigned int height) 	-> std::unique_ptr<Window>
{
	auto* win = new(std::nothrow) Window(width, height);
	if (!win)
	{
		logger->log("Failed at creating window in Window::createWindow(unsigned int, unsigned int)", LL_ERROR);
		SDL_assert(win && "ERROR window has not been created.");
	}

	return std::unique_ptr<Window>(win);
}

auto Window::swap() -> void
{
	SDL_GL_SwapWindow(_window);
}


} // namespace id

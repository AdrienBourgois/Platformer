#include <GL/glew.h>
#include <ctime>
#include <cstdlib>

#include "screenshot.h"
#include "device.h"
#include "window.h"
#include "txtLogger.h"

namespace {

id::TXTLogger* logger = id::TXTLogger::getInstance();

} // end namespace

namespace id {

auto Screenshot::take(Device* dev) -> void
{
	SDL_assert(dev);

	int window_width = dev->getWindow()->getWidth();
	int window_height = dev->getWindow()->getHeight();
	SDL_Surface * surf = SDL_CreateRGBSurface(SDL_SWSURFACE, window_width, window_height, 24, 0x000000FF, 0x0000FF00, 0x00FF0000, 0);
	if (surf == NULL) return;
	glReadPixels(0, 0, window_width, window_height, GL_RGB, GL_UNSIGNED_BYTE, surf->pixels);
	SDL_Surface * flip = flipVert(surf);
	if (flip == NULL) return;
	SDL_FreeSurface(surf);
	
	time_t t = time(0);
    struct tm* now = localtime(&t);
	int error_mkdir = std::system("mkdir SCREENS -p");
	(void)error_mkdir;
	
	std::string filename = "SCREENS/screenshot ";
	filename += std::to_string((now->tm_year + 1900));
	filename += "-";
	filename += std::to_string((now->tm_mon + 1));
	filename += "-";
	filename += std::to_string(now->tm_mday);
	filename += "_";
	filename += std::to_string(now->tm_hour);
    filename += ":";
    filename += std::to_string(now->tm_min);
    filename += ":";
    filename += std::to_string(now->tm_sec);
    filename += ".bmp";
	if (SDL_SaveBMP(flip, filename.c_str()))
	{
		std::string error = "Error while creating screenshot! (" + std::string(SDL_GetError()) + ")";
		logger->log(error.c_str(), LL_INFO);
	}
	else
	{
		std::string success = "Screenshot created ! (" + filename + ")";
		logger->log(success.c_str(), LL_INFO);
	}
	SDL_FreeSurface(flip);
	
}

auto Screenshot::flipVert(SDL_Surface* sfc) -> SDL_Surface*
{
	SDL_assert(sfc);

	SDL_Surface* result = SDL_CreateRGBSurface(sfc->flags, sfc->w, sfc->h,
		sfc->format->BytesPerPixel * 8, sfc->format->Rmask, sfc->format->Gmask,
		sfc->format->Bmask, sfc->format->Amask);
	if (result == NULL) return NULL;
 
	Uint8* pixels = (Uint8*) sfc->pixels;
	Uint8* rpixels = (Uint8*) result->pixels;
 
	Uint32 pitch = sfc->pitch;
	Uint32 pxlength = pitch*sfc->h;
 
	for(int line = 0; line < sfc->h; ++line) {
		Uint32 pos = line * pitch;
		memcpy(&rpixels[pos], &pixels[(pxlength-pos)-pitch], pitch);
	}
 
	return result;
}

} // namespace id

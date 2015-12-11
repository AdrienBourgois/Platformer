#include <iostream>

#include "texture.h"
#include "logger.h"

namespace id {

std::map<std::string, Texture*> Texture::textures;

auto Texture::addTexture(std::string file) -> Texture* 
{
	Texture* texture;

	if (textures.count(file) == 0)
		texture = new Texture(file);
	else
		texture = textures[file];

	if (!texture)
		LOG(L_WARNING, "Couldnt create texture in Texture::addTexture()");

	return texture;

}

Texture::Texture(std::string file)
:_id((GLuint)-1), _fileName(file)
{
	LOG(L_DEBUG, "Creating texture...");
	textures[_fileName] = this;
	LOG(L_DEBUG, "Texture has been created.");
}

Texture::~Texture()
{
	LOG(L_DEBUG, "Deleting texture...");
	glDeleteTextures(1, &_id);
	LOG(L_DEBUG, "Texture has been deleted.");
}

auto Texture::load() -> bool
{
	if (_fileName == "")
	{
		_id = 0;
		return true;
	}

	LOG(L_DEBUG, "loading texture...");

	SDL_Surface* imageSDL = IMG_Load(_fileName.c_str());
	
	if (!imageSDL)
	{
		LOG(L_WARNING, "Can't load texture file in Texture::load()");
		std::cout << SDL_GetError() << std::endl;
		return false;
	}	

	SDL_Surface* invImageSDL = inversPixels(imageSDL);
		SDL_FreeSurface(imageSDL);
	
	if (glIsTexture(_id) == GL_TRUE)
		glDeleteTextures(1, &_id);

	glGenTextures(1, &_id);

	glBindTexture(GL_TEXTURE_2D, _id);

	GLenum formatInterne(0);
	GLenum format(0);

	if (invImageSDL->format->BytesPerPixel == 3)
	{
		formatInterne = GL_RGB;

		if (invImageSDL->format->Rmask == 0xff)
			format = GL_RGB;
		else
			format = GL_BGR;	
	}

	else if (invImageSDL->format->BytesPerPixel == 4)
	{
		formatInterne = GL_RGBA;	
		
		if (invImageSDL->format->Rmask == 0xff)
			format = GL_RGBA;
		else
			format = GL_BGRA;
	}

	else
	{
		LOG(L_WARNING, "Format of texture file incorrect in Texture::load()");
		SDL_FreeSurface(invImageSDL);
		return false;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, formatInterne, invImageSDL->w, invImageSDL->h, 0, format, GL_UNSIGNED_BYTE, invImageSDL->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);	

	SDL_FreeSurface(invImageSDL);

	LOG(L_INFO, "Texture has been loaded.");

	return true;
}

auto Texture::inversPixels(SDL_Surface* imageSrc) -> SDL_Surface*
{
	SDL_assert(imageSrc);

	LOG(L_DEBUG, "inversing pixel from image texture...");
	
	SDL_Surface* imageInv = SDL_CreateRGBSurface(0, imageSrc->w, imageSrc->h, imageSrc->format->BitsPerPixel, imageSrc->format->Rmask, imageSrc->format->Gmask, imageSrc->format->Bmask, imageSrc->format->Amask);

	unsigned char* pixelSources  = static_cast<unsigned char*>(imageSrc->pixels);
	unsigned char* pixelInverses = static_cast<unsigned char*>(imageInv->pixels);

	for (int i = 0; i < imageSrc->h; ++i)
	{	
		for (int j = 0; j < imageSrc->w * imageSrc->format->BytesPerPixel; ++j)
		{	
			pixelInverses[(imageSrc->w * imageSrc->format->BytesPerPixel * (imageSrc->h - 1 - i)) + j] = pixelSources[(imageSrc->w * imageSrc->format->BytesPerPixel * i) + j];
		}
	}

	LOG(L_DEBUG, "Pixels has been inversed.");

return imageInv;
}

auto Texture::deleteTextures() -> void
{
	for (std::map<std::string, Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
	{
	        delete (*it).second;
	}

	textures.clear();
}

} // namespace id

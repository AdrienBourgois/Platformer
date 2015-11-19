#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>

namespace id{

class Texture
{
public:
	Texture() = default;
	~Texture();
	Texture(Texture const&) = delete;
	Texture(Texture&&) = delete;
	auto operator=(Texture const&) -> Texture& = delete;
	auto operator=(Texture&&) -> Texture& = delete;

	Texture(std::string file);

	static 	auto addTexture(std::string file) -> Texture*;

			auto getID() const 						-> GLuint 		{ return _id;		  	}
			auto setFileName(std::string newName) 	-> void 		{ _fileName = newName; 	}
			auto getFileName() const 				-> std::string 	{ return _fileName;		}

			auto load() 	-> bool;

			auto inversPixels(SDL_Surface* imageSrc)-> SDL_Surface*;
	static 	auto deleteTextures() 					-> void;
private:
	GLuint 		_id;
	std::string _fileName;
	
	static std::map<std::string, Texture*> textures;
};

} // namespace id

#endif // TEXTURE_H_INCLUDED

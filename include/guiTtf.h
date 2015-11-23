#ifndef GUITTF_H_INCLUDED
#define	GUITTF_H_INCLUDED

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <map>

namespace id{

class Texture;

class GuiTtf
{
public:
	GuiTtf();
	~GuiTtf();
	GuiTtf(GuiTtf const&) = delete;
	GuiTtf(GuiTtf&&) = delete;
	auto operator=(GuiTtf const&) -> GuiTtf = delete;
	auto operator=(GuiTtf&&) -> GuiTtf& = delete;
	
	auto addFont(std::string name) ->void;
	auto createText(std::string textureName, std::string text) ->void;
	auto pickColor(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255) -> void;

	auto setColorText(SDL_Color color) -> void {colorText = color;}

	auto getMapFonts() -> std::map<std::string,TTF_Font*>& {return mapFonts;}
	auto getMapSdl() -> std::map<std::string, SDL_Surface*>& {return mapSdlSurface;}
	auto getColorText()-> SDL_Color	{return colorText;}

//	GuiTtf(std::string fonts);

private:
	SDL_Color colorText;
	std::map<std::string, TTF_Font*> mapFonts;
	std::map<std::string, SDL_Surface*> mapSdlSurface;
};

}//id


#endif

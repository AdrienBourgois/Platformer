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
//	GuiTtf() default;
	~GuiTtf()
	GuiTtf(GuiTtf const&) = delete;
	GuiTtf(GuiTtf&&) = delete;
	auto operator=(GuiTtf const&) -> GuiTtf = delete;
	auto operator=(GuiTtf&&) -> GuiTtf& = delete;
	
	auto addfont(std::string name) ->void;

	GuiTtf(std::string fonts);

private:

	std::map<std::string, TTF_Font*> fonts;
	std::map<std::string, Texture*> texturesGui;
};

}//id


#endif

#include "guiTtf.h"
#include "texture.h"
#include <new>
#include "txtLogger.h"
#include "SDL2/SDL_ttf.h"


namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {

GuiTtf::GuiTtf()
{
	logger->log("Creating GuiTtf..."LL_DEBUG);

	TTF_Init();
	if(TTF_Init() == -1) {
		fprintf(stderr, "Error TTF_Init failed : %s\n", TTF_GetError());
	}
	logger->log("Creating GuiTtf finish..."LL_DEBUG);
}

GuiTtf::~GuiTtf()
{
	logger->log("Deleting GuiTtf..."LL_DEBUG);
	TTF_Quit();
	logger->log("Deleting GuiTtf finish..."LL_DEBUG);
}

auto addfont(std::string name) ->void;
{
	std::string path = "./assets/extra_fonts"
	std::string filepath = path + "/" + name;

	TTF_Font* font = TTF_OpenFont(filepath, 35);
	if(!font){
	std::cout << "Failled creating Font" << std::endl;
	}
	std::pair<std::string,TTF_Font*> fontmap (name,
}


}//id

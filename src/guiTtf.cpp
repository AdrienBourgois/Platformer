#include "guiTtf.h"
#include "texture.h"
#include <iostream>
#include <new>
#include "txtLogger.h"
#include "SDL2/SDL_ttf.h"
#include <utility>

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {

GuiTtf::GuiTtf()
{
	logger->log("Creating GuiTtf...");

	TTF_Init();
	if(TTF_Init() == -1)
	{
		fprintf(stderr, "Error TTF_Init failed : %s\n", TTF_GetError());
	}
	logger->log("Creating GuiTtf finish...");
}

GuiTtf::~GuiTtf()
{
	logger->log("Deleting GuiTtf...");
	TTF_Quit();
	logger->log("Deleting GuiTtf finish...");
}

auto GuiTtf::addFont(std::string name) ->void
{
	std::string path = "./assets/extra_fonts";
	std::string filepath = path + "/" + name;

	TTF_Font* font = TTF_OpenFont(filepath.c_str(), 35);
	if(!font)
	{
		std::cout << "Failled creating Font" << std::endl;
	}
	std::cout<< &font << std::endl;

	std::pair<std::string,TTF_Font*> pair;
	pair = std::make_pair(name,font);

//	std::cout<< pair.first << " " << pair.second << std::endl; 

	getMapFonts().insert(pair);

//(std::pair<std::string,TTF_Font*>(name,font));
//	std::cout<< getMapFonts().find(name)->second<<std::endl;
}

auto GuiTtf::pickColor(Uint8 r,Uint8 g,Uint8 b,Uint8 a)->void
{
	SDL_Color color = {r, g, b, a};
	setColorText(color);
//	std::cout<<  << std::endl;
}

auto GuiTtf::createText(std::string textureName, std::string text) ->void
{
	SDL_Color color = {0,0,0,255};
	std::cout<<"CreateText getMap "  <<getMapFonts().find("ProggyClean.tff")->second<<std::endl;
	SDL_Surface* surfText = TTF_RenderText_Blended(getMapFonts().find("ProggyClean.ttf")->second, text.c_str(), color);
	if(!surfText)
	{
		std::cout << "Failled creating Font" << std::endl;
	}
	std::pair::<std::string, SDL_Surface*> pair;
	pair = std::make_pair(textureName,surfText);
	getMapSdl().insert(pair);	
}
//auto GuiTtf::

}//id

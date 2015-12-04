#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <functional>

#include "txtLogger.h"
#include "guiManager.h"
#include "guiRect.h"
#include "guiButton.h"
#include "guiEventReceiver.h"
#include "guiMenu.h"

// debug
#include <iostream>
// end

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace gui {

GuiManager::GuiManager(int windowWidth, int windowHeight)
{
	logger->log("Creating GuiManager...", LL_INFO);

	if (TTF_Init() == -1)
		logger->log("Failed to initialisation TTF", LL_INFO);

	this->font = TTF_OpenFont("/usr/share/fonts/truetype/gentium-basic/GenBasB.ttf", 100);
	loadProgram("pos2d_color4");
	loadProgram("pos2d_tex2d_color4");
	this->guiEvt = new GuiEventReceiver(this);
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->camOrtho = {
		2.f/windowWidth, 0.f, 0.f, 0.f,
        0.f, 2.f/-windowHeight, 0.f, 0.f,
        0.f, 0.f, -2.f/(100.f - 0.1f), 0.f,
        0.f, 0.f, 0.f, 1.f
	};
	this->root = new GuiRect(this, nullptr, 0, 0, 0, 0, 0, false, nullptr);

	logger->log("GuiManager created", LL_INFO);
}
GuiManager::~GuiManager()
{
	logger->log("Deleting GuiManager...", LL_INFO);

	TTF_CloseFont(this->font);
	TTF_Quit();
	delete this->guiEvt;
	this->guiEvt = nullptr;
	for (auto&& rec : this->drawRect)
		delete rec;
	for (auto&& menu : this->listMenus)
		delete menu;
	this->drawRect.clear();
	delete this->root;
	this->root = nullptr;


	logger->log("GuiManager deleted", LL_INFO);
}
auto GuiManager::createGuiManager(int windowWidth, int windowHeight) -> std::unique_ptr<GuiManager>
{
	GuiManager* gui = new (std::nothrow) GuiManager(windowWidth, windowHeight);
	if (!gui)
	{
		logger->log("Failed at creating gui in GuiManager::createGuiManager()", LL_ERROR);
		SDL_assert(gui);
	}
	return std::unique_ptr<GuiManager>(gui);
}
auto GuiManager::render() -> void
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, (GLsizei)this->windowWidth, (GLsizei)this->windowHeight);

	for (std::vector<GuiRect*>::iterator it = this->drawRect.begin(); it != this->drawRect.end(); ++it)
	{
		if ((*it)->getVisible())
		{
			GLuint prgID = this->programGui.find((*it)->getShaderName())->second;
			glUseProgram(prgID);
			GLint projLoc = glGetUniformLocation(prgID, "proj");
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, this->camOrtho.data());
			if ((*it)->getType() == "button")
			{
				GuiButton* but = static_cast<GuiButton*>(*it);
				if (but->getText() != but->getNewText())
					changeText(but);

				GLint colorLoc = glGetUniformLocation(prgID, "color");
				maths::Vector4 color;
				if ((*it)->getPressed())
					color = {0.85f, 0.64f, 0.12f, 1.f};
				else
					color = (*it)->getColorBg();

				glUniform4f(colorLoc, color.val[0], color.val[1], color.val[2], color.val[3]);
			}

			glBindVertexArray((*it)->getVao());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*it)->getVbo());
			glBindTexture(GL_TEXTURE_2D, (*it)->getTexID());
			glDrawArrays(GL_TRIANGLES, 0, (*it)->getRect().size());
		}
	}

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
}
auto GuiManager::addRect(GuiRect* parent, float posX, float posY, float width, float height, int id, bool visible, maths::Vector4 color) -> void
{
	GuiRect* newRect = new GuiRect(this, parent, posX, posY, width, height, id, visible, nullptr);
	newRect->createElement(color);
	addToRender(newRect);
}
auto GuiManager::addButton(GuiRect* parent, float posX, float posY, float width, float height, int id, bool visible, maths::Vector4 colorBg, std::string const& text, maths::Vector4 colorText, std::function<void()> func) -> void
{
	GuiButton* newButton = new GuiButton(this, parent, posX, posY, width, height, id, visible, func);
	newButton->createElement(colorBg, text, colorText);
	addToRender(newButton);
}
auto GuiManager::addStaticText(GuiRect* parent, float posX, float posY, float width, float height, int id, bool visible, std::string const& text, maths::Vector4 colorText) -> void
{
	addButton(parent, posX, posY, width, height, id, visible, {0.f, 0.f, 0.f, 0.f}, text, colorText, nullptr);
	GuiRect* newStaticText = getElementFromID(id);
	newStaticText->setListenEvent(false);
}
auto GuiManager::addMenuTitleScreen() -> void
{
	GuiMenu* newMenu = new GuiMenu(this);
	newMenu->createMenuTitleScreen();
	this->listMenus.push_back(newMenu);
}
auto GuiManager::addMenuSettings() -> void
{
	GuiMenu* newMenu = new GuiMenu(this);
	newMenu->createMenuSettings();
	this->listMenus.push_back(newMenu);
}
auto GuiManager::addToRender(GuiRect* newRect) -> void
{
	this->drawRect.push_back(newRect);
}
auto GuiManager::loadProgram(std::string const& nameShader) -> void
{
	GLuint vsID = loadShader(nameShader, GL_VERTEX_SHADER);
	GLuint fsID = loadShader(nameShader, GL_FRAGMENT_SHADER);

	GLuint prgID = glCreateProgram();

	SDL_assert(prgID);

	glAttachShader(prgID, vsID);
	glAttachShader(prgID, fsID);
	glLinkProgram(prgID);

	GLint status;
    glGetProgramiv(prgID, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint len;
        glGetProgramiv(prgID, GL_INFO_LOG_LENGTH, &len);

        auto infolog = new char[len];
        glGetProgramInfoLog(prgID, len, &len, infolog);
		std::cerr << "Program link error : " << infolog << std::endl;
        SDL_assert(false);
    }
    else
    {
        logger->log("Program linkage success");
    }

	glDetachShader(prgID, vsID);
    glDetachShader(prgID, fsID);
    glDeleteShader(vsID);
    glDeleteShader(fsID);

	this->programGui.insert(std::pair<std::string, GLuint>(nameShader, prgID));
}
auto GuiManager::loadShader(std::string const& name, GLint shaderType) -> GLuint
{
	std::fstream file;
    std::string filePath;
    if (shaderType == GL_VERTEX_SHADER)
        filePath = "./assets/shaders/" + name + "_vs.glsl";
    else
        filePath = "./assets/shaders/" + name + "_fs.glsl";

    file.open(filePath, std::fstream::in | std::fstream::binary);
    SDL_assert(file.is_open());

	std::string sourceCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

	GLuint id = glCreateShader(shaderType);

    char const* cSource = sourceCode.c_str();
    int const sourceLen = sourceCode.size();
    glShaderSource(id, 1, &cSource, &sourceLen);

    glCompileShader(id);

	GLint status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);

        auto infolog = new char[len];
        glGetShaderInfoLog(id, len, &len, infolog);
		std::cerr << "Shader [" << filePath << "] compile error : " << infolog << std::endl;
        SDL_assert(false);
    }
    else
    {
		std::string str = "Shader [" + filePath + "] compilation success";
		logger->log(str);
	}
	
	return id;
}
auto GuiManager::loadText(std::string const& text, maths::Vector4 colorText) -> GLuint
{
	SDL_Color color = { (Uint8)(colorText.val[0]*255), (Uint8)(colorText.val[1]*255), (Uint8)(colorText.val[2]*255), (Uint8)(colorText.val[3]*255) };
	SDL_Surface* surf = TTF_RenderText_Blended(this->font, (" " + text + " ").c_str(), color);

	SDL_assert(surf);

	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);

	SDL_FreeSurface(surf);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}
auto GuiManager::changeText(GuiButton* button) -> void
{
	GLuint texID = button->getTexID();
	glDeleteTextures(1, &texID);
	button->setTexID(0);
	GLuint newTexID = loadText(button->getNewText(), button->getColorText());
	button->setTexID(newTexID);
	button->setText(button->getNewText());
}
auto GuiManager::getElementFromID(int id) -> GuiRect*
{
	for (std::vector<GuiRect*>::iterator it = this->drawRect.begin(); it != this->drawRect.end(); ++it)
	{
		if ((*it)->getID() == id)
			return *it;
	}
	return nullptr;
}
auto GuiManager::getPressedElement() -> GuiRect*
{
    for (auto it = this->drawRect.begin(); it !=  this->drawRect.end(); ++it)
	{
    	if ((*it)->getPressed())
			return *it;
	}
	return nullptr;
}

} // end namespace gui

} // end namespace id

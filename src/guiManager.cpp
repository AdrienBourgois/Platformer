#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <memory>

#include "guiManager.h"
#include "guiRect.h"
#include "guiEventReceiver.h"
#include "sceneManager.h"
#include "txtLogger.h"

#include <iostream>

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace gui {

GuiManager::GuiManager(int widthWin, int heightWin)
: widthWin(widthWin), heightWin(heightWin)
{
	if (TTF_Init() == -1)
	{
		logger->log("Initialisation of TFF failed", LL_ERROR);
	}
	this->guiEvt = new GuiEventReceiver(this);
	initGui();
}
GuiManager::~GuiManager()
{
	logger->log("Deleting Gui...", LL_INFO);

	for (std::vector<GuiRect*>::iterator it = this->renderedRect.begin(); it != this->renderedRect.end(); ++it)
	{
		delete *it;
	}

	TTF_Quit();

	logger->log("Gui deleted", LL_INFO);
}
auto GuiManager::initGui() -> void
{
	logger->log("Initialize Gui...", LL_INFO);

	this->prgIDRect = createProgram("pos2d_color4");
	this->prgIDButton = createProgram("gui");
	this->font = TTF_OpenFont("/usr/share/fonts/truetype/tlwg/Norasi.ttf", 100);

	logger->log("Gui initialized", LL_INFO);
}
auto GuiManager::renderGui() -> void
{
	glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glViewport(0, 0, (GLsizei)this->widthWin, (GLsizei)this->heightWin);

	const GLfloat camOrtho[16] = 
	{
		2.f/this->widthWin, 0.f, 0.f, 0.f,
		0.f, 2.f/-this->heightWin, 0.f, 0.f,
		0.f, 0.f, -2.f/(100.f - 0.1f), 0.f,
		0.f, 0.f, 0.f, 1.f
	};

	for (std::vector<GuiRect*>::iterator it = this->renderedRect.begin(); it != this->renderedRect.end(); ++it)
	{
		if ((*it)->getTexID() != 0)
		{
			glUseProgram(this->prgIDButton);
			GLint projLoc = glGetUniformLocation(this->prgIDButton, "proj");
			GLint colorLoc = glGetUniformLocation(this->prgIDButton, "back_color");
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, &camOrtho[0]);
			glUniform4f(colorLoc, (*it)->getColor().val[0], (*it)->getColor().val[1], (*it)->getColor().val[2], (*it)->getColor().val[3]);
		}
		else
		{
			glUseProgram(this->prgIDRect);
			GLint location = glGetUniformLocation(this->prgIDRect, "proj");
            glUniformMatrix4fv(location, 1, GL_FALSE, &camOrtho[0]);
		}

		glBindVertexArray((*it)->getVao());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*it)->getVbo());
		glBindTexture(GL_TEXTURE_2D, (*it)->getTexID());

		glDrawArrays(GL_TRIANGLES, 0, (*it)->getRect().size());
	}

	glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
	glDisable(GL_BLEND);
}
auto GuiManager::createShader(std::string const& name, GLint shaderType) -> GLuint
{
	std::fstream file;
    std::string filePath;
    if (shaderType == GL_VERTEX_SHADER)
    {   
        filePath = "./assets/shaders/" + name + "_vs.glsl";
    }
    else
    {
        filePath = "./assets/shaders/" + name + "_fs.glsl";
    }
    file.open(filePath, std::fstream::in | std::fstream::binary);
    SDL_assert(file.is_open());

    std::string source_code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    file.close();

	GLuint id = glCreateShader(shaderType);

	char const* c_source = source_code.c_str();
    int const source_len = source_code.size();

    glShaderSource(id, 1, &c_source, &source_len);

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
        std::cout << "Shader [" << filePath << "] compilation success" << std::endl;
    }

    return id;
}
auto GuiManager::createProgram(std::string const& pathShader) -> GLuint
{
	GLuint vs_id = createShader(pathShader, GL_VERTEX_SHADER);
    GLuint fs_id = createShader(pathShader, GL_FRAGMENT_SHADER);

    GLuint prg_id = glCreateProgram();

	SDL_assert(prg_id);

    glAttachShader(prg_id, vs_id);
    glAttachShader(prg_id, fs_id);

    glLinkProgram(prg_id);

	GLint status;
    glGetProgramiv(prg_id, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint len;
        glGetProgramiv(prg_id, GL_INFO_LOG_LENGTH, &len);

        auto infolog = new char[len];
        glGetProgramInfoLog(prg_id, len, &len, infolog);
        std::cerr << "Program link error : " << infolog << std::endl;
        SDL_assert(false);
    }
    else
    {
        std::cout << "Program linkage success" << std::endl;
    }

    glDetachShader(prg_id, vs_id);
    glDetachShader(prg_id, fs_id);
	glDeleteShader(vs_id);
    glDeleteShader(fs_id);

	return prg_id;
}
auto GuiManager::addToRender(GuiRect* rect) -> void
{
	this->renderedRect.push_back(rect);
}
auto GuiManager::addRect(maths::Vector2 pos, float width, float height, maths::Vector4 color) -> void
{
	logger->log("Creating Rect...", LL_INFO);

	GuiRect* newRect = new GuiRect();
	newRect->createRect(pos, width, height, color);
	addToRender(newRect);

	logger->log("Rect created", LL_INFO);
}
auto GuiManager::addButton(maths::Vector2 pos, float width, float height, maths::Vector4 colorBg, maths::Vector4 colorText, std::string const& text) -> void
{
	logger->log("Creating button...", LL_INFO);

	GuiRect* newButton = new GuiRect();
	newButton->createButton(this, pos, width, height, colorBg, colorText, text);
	addToRender(newButton);

	logger->log("Button created", LL_INFO);
}

} // end namespace gui

} // end namespace id

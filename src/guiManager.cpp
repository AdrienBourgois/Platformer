#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <memory>

#include "txtLogger.h"
#include "guiManager.h"
#include "guiRect.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace gui {

GuiManager::GuiManager(int windowWidth, int windowHeight)
{
	logger->log("Creating GuiManager...", LL_INFO);

	loadProgram("pos2d_color4");
	loadProgram("pos2d_tex2d_color4");
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->camOrtho = {
		2.f/windowWidth, 0.f, 0.f, 0.f,
        0.f, 2.f/-windowHeight, 0.f, 0.f,
        0.f, 0.f, -2.f/(100.f - 0.1f), 0.f,
        0.f, 0.f, 0.f, 1.f
	};
	this->root = new GuiRect(this, nullptr, 0, 0, 0, 0, 0, false);

	logger->log("GuiManager created", LL_INFO);
}
GuiManager::~GuiManager()
{
	logger->log("Deleting GuiManager...", LL_INFO);

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
			GLuint prgID = this->programGui.find(*(*it)->getShaderName())->second;
			glUseProgram(prgID);
			GLint projLoc = glGetUniformLocation(prgID, "proj");
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, this->camOrtho.data());

			glBindVertexArray((*it)->getVao());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*it)->getVbo());
			glDrawArrays(GL_TRIANGLES, 0, (*it)->getRect()->size());
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
	GuiRect* newRect = new GuiRect(this, parent, posX, posY, width, height, id, visible);
	newRect->createElement(color);
	addToRender(newRect);
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
        std::cout << "Program linkage success" << std::endl;
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
    {
        filePath = "./assets/shaders/" + name + "_vs.glsl";
    }
    else
    {
        filePath = "./assets/shaders/" + name + "_fs.glsl";
    }
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
        std::cout << "Shader [" << filePath << "] compilation success" << std::endl;
    }

	return id;
}

} // end namespace gui

} // end namespace id

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <vector>
#include <memory>

#include "guiManager.h"
#include "txtLogger.h"
#include "guiRect.h"
#include "sceneManager.h"

#include <iostream>

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace gui {

GuiManager::GuiManager(std::unique_ptr<Window>::pointer win, scene::SceneManager* scn)
: win(win), scn(scn)
{
	initGui();
	new GuiRect(this, { 1.f, 0.f, 0.f, 1.f });
}
GuiManager::~GuiManager()
{
	logger->log("Deleting Gui...", LL_INFO);

	logger->log("Gui deleted", LL_INFO);
}
auto GuiManager::initGui() -> void
{
	logger->log("Initialize Gui...", LL_INFO);

	this->prgID = createProgram("pos2_color4");

	logger->log("Gui initialized", LL_INFO);
}
auto GuiManager::renderGui() -> void
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	int widthWin = this->win->getWidth();
	int heightWin = this->win->getHeight();

	glViewport(0, 0, (GLsizei)widthWin, (GLsizei)heightWin);

	const GLfloat camOrtho[16] = 
	{
		2.f/widthWin, 0.f, 0.f, 0.f,
		0.f, 2.f/-heightWin, 0.f, 0.f,
		0.f, 0.f, -2.f/(100.f - 0.1f), 0.f,
		0.f, 0.f, 0.f, 1.f
	};

	glUseProgram(this->prgID);
	GLint location = glGetUniformLocation(this->prgID, "proj");
	glUniformMatrix4fv(location, 1, GL_FALSE, &camOrtho[0]);

	for (std::vector<GuiRect*>::iterator it = this->renderedRect.begin(); it != this->renderedRect.end(); ++it)
	{
		glBindVertexArray((*it)->getVao());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*it)->getVbo());

		glDrawArrays(GL_TRIANGLES, 0, (*it)->getRect().size());
	}

	glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
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


} // end namespace gui

} // end namespace id

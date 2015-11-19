#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <vector>

#include "guiManager.h"
#include "txtLogger.h"
#include "guiRect.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace gui {

GuiManager::~GuiManager()
{
	logger->log("Deleting Gui...", LL_INFO);

	logger->log("Gui deleted", LL_INFO);
}
auto GuiManager::initGui(SDL_Window* window) -> void
{
	logger->log("Initialize Gui...", LL_INFO);

	SDL_GetWindowSize(window, &this->widthWindow, &this->heightWindow);

	GLchar const* vertexShader =
	"#version 420\n"
	"uniform mat4 proj;\n"
	"in vec2 pos;\n"
	"in vec4 color;\n"
	"out vec4 tmpColor;\n"
	"void main(void)\n"
	"{\n"
	"	tmpColor = color;\n"
	"	gl_Position = proj * vec4(pos, 0.0, 1.0);\n"
	"}\n";

	GLchar const* fragmentShader =
	"#version 420\n"
	"in vec4 tmpColor;\n"
	"out vec4 outColor;\n"
	"void main(void)\n"
	"{\n"
	"	outColor = tmpColor;\n"
	"}\n";

	this->prgID = glCreateProgram();
	GLuint vsID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fsID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vsID, 1, &vertexShader, 0);
	glShaderSource(fsID, 1, &fragmentShader, 0);

	glCompileShader(vsID);
	glCompileShader(fsID);

	glAttachShader(this->prgID, vsID);
	glAttachShader(this->prgID, fsID);
	glLinkProgram(this->prgID);

	glDetachShader(this->prgID, vsID);
	glDeleteShader(vsID);
	glDetachShader(this->prgID, fsID);
	glDeleteShader(fsID);

	this->proj = glGetUniformLocation(this->prgID, "proj");
	GLuint posLoc = glGetUniformLocation(this->prgID, "pos");
	GLuint colorLoc = glGetUniformLocation(this->prgID, "color");

	glGenBuffers(1, &this->vbo);
	glGenVertexArrays(1, &this->vao);

	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glEnableVertexAttribArray(posLoc);
	glEnableVertexAttribArray(colorLoc);

	glVertexAttribPointer(posLoc, 2, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), nullptr);
	glVertexAttribPointer(colorLoc, 4, GL_UNSIGNED_BYTE, GL_TRUE, 6*sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	logger->log("Gui initialized", LL_INFO);
}
auto GuiManager::renderGui() -> void
{
	GLint activePrg, activeTex;
	glGetIntegerv(GL_CURRENT_PROGRAM, &activePrg);
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &activeTex);

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	float const orthoProj[4][4] =
	{
		{ 2.f/this->widthWindow, 0.f, 0.f, 0.f },
		{ 0.f, 2.f/-this->heightWindow, 0.f, 0.f },
		{ 0.f, 0.f, -1.f, 0.f },
		{ -1.f, 1.f, 0.f, 1.f }
	};

	glUseProgram(this->prgID);
	glUniformMatrix4fv(this->proj, 1, GL_FALSE, &orthoProj[0][0]);
	glBindVertexArray(this->vao);

	for (std::vector<GuiRect*>::iterator it = this->renderedRect.begin(); it != this->renderedRect.end(); ++it)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
	}
}
auto GuiManager::addToRender(GuiRect* rect) -> void
{
	this->renderedRect.push_back(rect);
}
GuiManager::GuiManager()
{
}

} // end namespace gui

} // end namespace id

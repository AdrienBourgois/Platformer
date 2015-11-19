#include "Shaders.h"
#include "TxtLogger.h"
#include <SDL2/SDL.h>
#include <iostream>

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
} // namespace

namespace id {

auto Shaders::createShaders() -> std::unique_ptr<Shaders>
{
	logger->log("Creating Shaders...");

	auto* shaders = new(std::nothrow) Shaders;
	if (!shaders)
	{
		logger->log("Failed at creating shaders in Shaders::createShaders()", LL_ERROR);
		SDL_assert(shaders && "ERROR shaders has not been created.");
	}

	logger->log("Shaders constructed", LL_INFO);

	return std::unique_ptr<Shaders>(shaders);
}

Shaders::~Shaders()
{
	logger->log("Deleting Shaders...", LL_DEBUG);

	for (auto&& prg : _program_loaded)
		glDeleteProgram(prg.second);

	logger->log("Shaders has been deleted.");
}

auto Shaders::loadShader(std::string const& name, GLint shader_type) -> GLuint
{
	// ouvrir le fichier avec fstream
	std::string filename = "./assets/shaders/";
	filename += name;
	if (shader_type == GL_VERTEX_SHADER)
		filename += "_vs.glsl";
	else
		filename += "_fs.glsl";
	std::ifstream file(filename);
	
	std::string source_code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	
	if (shader_type == GL_VERTEX_SHADER)
		_shaders_data[name].vertex = source_code;
	else
		_shaders_data[name].fragment = source_code;
	
	file.close();

	auto id = glCreateShader(shader_type);

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
		std::cerr << "Shader [" << filename << "] compilation error : " << infolog << std::endl;
		delete infolog;
		infolog = nullptr;
		SDL_assert(false);
	}
	else
	{
		std::string str = "Shader [" + filename + "] compilation success"; 
		logger->log(str.c_str());
	}
	return id;
}

auto Shaders::createProgram(GLuint vs_id, GLuint fs_id) -> GLuint
{
	auto prg_id = glCreateProgram();
	if (!prg_id)
	{
		logger->log("Failed at creating prg_id in Shaders::loadProgram(std::string const&)", LL_ERROR);
		SDL_assert(prg_id && "ERROR prg_id has not been created.");
	}

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
		logger->log("Program link error : ", LL_ERROR);
		logger->log(infolog, LL_ERROR);
		delete infolog;
		infolog = nullptr;
		SDL_assert(false);
	}
	else
		logger->log("Program link compilation success", LL_INFO);

	glDetachShader(prg_id, vs_id);
	glDetachShader(prg_id, fs_id);
	glDeleteShader(vs_id);
	glDeleteShader(fs_id);

	return prg_id;
}

auto Shaders::loadProgram(std::string const& shader) -> void
{
	if (_program_loaded.count(shader) == 0)
	{
		auto vs_id = loadShader(shader, GL_VERTEX_SHADER);
		auto fs_id = loadShader(shader, GL_FRAGMENT_SHADER);
		auto prg_id = createProgram(vs_id, fs_id);

		_program_loaded.insert(std::pair<std::string, GLuint>(shader, prg_id));
	}
	else
			_program_loaded[shader];
}

} // namespace id

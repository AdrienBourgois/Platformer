#ifndef SHADERS_H
#define SHADERS_H

#include <memory>
#include <GL/glew.h>
#include <string>
#include <map>

namespace id {

struct shader_data
{
	std::string fragment;
	std::string vertex;
};

class Shaders
{
public:
	~Shaders();
	Shaders(Shaders const&) = delete;
	Shaders(Shaders&&) = delete;
	Shaders& operator=(Shaders const&) = delete;
	Shaders& operator=(Shaders&&) = delete;

	static 	auto createShaders() 					-> std::unique_ptr<Shaders>;

			auto loadProgram(std::string const&) 	-> void;

			auto getPrg(std::string key) 			-> GLuint 		{ return _program_loaded.find(key)->second; }
	
			auto* getShaderData(std::string name) { return &_shaders_data[name]; }

private:
	Shaders() = default;

	auto loadShader(std::string const&, GLint) 	-> GLuint;
	auto createProgram(GLuint, GLuint) 			-> GLuint;
	
	std::map< std::string, shader_data > _shaders_data;

	std::map<std::string, GLuint> 		_program_loaded;
};

} // namespace id

#endif

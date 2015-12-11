#ifndef DRIVER_H_INCLUDED
#define DRIVER_H_INCLUDED

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <string>
#include <memory>

#include "maths/matrix.h"

namespace id
{

class Device;
class Window;
class Shaders;

namespace scene{
	class MeshSceneNode;
} // namespace scene

namespace video {

class Driver
{
public:
	~Driver();
	Driver(Driver const&) = delete;
	Driver(Driver&&) = delete;
	Driver& operator=(Driver const&) = delete;
	Driver& operator=(Driver&&) = delete;
			
	static 	auto createDriver(Window* window) 	-> std::unique_ptr<Driver>;

			auto setAttribute(int, int, int, int, int, int, int) -> void;
			auto initGlew() -> void;
			auto backgroundColor(float red = 0.f, float green = 0.f, float blue = 0.f, float alpha = 1.f) -> void;

			auto useProgram(GLuint prg) -> void;
			auto deleteProgram(GLuint prg) -> void;

			auto clear() -> void;
			auto genVertexObject(int size, float* vertices, GLuint* vbo, GLuint* vao) -> void;
			auto deleteBuffer(GLuint* vbo) -> void;
			auto draw(scene::MeshSceneNode* meshNode) -> void;
			auto AttachUniformMatrix4(GLuint prg_id, std::string var_name, maths::Matrix4 mat) -> void;

			auto LoadTexture(std::string const& path, GLenum format) -> GLuint;
			auto ChangeTexture(GLuint index) -> void;

			auto getShader() const -> Shaders* { return _shaders.get(); }


					
private:
	Driver(Window* window);
	
	SDL_GLContext 				_context;
	std::unique_ptr<Shaders> 	_shaders;

};

} // namespace video
} // namespace id
#endif // DRIVER_H_INCLUDED

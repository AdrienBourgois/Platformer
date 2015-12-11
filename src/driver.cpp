#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include "driver.h"
#include "device.h"
#include "window.h"
#include "shaders.h"
#include "meshSceneNode.h"
#include "mesh.h"
#include "logger.h"

namespace id
{

namespace video {

Driver::Driver(Window* window)
:_context(NULL), _shaders(nullptr)
{
	LOG(L_INFO,"Creating Driver...");

	_context = SDL_GL_CreateContext(window->getWindow());
	if (_context == NULL)
	{
		LOG(L_INFO, "Failed at creating context in Driver::createDriver(Window*)");
		SDL_assert(false);
	}

	setAttribute(4, 2, 8, 8, 8, 24, 1);
	
	initGlew();

	_shaders = Shaders::createShaders();

	backgroundColor(0.2f,0.2f,0.2f,1.f);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	
	LOG(L_INFO,"Driver has been created.");
}

Driver::~Driver()
{
	LOG(L_DEBUG,"Driver deleting...");

	_shaders.reset(nullptr);

	SDL_GL_DeleteContext(this->_context);

	LOG(L_INFO,"Driver deleted");
}

auto Driver::createDriver(Window* window) -> std::unique_ptr<Driver>
{
	SDL_assert(window);

	auto* drv = new(std::nothrow) Driver(window);
	if (!drv)
	{
		LOG(L_INFO,"Failed at creating driver in Driver::createDriver(Window*)");
		SDL_assert(drv && "ERROR driver has not been created.");
	}

	return std::unique_ptr<Driver>(drv);
}

auto Driver::setAttribute(int major, int minor, int red, int green, int blue, int depth, int buffer) -> void
{
	SDL_assert(major && minor && red && green && blue && depth && buffer);

	LOG(L_INFO,"Setting attribute of driver (SDL_GL_SetAttribute)...");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, red);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, green);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, blue);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, depth);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, buffer);

	LOG(L_INFO,"Attribute has been setted.");
}

auto Driver::initGlew() -> void
{
	LOG(L_INFO,"Initializing glew...");

	glewExperimental = GL_TRUE;
    auto status = glewInit();
    SDL_assert(status == GLEW_OK);

	LOG(L_INFO,"Glew has been initialized.");
}

auto Driver::backgroundColor(float red, float green, float blue, float alpha) -> void
{
	LOG(L_INFO,"Initializing Background Color...");

	glClearColor(red, green, blue, alpha);

	LOG(L_INFO,"Background Color has been initialized.");
}

auto Driver::clear() -> void
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

auto Driver::genVertexObject(int size, float* vertices, GLuint* vbo, GLuint* vao) -> void
{
    glGenVertexArrays(1, vao);
    glGenBuffers(1, vbo);
    
    
    glBindVertexArray(*vao);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_READ);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), nullptr);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)(3*sizeof(GLfloat) + 2*sizeof(GLfloat)));
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
	
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
auto Driver::draw(scene::MeshSceneNode* meshNode) -> void
{

	for (auto& v : meshNode->getMesh()->getGroups())
	{
		Material* material = meshNode->getMesh()->getMaterial();
		if (material)
		{	
			Texture* texture = material->getTextureFromMTL(v.second.mtl);
			unsigned int texture_id = 0;
			if (texture)
				texture_id = texture->getID();
			ChangeTexture(texture_id);
		}
		glBindVertexArray(v.second.vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, v.second.vbo);
		glDrawArrays(GL_TRIANGLES, 0, v.second.dataSize());
	}
}

auto Driver::useProgram(GLuint prg) -> void
{
	glUseProgram(prg);
}

auto Driver::deleteProgram(GLuint prg) -> void
{
	glDeleteProgram(prg);
}

auto Driver::deleteBuffer(GLuint* vbo) -> void
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, vbo);
}

auto Driver::AttachUniformMatrix4(GLuint prg_id, std::string var_name, maths::Matrix4 mat) -> void
{
	auto var_loc = glGetUniformLocation(prg_id, var_name.c_str());
    glUniformMatrix4fv(var_loc, 1, GL_TRUE, mat.val.data());
}

auto Driver::LoadTexture(std::string const& path, GLenum format) -> GLuint
{
	SDL_Surface* surf = IMG_Load(path.c_str());

	SDL_assert(surf);
	GLuint tex_id;
	glGenTextures(1, &tex_id);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, format, GL_UNSIGNED_BYTE, surf->pixels);

	SDL_FreeSurface(surf);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	

	glBindTexture(GL_TEXTURE_2D, 0);
	return tex_id;
}

auto Driver::ChangeTexture(GLuint index) -> void
{
	glBindTexture(GL_TEXTURE_2D, index);
}


} // namespace video
} // namespace id

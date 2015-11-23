#ifndef DEVICE_H_INCLUDED
#define DEVICE_H_INCLUDED

#include <GL/glew.h> 
#include <SDL2/SDL.h> 
#include <memory>

namespace id {

namespace video{
	class Driver;
} // namespace video

namespace scene{
	class SceneManager;
} // namespace scene

class Window;

namespace gui {
	class GuiManager;
} // end namespace gui

class Device
{
public:
		~Device();
		Device(Device const&) = delete;
		Device(Device&&) = delete;
		Device& operator=(Device const&) = delete;	
		Device& operator=(Device&&) = delete;

	static 	auto create() 					-> std::unique_ptr<Device>;

			auto getWindow() const 			-> Window*		 				{ return _window.get();	}
			auto getDriver() const 			-> video::Driver* 				{ return _driver.get();	}
			auto getSceneManager() const 	-> scene::SceneManager* 		{ return _sceneManager;	}
			auto getGui() const				-> gui::GuiManager*				{ return _gui; };
			auto setSceneManager(scene::SceneManager* smgr) -> void 		{ _sceneManager = smgr;	}

			auto run() 	-> bool;
private:
	Device();

	std::unique_ptr<video::Driver> 	_driver;
	std::unique_ptr<Window>			_window;
	scene::SceneManager*			_sceneManager;
	gui::GuiManager* 				_gui;
};





} // namespace id



#endif // DEVICE_H_INCLUDED 

#ifndef DEVICE_H_INCLUDED
#define DEVICE_H_INCLUDED

#include <GL/glew.h> 
#include <SDL2/SDL.h> 
#include <chrono>
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

namespace event {
	class EventManager;
} // end namespace event

class LevelEditor;
class DebugLogger;
class Device
{
public:
	~Device();
	Device(Device const&) = delete;
	Device(Device&&) = delete;
	Device& operator=(Device const&) = delete;	
	Device& operator=(Device&&) = delete;

	static 	auto create() -> std::unique_ptr<Device>;

	auto getWindow() const -> Window*			{ return _window.get();}
	auto getDriver() const -> video::Driver*		{ return _driver.get();}
	auto getSceneManager() const -> scene::SceneManager*	{ return _sceneManager;}
	auto getGui() const -> gui::GuiManager*			{ return _gui.get(); };
	auto getEventManager() const -> event::EventManager*	{ return _eventManager.get(); };
	auto getLevelEditor() const -> LevelEditor* { return this->levelEditor; }
	auto getDeltaTime() const -> float			{ return this->deltaTime; };

	auto setSceneManager(scene::SceneManager* smgr) -> void { _sceneManager = smgr;	}
	auto setDeltaTime(float deltaTime) -> void { this->deltaTime = deltaTime; };

	auto run() 	-> bool;
	auto close() -> void;

private:
	Device();

	std::unique_ptr<video::Driver> 	_driver;
	std::unique_ptr<Window>			_window;
	scene::SceneManager*			_sceneManager;
	std::unique_ptr<gui::GuiManager> _gui;
	std::unique_ptr<event::EventManager> _eventManager;
	LevelEditor*	levelEditor;
	DebugLogger*	debugLogger;
	bool running;
	float deltaTime;
};

} // namespace id

#endif // DEVICE_H_INCLUDED 

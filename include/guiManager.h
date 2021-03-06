#ifndef GUI_MANAGER_H_INCLUDED
#define GUI_MANAGER_H_INCLUDED

#include <GL/glew.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <vector>
#include <map>
#include <string>
#include <functional>


namespace id {

class Device;

namespace maths {
	class Vector4;
} // namespace maths

namespace gui {

class GuiRect;
class GuiButton;
class GuiEventReceiver;
class GuiMenu;

class GuiManager
{
public:
	~GuiManager();
	GuiManager(GuiManager const&) = delete;
	GuiManager(GuiManager&&) = delete;
	auto operator =(GuiManager const&) -> GuiManager& = delete;
	auto operator =(GuiManager&&) -> GuiManager& = delete;

	static 	auto createGuiManager(Device* dev, int windowWidth, int windowHeight) -> std::unique_ptr<GuiManager>;
			auto render() -> void;

			auto addRect(GuiRect* parent, float posX, float posY, float width, float height, int id, bool visible, maths::Vector4 color) -> void;
			auto addButton(GuiRect* parent, float posX, float posY, float width, float height, int id, bool visible, maths::Vector4 colorBg, std::string const& text, maths::Vector4 colorText, std::function<void()> func) -> void;
			auto addStaticText(GuiRect* parent, float posX, float posY, float width, float height, int id, bool visible, std::string const& text, maths::Vector4 colorText) -> void;
			auto addMenuTitleScreen(std::function<void()> funcQuit) -> void;
			auto addMenuSettings() -> void;
			auto addMenuResolution() -> void;

			auto addToRender(GuiRect* newRect) -> void;
			auto addMenu(GuiMenu* newMenu) -> void;
			auto removeToRender(GuiRect* rectToDelete) -> void;
			auto removeMenu(GuiMenu* menuToDelete) -> void;
			auto loadProgram(std::string const& nameShader) -> void;
			auto loadShader(std::string const& name, GLint shaderType) -> GLuint;
			auto loadText(std::string const& text, maths::Vector4 colorText) -> GLuint;
			auto changeText(GuiButton* button) -> void;
			auto getElementFromID(int id) -> GuiRect*;
			auto getMenuFromID(int id) -> GuiMenu*;
			auto getPressedElement() -> GuiRect*;

			auto getDrawRect() const -> std::vector<GuiRect*> const& 	{ return this->drawRect; 	 }
			auto getListMenus() const -> std::vector<GuiMenu*> const& 	{ return this->listMenus; 	 }
			auto getGuiEvt() const -> GuiEventReceiver* 				{ return this->guiEvt; 		 }
			auto getDevice() const -> Device* 							{ return this->dev; 		 }
			auto getWidth() const -> int 								{ return this->windowWidth;  }
			auto getHeight() const -> int 								{ return this->windowHeight; }
			auto getRoot() const -> GuiRect* 							{ return this->root; 		 }

private:
	GuiManager(Device* dev, int windowWidth, int windowHeight);
	std::vector<GuiRect*> drawRect;
	std::vector<GuiMenu*> listMenus;
	std::map<std::string, GLuint> programGui;
	GuiEventReceiver* guiEvt;

	Device* dev;
	int windowWidth, windowHeight;
	std::array<float, 16> camOrtho;
	TTF_Font* font;
	GuiRect* root;
};

} // namespace gui
} // namespace id

#endif // GUI_MANAGER_H_INCLUDED

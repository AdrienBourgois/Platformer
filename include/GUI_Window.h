#ifndef GUI_WINDOW_H
#define GUI_WINDOW_H

namespace id {

class GUI_Window
{
public:
	GUI_Window(bool visible = true);
	virtual ~GUI_Window() = default;
	
	virtual auto setVisible(bool v) -> void 	{ _visible = v; }

protected:
		bool _visible;
};

} // namespace id

#endif

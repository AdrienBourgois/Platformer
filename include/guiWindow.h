#ifndef GUI_WINDOW_H_INCLUDED
#define GUI_WINDOW_H_INCLUDED

namespace id {

class GUI_Window
{
public:
	GUI_Window(bool visible = true);
	virtual ~GUI_Window() = default;
	GUI_Window(GUI_Window const&) = delete;
	GUI_Window(GUI_Window&&) = delete;
	auto operator=(GUI_Window const&) -> GUI_Window& = delete;
	auto operator=(GUI_Window&&) -> GUI_Window& = delete;

	virtual auto setVisible(bool v) -> void 	{ _visible = v; 	}
	virtual auto getVisible()-> bool 			{ return _visible;	}

protected:
		bool _visible;
};

} // namespace id

#endif // GUI_WINDOW_H_INCLUDED

#ifndef GUI_WINDOW_H_INCLUDED
#define GUI_WINDOW_H_INCLUDED

namespace id {

class GUI_Window
{
public:
	GUI_Window(bool visible = true);
	virtual ~GUI_Window() = default;
	
	virtual auto setVisible(bool v) -> void 	{ _visible = v; }
	virtual auto getVisible()-> bool {return _visible;}
protected:
		bool _visible;
};

} // namespace id

#endif // GUI_WINDOW_H_INCLUDED

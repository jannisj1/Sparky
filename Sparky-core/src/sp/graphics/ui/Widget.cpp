#include "sp/sp.h"
#include "Widget.h"

namespace sp { namespace graphics { namespace ui {

	bool Widget::OnMousePressed(events::MousePressedEvent& e)
	{
		return false;
	}

	bool Widget::OnMouseReleased(events::MouseReleasedEvent& e)
	{
		return false;
	}

	bool Widget::OnMouseMoved(events::MouseMovedEvent& e)
	{
		return false;
	}

	void Widget::OnUpdate()
	{
	}

	void Widget::OnRender(Renderer2D& renderer)
	{
	}

} } }
#include "sp/sp.h"
#include "Widget.h"

namespace sp { namespace graphics { namespace ui {

	Widget::Widget(css::CSSManager *cssManager, tinyxml2::XMLElement *domElement)
		: m_CSSManager(cssManager), m_DOMElement(domElement)
	{
		m_CSSInfo.Name = domElement->Name();
		
		if (domElement->Attribute("class"))
			m_CSSInfo.Classes = SplitString(domElement->Attribute("class"), ' ');

		if (domElement->Attribute("id"))
			m_CSSInfo.ID = domElement->Attribute("id");
	}

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
		if (m_Bounds.Contains(e.GetPosition()))
		{
			m_CSSInfo.State = css::HOVER;
		}
		else
		{
			m_CSSInfo.State = css::IDLE;
		}

		for (auto c : m_Children)
		{
			c->OnMouseMoved(e);
		}

		return false;
	}

	void Widget::OnUpdate(const css::CSSBounds& space)
	{

	}

	void Widget::OnRender(Renderer2D& renderer)
	{
	}

} } }
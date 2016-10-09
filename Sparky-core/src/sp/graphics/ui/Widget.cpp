#include "sp/sp.h"
#include "Widget.h"

namespace sp { namespace graphics { namespace ui {

	ui::Widget *Widget::FocusedWidget;

	Widget::Widget(Widget *parent, css::CSSManager *cssManager, tinyxml2::XMLElement *domElement, bool activatable, bool focusable)
		: m_CSSManager(cssManager), m_DOMElement(domElement), m_Activatable(activatable), m_Focusable(focusable)
	{
		m_CSSInfo.Name = domElement->Name();
		
		if (domElement->Attribute("class"))
			m_CSSInfo.Classes = SplitString(domElement->Attribute("class"), ' ');

		if (domElement->Attribute("id"))
			m_CSSInfo.ID = domElement->Attribute("id");

		if (parent)
		{
			m_CSSInfo.Parent = &parent->GetCSSInfo();
		}
	}

	bool Widget::OnMouseMoved(events::MouseMovedEvent& e)
	{
		if (m_Bounds.Contains(e.GetPosition()))
		{
			if (m_CSSInfo.State == css::IDLE) m_CSSInfo.State = css::HOVER;
		}
		else
		{
			if (m_CSSInfo.State == css::HOVER) m_CSSInfo.State = css::IDLE;
		}

		for (auto c : m_Children)
		{
			c->OnMouseMoved(e);
		}

		return false;
	}

	void Widget::OnRender(Renderer2D& renderer)
	{

	}

	bool Widget::OnMousePressed(events::MousePressedEvent& e)
	{
		if (m_Bounds.Contains(e.GetPosition()))
		{
			if (FocusedWidget)
			{
				FocusedWidget->GetCSSInfo().State = css::IDLE;
				FocusedWidget = nullptr;
			}

			if (m_Activatable)
			{
				m_CSSInfo.State = css::ACTIVE;
				return true;
			}
		}

		for (auto c : m_Children)
		{
			if (c->OnMousePressed(e)) return true;
		}

		return false;
	}

	bool Widget::OnMouseReleased(events::MouseReleasedEvent& e)
	{
		if (m_CSSInfo.State == css::ACTIVE)
		{
			if (m_Bounds.Contains(e.GetPosition()))
			{
				if (m_Focusable)
				{
					m_CSSInfo.State = css::FOCUSED;
					FocusedWidget = this;
				}
				else m_CSSInfo.State = css::HOVER;
			}
			else
			{
				m_CSSInfo.State = css::IDLE;
			}
		}

		for (auto c : m_Children)
		{
			if (c->OnMouseReleased(e)) return true;
		}

		return false;
	}

} } }
#include "sp/sp.h"
#include "Widget.h"

namespace sp { namespace graphics { namespace ui {

	ui::Widget *Widget::FocusedWidget;

	Widget::Widget(Widget *parent, css::CSSManager *cssManager, tinyxml2::XMLElement *domElement, bool activatable, bool focusable)
		: m_Parent(parent), m_CSSManager(cssManager), m_DOMElement(domElement), m_Activatable(activatable), m_Focusable(focusable)
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

		m_ChildrenWrapSize.x = 0;
		m_ChildrenWrapSize.y = 0;
	}

	void Widget::MoveBy(const maths::vec2& delta)
	{
		m_OuterBounds.position += delta;
		m_InnerBounds.position += delta;
		m_Bounds.position += delta;
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

	void Widget::DrawBackgroundAndBorder(Renderer2D& renderer)
	{
		css::CSSBounds tempBounds;

		// Background
		tempBounds.x = m_Bounds.x + GetPixelWidth(css::BORDER_LEFT_WIDTH);
		tempBounds.y = m_Bounds.y + GetPixelHeight(css::BORDER_TOP_WIDTH);

		tempBounds.width = m_Bounds.width - (tempBounds.x - m_Bounds.x)/* (same as BORDER_LEFT_WIDTH) */ - GetPixelWidth(css::BORDER_RIGHT_WIDTH);
		tempBounds.height = m_Bounds.height - (tempBounds.y - m_Bounds.y)/* (same as BORDER_TOP_WIDTH) */ - GetPixelHeight(css::BORDER_BOTTOM_WIDTH);

		renderer.FillRect(tempBounds.ToRectangle(), Get<css::CSSColor>(css::BACKGROUND_COLOR)->GetColor());
		
		// Top Border
		if (Get<css::CSSBorderStyle>(css::BORDER_TOP_STYLE)->GetBorderStyle() != css::CSSBorderStyle::NONE)
		{
			tempBounds.x = m_Bounds.x;
			tempBounds.y = m_Bounds.y;

			tempBounds.width = m_Bounds.width;
			tempBounds.height = GetPixelHeight(css::BORDER_TOP_WIDTH);

			renderer.FillRect(tempBounds.ToRectangle(), Get<css::CSSColor>(css::BORDER_TOP_COLOR)->GetColor());
		}

		// Right Border
		if (Get<css::CSSBorderStyle>(css::BORDER_RIGHT_STYLE)->GetBorderStyle() != css::CSSBorderStyle::NONE)
		{
			tempBounds.x = m_Bounds.x + m_Bounds.width - GetPixelWidth(css::BORDER_RIGHT_WIDTH);
			tempBounds.width = GetPixelWidth(css::BORDER_RIGHT_WIDTH);
			tempBounds.height = m_Bounds.height;

			renderer.FillRect(tempBounds.ToRectangle(), Get<css::CSSColor>(css::BORDER_RIGHT_COLOR)->GetColor());
		}

		// Bottom Border
		if (Get<css::CSSBorderStyle>(css::BORDER_BOTTOM_STYLE)->GetBorderStyle() != css::CSSBorderStyle::NONE)
		{
			tempBounds.x = m_Bounds.x;
			tempBounds.y = m_Bounds.y + m_Bounds.height - GetPixelHeight(css::BORDER_BOTTOM_WIDTH);
			tempBounds.width = m_Bounds.width;
			tempBounds.height = GetPixelHeight(css::BORDER_BOTTOM_WIDTH);

			renderer.FillRect(tempBounds.ToRectangle(), Get<css::CSSColor>(css::BORDER_BOTTOM_COLOR)->GetColor());
		}

		// Left Border
		if (Get<css::CSSBorderStyle>(css::BORDER_LEFT_STYLE)->GetBorderStyle() != css::CSSBorderStyle::NONE)
		{
			tempBounds.x = m_Bounds.x;
			tempBounds.y = m_Bounds.y;
			tempBounds.width = GetPixelWidth(css::BORDER_LEFT_WIDTH);
			tempBounds.height = m_Bounds.height;

			renderer.FillRect(tempBounds.ToRectangle(), Get<css::CSSColor>(css::BORDER_LEFT_COLOR)->GetColor());
		}
	}

	css::CSSBounds Widget::PositionInsideParent(const css::CSSBounds& space, const css::CSSBounds& initialSpace)
	{
		using namespace css;

		bool wrap = m_Parent->Get<CSSFlowDirection>(FLOW_CHILDREN)->IsWrapping();
		CSSFlowDirection::FlowDirection fd = m_Parent->Get<CSSFlowDirection>(FLOW_CHILDREN)->GetDirection();

		CSSBounds ret = space;

		if (fd == CSSFlowDirection::RIGHT)
		{
			if (wrap && ret.width < m_OuterBounds.width)
			{
				ret.width = initialSpace.width;
				ret.height -= m_Parent->m_ChildrenWrapSize.y;
				ret.y += m_Parent->m_ChildrenWrapSize.y;
				ret.x = initialSpace.x;

				MoveBy(maths::vec2(-(space.x - initialSpace.x), m_Parent->m_ChildrenWrapSize.y));

				m_Parent->m_ChildrenWrapSize.x = 0;
				m_Parent->m_ChildrenWrapSize.y = 0;
			}

			ret.x += m_OuterBounds.width;
			ret.width -= m_OuterBounds.width;
		}
		else if (fd == CSSFlowDirection::DOWN)
		{
			if (wrap && ret.height < m_OuterBounds.height)
			{
				ret.height = initialSpace.height;
				ret.width -= m_Parent->m_ChildrenWrapSize.x;
				ret.x += m_Parent->m_ChildrenWrapSize.x;
				ret.y = initialSpace.y;

				MoveBy(maths::vec2(m_Parent->m_ChildrenWrapSize.x, -(space.y - initialSpace.y)));

				m_Parent->m_ChildrenWrapSize.x = 0;
				m_Parent->m_ChildrenWrapSize.y = 0;
			}

			ret.y += m_OuterBounds.height;
			ret.height -= m_OuterBounds.height;
		}

		m_Parent->m_ChildrenWrapSize.x = m_Parent->m_ChildrenWrapSize.x < m_OuterBounds.width ? m_OuterBounds.width : m_Parent->m_ChildrenWrapSize.x;
		m_Parent->m_ChildrenWrapSize.y = m_Parent->m_ChildrenWrapSize.y < m_OuterBounds.height ? m_OuterBounds.height : m_Parent->m_ChildrenWrapSize.y;

		return ret;
	}

} } }
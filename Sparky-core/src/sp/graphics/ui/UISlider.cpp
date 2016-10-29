#include "sp/sp.h"
#include "UISlider.h"

#include "sp/graphics/FontManager.h"

namespace sp { namespace graphics { namespace ui {

	using namespace maths;
	using namespace css;

	UISlider::UISlider(Widget *parent, css::CSSManager* cssManager, tinyxml2::XMLElement *domElement)
		: Widget(parent, cssManager, domElement, true)
	{
		if (domElement->QueryFloatAttribute("min", &m_MinValue))
		{
			m_MinValue = 0.0f;
		}
		
		if (domElement->QueryFloatAttribute("max", &m_MaxValue))
		{
			m_MaxValue = 100.0f;
		}

		if (domElement->QueryFloatAttribute("step", &m_StepSize))
		{
			m_StepSize = 0.0f;
		}
	}

	css::CSSBounds UISlider::CalculatePosition(const css::CSSBounds& space, const css::CSSBounds& initialSpace)
	{
		CSSLength *width = Get<CSSLength>(WIDTH);
		CSSLength *height = Get<CSSLength>(HEIGHT);

		if (width->FitChildren())
			m_InnerBounds.width = 16.0f;
		else
			m_InnerBounds.width = width->ToPixel(&m_CSSInfo, true);

		if (height->FitChildren())
			m_InnerBounds.height = 16.0f;
		else
			m_InnerBounds.height = height->ToPixel(&m_CSSInfo, false);

		m_OuterBounds.x = space.x;
		m_OuterBounds.y = space.y;

		m_Bounds.x = space.x + GetPixelWidth(MARGIN_LEFT);
		m_Bounds.y = space.y + GetPixelHeight(MARGIN_TOP);

		m_InnerBounds.x = m_Bounds.x + GetPixelWidth(PADDING_LEFT) + GetPixelWidth(BORDER_LEFT_WIDTH);
		m_InnerBounds.y = m_Bounds.y + GetPixelWidth(PADDING_TOP) + GetPixelWidth(BORDER_TOP_WIDTH);

		m_Bounds.width = m_InnerBounds.width + GetPixelWidth(PADDING_LEFT) + GetPixelWidth(PADDING_RIGHT) + GetPixelWidth(BORDER_LEFT_WIDTH) + GetPixelWidth(BORDER_RIGHT_WIDTH);
		m_Bounds.height = m_InnerBounds.height + GetPixelHeight(PADDING_TOP) + GetPixelHeight(PADDING_BOTTOM) + GetPixelHeight(BORDER_TOP_WIDTH) + GetPixelHeight(BORDER_BOTTOM_WIDTH);
		
		m_OuterBounds.width = m_Bounds.width + GetPixelWidth(MARGIN_RIGHT) + GetPixelWidth(MARGIN_LEFT);
		m_OuterBounds.height = m_Bounds.height + GetPixelHeight(MARGIN_BOTTOM) + GetPixelHeight(MARGIN_TOP);

		m_Vertical = m_InnerBounds.height > m_InnerBounds.width;

		return PositionInsideParent(space, initialSpace);
	}

	void UISlider::OnRender(Renderer2D& renderer)
	{
		DrawBackgroundAndBorder(renderer);
		if (m_Vertical)
		{
			CSSBounds sliderGrip = m_InnerBounds;

			sliderGrip.height = 5;
			sliderGrip.y += (m_InnerBounds.height - 5) * m_Factor;

			renderer.FillRect(sliderGrip.ToRectangle(), Get<CSSColor>(COLOR)->GetColor());
		}
		else
		{
			CSSBounds sliderGrip = m_InnerBounds;

			sliderGrip.width = 5;
			sliderGrip.x += (m_InnerBounds.width - 5) * m_Factor;

			renderer.FillRect(sliderGrip.ToRectangle(), Get<CSSColor>(COLOR)->GetColor());
		}
	}

	bool UISlider::OnMousePressed(events::MousePressedEvent& e) 
	{
		Widget::OnMousePressed(e);

		return true;
	}

	bool UISlider::OnMouseReleased(events::MouseReleasedEvent& e) 
	{
		Widget::OnMouseReleased(e);

		return true;
	}

	bool UISlider::OnMouseMoved(events::MouseMovedEvent& e) 
	{
		Widget::OnMouseMoved(e);

		if(e.IsDragged() && m_CSSInfo.State == ACTIVE)
		{
			float factor;
			if (m_Vertical)
			{
				factor = (e.GetPosition().y - m_InnerBounds.y) / m_InnerBounds.height;
			}
			else
			{
				factor = (e.GetPosition().x - m_InnerBounds.x) / m_InnerBounds.width;
			}

			m_Factor = maths::clamp(factor, 0.0f, 1.0f);

			m_Value = m_MinValue + (m_MaxValue - m_MinValue) * factor;
			
			if(m_StepSize)
				m_Value = maths::roundStep(m_Value, m_StepSize, m_MinValue);
			
			m_Value = maths::clamp(m_Value, m_MinValue, m_MaxValue);
		}

		return true;
	}

} } }
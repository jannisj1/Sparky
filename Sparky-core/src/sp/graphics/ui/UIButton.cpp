#include "sp/sp.h"
#include "UIButton.h"

#include "sp/graphics/FontManager.h"

namespace sp { namespace graphics { namespace ui {

	using namespace maths;
	using namespace css;
	/*
	UIButton::UIButton(Widget *parent, css::CSSManager* cssManager, tinyxml2::XMLElement *domElement)
		: Widget(parent, cssManager, domElement, true)
	{
		
	}

	void UIButton::OnUpdate(const css::CSSBounds& space)
	{
		m_Bounds.position = vec2(space.position.x + Get<css::CSSLength>(css::MARGIN_LEFT)->ToPixel(true), space.position.y + Get<css::CSSLength>(css::MARGIN_TOP)->ToPixel(false));
		m_Bounds.size.x = GetWidth(css::CSSBounds()) - Get<css::CSSLength>(css::MARGIN_LEFT)->ToPixel(true) - Get<css::CSSLength>(css::MARGIN_RIGHT)->ToPixel(true);
		m_Bounds.size.y = GetHeight(css::CSSBounds()) - Get<css::CSSLength>(css::MARGIN_TOP)->ToPixel(false) - Get<css::CSSLength>(css::MARGIN_BOTTOM)->ToPixel(false);

		float xOffset = Get<css::CSSLength>(css::MARGIN_LEFT)->ToPixel(true) + Get<css::CSSLength>(css::PADDING_LEFT)->ToPixel(true),
			yOffset = Get<css::CSSLength>(css::MARGIN_TOP)->ToPixel(false) + Get<css::CSSLength>(css::PADDING_TOP)->ToPixel(false);

		for (auto c : m_Children)
		{
			float height = c->GetHeight(css::CSSBounds());
			float width = c->GetWidth(css::CSSBounds());

			c->OnUpdate(css::CSSBounds(space.x + xOffset, space.y + yOffset, space.x + width, space.y + height));
			yOffset += height;
		}
	}

	void UIButton::OnRender(Renderer2D& renderer)
	{
		renderer.FillRect(m_Bounds.ToRectangle(), Get<css::CSSColor>(css::BACKGROUND_COLOR)->GetColor());

		for (auto c : m_Children)
		{
			c->OnRender(renderer);
		}
	}

	float UIButton::GetWidth(const css::CSSBounds& space)
	{
		float res = 0.0f;

		for (auto c : m_Children)
		{
			float temp = c->GetWidth(css::CSSBounds());
			res = temp > res ? temp : res;
		}

		return res +
			Get<CSSLength>(PADDING_LEFT)->ToPixel(true) +
			Get<CSSLength>(PADDING_RIGHT)->ToPixel(true) +
			Get<CSSLength>(MARGIN_LEFT)->ToPixel(true) +
			Get<CSSLength>(MARGIN_RIGHT)->ToPixel(true);
	}

	float UIButton::GetHeight(const css::CSSBounds& space)
	{
		float res = 0.0f;

		for (auto c : m_Children)
		{
			res += c->GetHeight(css::CSSBounds());
		}

		return res +
			Get<CSSLength>(PADDING_TOP)->ToPixel(false) +
			Get<CSSLength>(PADDING_BOTTOM)->ToPixel(false) +
			Get<CSSLength>(MARGIN_TOP)->ToPixel(false) +
			Get<CSSLength>(MARGIN_BOTTOM)->ToPixel(false);
	}
	*/
} } }
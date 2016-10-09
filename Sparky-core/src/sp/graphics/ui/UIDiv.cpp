#include "sp/sp.h"
#include "UIDiv.h"

#include "sp/graphics/FontManager.h"

namespace sp { namespace graphics { namespace ui {

	using namespace maths;

	UIDiv::UIDiv(Widget *parent, css::CSSManager* cssManager, tinyxml2::XMLElement *domElement)
		: Widget(parent, cssManager, domElement)
	{

	}

	void UIDiv::OnUpdate(const css::CSSBounds& space)
	{
		m_Bounds = space;
		m_Bounds.x += Get<css::CSSLength>(css::MARGIN_LEFT)->ToPixel(true);
		m_Bounds.y += Get<css::CSSLength>(css::MARGIN_TOP)->ToPixel(false);
		m_Bounds.width = GetWidth(space) - (Get<css::CSSLength>(css::MARGIN_LEFT)->ToPixel(true) + Get<css::CSSLength>(css::MARGIN_RIGHT)->ToPixel(true));
		m_Bounds.height = GetHeight(space) - (Get<css::CSSLength>(css::MARGIN_TOP)->ToPixel(false) + Get<css::CSSLength>(css::MARGIN_BOTTOM)->ToPixel(false));

		float xOffset = Get<css::CSSLength>(css::PADDING_LEFT)->ToPixel(true),
			yOffset = Get<css::CSSLength>(css::PADDING_TOP)->ToPixel(false);

		for (auto c : m_Children)
		{
			css::CSSBounds b;
			b.x = m_Bounds.x + xOffset;
			b.y = m_Bounds.y + yOffset;
			b.width = m_Bounds.width - xOffset - Get<css::CSSLength>(css::PADDING_RIGHT)->ToPixel(true);
			b.height = m_Bounds.height - yOffset - Get<css::CSSLength>(css::PADDING_BOTTOM)->ToPixel(false);

			float height = c->GetHeight(b);
			float width = c->GetWidth(b);

			c->OnUpdate(css::CSSBounds(m_Bounds.x + xOffset, m_Bounds.y + yOffset, width, height));
			yOffset += height;
		}
	}

	void UIDiv::OnRender(Renderer2D& renderer)
	{
		renderer.FillRect(m_Bounds.ToRectangle(), Get<css::CSSColor>(css::BACKGROUND_COLOR)->GetColor());

		for (auto c : m_Children)
		{
			c->OnRender(renderer);
		}
	}

	float UIDiv::GetWidth(const css::CSSBounds& space)
	{
		float res = 0.0f;

		if (Get<css::CSSLength>(css::WIDTH)->IsAuto())
		{
			return space.width;
		}
		else
		{
			return Get<css::CSSLength>(css::WIDTH)->ToPixel(true)
				+ Get<css::CSSLength>(css::PADDING_LEFT)->ToPixel(true)
				+ Get<css::CSSLength>(css::PADDING_RIGHT)->ToPixel(true)
				+ Get<css::CSSLength>(css::MARGIN_LEFT)->ToPixel(true)
				+ Get<css::CSSLength>(css::MARGIN_RIGHT)->ToPixel(true);
		}

		return res;
	}

	float UIDiv::GetHeight(const css::CSSBounds& space)
	{
		float res = 0.0f;
		res += Get<css::CSSLength>(css::PADDING_TOP)->ToPixel(false);
		res += Get<css::CSSLength>(css::PADDING_BOTTOM)->ToPixel(false);
		res += Get<css::CSSLength>(css::MARGIN_TOP)->ToPixel(false);
		res += Get<css::CSSLength>(css::MARGIN_BOTTOM)->ToPixel(false);

		for (auto c : m_Children)
		{
			res += c->GetHeight(space);
		}

		return res;
	}

} } }
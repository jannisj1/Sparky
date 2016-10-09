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
		m_Bounds.width -= Get<css::CSSLength>(css::MARGIN_LEFT)->ToPixel(true) + Get<css::CSSLength>(css::MARGIN_RIGHT)->ToPixel(true);
		m_Bounds.height -= Get<css::CSSLength>(css::MARGIN_TOP)->ToPixel(false) + Get<css::CSSLength>(css::MARGIN_BOTTOM)->ToPixel(false);

		float xOffset = 0.0f, yOffset = 0.0f;

		for (auto c : m_Children)
		{
			float height = c->GetHeight();
			float width = c->GetWidth();

			c->OnUpdate(css::CSSBounds(space.x + xOffset, space.y + yOffset, space.x + width, space.y + height));
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

	float UIDiv::GetWidth()
	{
		float res = 0.0f;


		return res;
	}

	float UIDiv::GetHeight()
	{
		float res = 0.0f;


		return res;
	}

} } }
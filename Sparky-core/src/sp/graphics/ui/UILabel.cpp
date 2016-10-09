#include "sp/sp.h"
#include "UILabel.h"

#include "sp/graphics/FontManager.h"

namespace sp { namespace graphics { namespace ui {

	using namespace maths;
	using namespace css;

	UILabel::UILabel(Widget *parent, css::CSSManager* cssManager, tinyxml2::XMLElement *domElement)
		: Widget(parent, cssManager, domElement)
	{
		m_Font = FontManager::Get();

		if (domElement->Attribute("value"))
			m_Value = domElement->Attribute("value");
		else
			m_Value = domElement->GetText();
	}

	void UILabel::OnUpdate(const css::CSSBounds& space)
	{
		float size;
		if (m_Font->GetFontSize() != (size = Get<css::CSSLength>(css::FONT_SIZE)->ToPixel(false)))
		{
			m_Font = FontManager::Get((uint)size);
		}

		m_Bounds.position = vec2(space.position.x + Get<css::CSSLength>(css::MARGIN_LEFT)->ToPixel(true), space.position.y + Get<css::CSSLength>(css::MARGIN_TOP)->ToPixel(false));
		m_Bounds.size.x = GetWidth(css::CSSBounds()) - Get<css::CSSLength>(css::MARGIN_LEFT)->ToPixel(true) - Get<css::CSSLength>(css::MARGIN_RIGHT)->ToPixel(true);
		m_Bounds.size.y = GetHeight(css::CSSBounds()) - Get<css::CSSLength>(css::MARGIN_TOP)->ToPixel(false) - Get<css::CSSLength>(css::MARGIN_BOTTOM)->ToPixel(false);

		m_Pos.y = space.y;
		m_Pos.y += Get<css::CSSLength>(css::MARGIN_TOP)->ToPixel(false);
		m_Pos.y += Get<css::CSSLength>(css::PADDING_TOP)->ToPixel(false);
		m_Pos.y += m_Font->GetHeight(m_Value);
		m_Pos.y = m_CSSManager->GetHeight() - m_Pos.y;

		m_Pos.x = space.x;
		m_Pos.x += Get<css::CSSLength>(css::MARGIN_LEFT)->ToPixel(true);
		m_Pos.x += Get<css::CSSLength>(css::PADDING_LEFT)->ToPixel(true);
	}

	void UILabel::OnRender(Renderer2D& renderer)
	{
		renderer.FillRect(m_Bounds.ToRectangle(), Get<css::CSSColor>(css::BACKGROUND_COLOR)->GetColor());
		renderer.DrawString(m_Value, m_Pos, *m_Font, Get<css::CSSColor>(css::COLOR)->GetColor());
	}

	float UILabel::GetWidth(const css::CSSBounds& space)
	{
		return m_Font->GetWidth(m_Value) +
			Get<CSSLength>(PADDING_LEFT)->ToPixel(true) +
			Get<CSSLength>(PADDING_RIGHT)->ToPixel(true) +
			Get<CSSLength>(MARGIN_LEFT)->ToPixel(true) +
			Get<CSSLength>(MARGIN_RIGHT)->ToPixel(true);
	}

	float UILabel::GetHeight(const css::CSSBounds& space)
	{
		return m_Font->GetHeight(m_Value) +
			Get<CSSLength>(PADDING_TOP)->ToPixel(false) +
			Get<CSSLength>(PADDING_BOTTOM)->ToPixel(false) +
			Get<CSSLength>(MARGIN_TOP)->ToPixel(false) +
			Get<CSSLength>(MARGIN_BOTTOM)->ToPixel(false);
	}

} } }
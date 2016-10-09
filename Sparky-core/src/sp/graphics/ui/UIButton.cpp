#include "sp/sp.h"
#include "UIButton.h"

#include "sp/graphics/FontManager.h"

namespace sp { namespace graphics { namespace ui {

	using namespace maths;
	using namespace css;

	UIButton::UIButton(css::CSSManager* cssManager, tinyxml2::XMLElement *domElement)
		: Widget(cssManager, domElement)
	{
		m_Font = FontManager::Get();

		if (domElement->Attribute("value"))
			m_Value = domElement->Attribute("value");
		else
			m_Value = domElement->GetText();
	}

	void UIButton::OnUpdate(const css::CSSBounds& space)
	{
		float size;
		if (m_Font->GetFontSize() != (size = Get<css::CSSLength>(css::FONT_SIZE)->ToPixel(false)))
		{
			m_Font = FontManager::Get((uint)size);
		}

		m_Bounds.position = vec2(space.position.x + Get<css::CSSLength>(css::MARGIN_LEFT)->ToPixel(true), space.position.y + Get<css::CSSLength>(css::MARGIN_TOP)->ToPixel(false));
		m_Bounds.size.x = GetWidth() - Get<css::CSSLength>(css::MARGIN_LEFT)->ToPixel(true) - Get<css::CSSLength>(css::MARGIN_RIGHT)->ToPixel(true); //TODO: Make this more efficient
		m_Bounds.size.y = GetHeight() - Get<css::CSSLength>(css::MARGIN_TOP)->ToPixel(false) - Get<css::CSSLength>(css::MARGIN_BOTTOM)->ToPixel(false);

		m_Pos.y = space.y;
		m_Pos.y += Get<css::CSSLength>(css::MARGIN_TOP)->ToPixel(false);
		m_Pos.y += Get<css::CSSLength>(css::PADDING_TOP)->ToPixel(false);
		m_Pos.y += m_Font->GetHeight(m_Value);
		m_Pos.y = m_CSSManager->GetHeight() - m_Pos.y;

		m_Pos.x = space.x;
		m_Pos.x += Get<css::CSSLength>(css::MARGIN_LEFT)->ToPixel(true);
		m_Pos.x += Get<css::CSSLength>(css::PADDING_LEFT)->ToPixel(true);
	}

	void UIButton::OnRender(Renderer2D& renderer)
	{
		renderer.FillRect(m_Bounds.ToRectangle(), Get<css::CSSColor>(css::BACKGROUND_COLOR)->GetColor());
		renderer.DrawString(m_Value, m_Pos, *m_Font, Get<css::CSSColor>(css::COLOR)->GetColor());
	}

	float UIButton::GetWidth()
	{
		return m_Font->GetWidth(m_Value) +
			m_CSSManager->Get<CSSLength>(m_CSSInfo, PADDING_LEFT)->ToPixel(true) +
			m_CSSManager->Get<CSSLength>(m_CSSInfo, PADDING_RIGHT)->ToPixel(true) +
			m_CSSManager->Get<CSSLength>(m_CSSInfo, MARGIN_LEFT)->ToPixel(true) +
			m_CSSManager->Get<CSSLength>(m_CSSInfo, MARGIN_RIGHT)->ToPixel(true);
	}

	float UIButton::GetHeight()
	{
		return m_Font->GetHeight(m_Value) +
			m_CSSManager->Get<CSSLength>(m_CSSInfo, PADDING_TOP)->ToPixel(false) +
			m_CSSManager->Get<CSSLength>(m_CSSInfo, PADDING_BOTTOM)->ToPixel(false) +
			m_CSSManager->Get<CSSLength>(m_CSSInfo, MARGIN_TOP)->ToPixel(false) +
			m_CSSManager->Get<CSSLength>(m_CSSInfo, MARGIN_BOTTOM)->ToPixel(false);
	}

	bool UIButton::OnMousePressed(events::MousePressedEvent& e)
	{
		return false;
	}

} } }
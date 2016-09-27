#include "sp/sp.h"
#include "UILabel.h"

#include "sp/graphics/FontManager.h"

namespace sp { namespace graphics { namespace ui {

	using namespace maths;
	using namespace css;

	UILabel::UILabel(css::CSSManager* cssManager, tinyxml2::XMLElement *domElement)
		: Widget(cssManager, domElement)
	{
		m_Font = FontManager::Get();

		if (domElement->Attribute("value"))
			m_Value = domElement->Attribute("value");
		else
			m_Value = m_CSSInfo.Name;
	}

	void UILabel::OnUpdate(const maths::Rectangle& space)
	{
		m_Bounds = space;
		
		m_Pos.y = space.y;
		m_Pos.y += m_CSSManager->Get<css::CSSLength>(m_CSSInfo, css::MARGIN_TOP)->ToPixel(false);
		m_Pos.y += m_CSSManager->Get<css::CSSLength>(m_CSSInfo, css::PADDING_TOP)->ToPixel(false);
		m_Pos.y += m_Font->GetHeight(m_Value);
		m_Pos.y = m_CSSManager->GetHeight() - m_Pos.y;

		m_Pos.x = space.x;
		m_Pos.x += m_CSSManager->Get<css::CSSLength>(m_CSSInfo, css::MARGIN_LEFT)->ToPixel(true);
		m_Pos.x += m_CSSManager->Get<css::CSSLength>(m_CSSInfo, css::PADDING_LEFT)->ToPixel(true);
	}

	void UILabel::OnRender(Renderer2D& renderer)
	{
		renderer.DrawString(m_Value, m_Pos, *m_Font);
	}

	float UILabel::GetWidth()
	{
		return m_Font->GetWidth(m_Value) +
			m_CSSManager->Get<CSSLength>(m_CSSInfo, PADDING_LEFT)->ToPixel(true) +
			m_CSSManager->Get<CSSLength>(m_CSSInfo, PADDING_RIGHT)->ToPixel(true) +
			m_CSSManager->Get<CSSLength>(m_CSSInfo, MARGIN_LEFT)->ToPixel(true) +
			m_CSSManager->Get<CSSLength>(m_CSSInfo, MARGIN_RIGHT)->ToPixel(true);
	}

	float UILabel::GetHeight()
	{
		return m_Font->GetHeight(m_Value) +
			m_CSSManager->Get<CSSLength>(m_CSSInfo, PADDING_TOP)->ToPixel(false) +
			m_CSSManager->Get<CSSLength>(m_CSSInfo, PADDING_BOTTOM)->ToPixel(false) +
			m_CSSManager->Get<CSSLength>(m_CSSInfo, MARGIN_TOP)->ToPixel(false) +
			m_CSSManager->Get<CSSLength>(m_CSSInfo, MARGIN_BOTTOM)->ToPixel(false);
	}

} } }
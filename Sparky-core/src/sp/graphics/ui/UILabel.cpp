#include "sp/sp.h"
#include "UILabel.h"

#include "sp/graphics/FontManager.h"

namespace sp { namespace graphics { namespace ui {

	using namespace maths;

	UILabel::UILabel(css::CSSManager* cssManager, const String& value, const maths::vec2& pos, uint size)
		: Widget(css::UIElementCSSInfo("label"), cssManager), m_Value(value), m_Size(size), m_Pos(pos)
	{
		m_Font = FontManager::Get(size);
	}

	void UILabel::OnUpdate()
	{
		m_Pos.x = ((css::CSSLength*) m_CSSManager->GetProperty(&m_CSSInfo, css::PADDING_LEFT))->ToPixel(true);
		m_Pos.y = ((css::CSSLength*) m_CSSManager->GetProperty(&m_CSSInfo, css::PADDING_TOP))->ToPixel(false);

	}

	void UILabel::OnRender(Renderer2D& renderer)
	{
		renderer.DrawString(m_Value, m_Pos, *m_Font);
	}

} } }
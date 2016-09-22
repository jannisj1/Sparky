#include "sp/sp.h"
#include "UILabel.h"

#include "sp/graphics/FontManager.h"

namespace sp { namespace graphics { namespace ui {

	using namespace maths;

	UILabel::UILabel(const String& value, const maths::vec2& pos, uint size)
		: Widget("label"), m_Value(value), m_Size(size), m_Pos(pos)
	{
		m_Font = FontManager::Get(size);
	}

	void UILabel::OnUpdate()
	{
		
	}

	void UILabel::OnRender(Renderer2D& renderer)
	{
		renderer.DrawString(m_Value, m_Pos, *m_Font);
	}

} } }
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
			m_InitialValue = domElement->Attribute("value");
		else
			m_InitialValue = domElement->GetText();
	}

	css::CSSBounds UILabel::CalculatePosition(const css::CSSBounds& space, const css::CSSBounds& initialSpace)
	{
		float size;
		if (m_Font->GetFontSize() != (size = GetPixelHeight(FONT_SIZE)))
		{
			m_Font = FontManager::Get((uint)size);
		}

		m_OuterBounds.x = space.x;
		m_OuterBounds.y = space.y;

		m_Bounds.x = space.x + GetPixelWidth(MARGIN_LEFT);
		m_Bounds.y = space.y + GetPixelHeight(MARGIN_TOP);

		//TODO: Calculate font height correctly
		m_Bounds.width = m_Font->GetWidth(m_Value) + GetPixelWidth(PADDING_LEFT) + GetPixelWidth(PADDING_RIGHT) + GetPixelWidth(BORDER_LEFT_WIDTH) + GetPixelWidth(BORDER_RIGHT_WIDTH);
		m_Bounds.height = m_Font->GetHeight(m_Value) + GetPixelHeight(PADDING_TOP) + GetPixelHeight(PADDING_BOTTOM) + GetPixelHeight(BORDER_TOP_WIDTH) + GetPixelHeight(BORDER_BOTTOM_WIDTH);
		
		m_OuterBounds.width = m_Bounds.width + GetPixelWidth(MARGIN_RIGHT) + GetPixelWidth(MARGIN_LEFT);
		m_OuterBounds.height = m_Bounds.height + GetPixelHeight(MARGIN_BOTTOM) + GetPixelHeight(MARGIN_TOP);

		m_Pos.x = m_Bounds.x + GetPixelWidth(BORDER_LEFT_WIDTH) + GetPixelWidth(PADDING_LEFT);
		m_Pos.y = m_Bounds.y + GetPixelHeight(PADDING_TOP) + GetPixelHeight(BORDER_TOP_WIDTH) + m_Font->GetHeight(m_Value);

		maths::vec2 offsets = m_Font->GetOffsets(m_Value);
		offsets.x = -offsets.x;
		m_Pos += offsets;

		m_Pos.y = Application::GetApplication().GetWindowHeight() - m_Pos.y;

		//m_Value = m_JS->EvalString(m_InitialValue);
		m_Value = "todo";

		return PositionInsideParent(space, initialSpace);
	}

	void UILabel::OnRender(Renderer2D& renderer)
	{
		DrawBackgroundAndBorder(renderer);
		renderer.DrawString(m_Value, m_Pos, *m_Font, Get<css::CSSColor>(css::COLOR)->GetColor());
	}

	void UILabel::MoveBy(const maths::vec2& delta)
	{
		m_OuterBounds.position += delta;
		m_InnerBounds.position += delta;
		m_Bounds.position += delta;
		m_Pos.x += delta.x;
		m_Pos.y -= delta.y;
	}

} } }
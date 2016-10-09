#pragma once
#include "sp/sp.h"
#include "sp/String.h"

#include "Widget.h"

namespace sp { namespace graphics { namespace ui {

	class UILabel : public Widget
	{
	protected:
		String m_Value;
		Font* m_Font;
		maths::vec2 m_Pos;

	public:
		UILabel(Widget *parent, css::CSSManager* cssManager, tinyxml2::XMLElement *domElement);

		void OnUpdate(const css::CSSBounds& space) override;
		void OnRender(Renderer2D& renderer) override;

		inline void SetValue(const String& label) { m_Value = label; }
		inline const String& GetValue() const { return m_Value; }

		inline void SetFont(Font* font) { m_Font = font; }
		inline const Font& GetFont() const { return *m_Font; }

		float GetWidth(const css::CSSBounds& space) override;
		float GetHeight(const css::CSSBounds& space) override;
	};

} } }
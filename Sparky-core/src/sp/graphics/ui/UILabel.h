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
		uint32 m_Color;

	public:
		UILabel(css::CSSManager* cssManager, tinyxml2::XMLElement *domElement);

		virtual void OnUpdate(const css::CSSBounds& space) override;
		virtual void OnRender(Renderer2D& renderer) override;

		inline void SetValue(const String& label) { m_Value = label; }
		inline const String& GetValue() const { return m_Value; }

		inline void SetFont(Font* font) { m_Font = font; }
		inline const Font& GetFont() const { return *m_Font; }

		float GetWidth() override;
		float GetHeight() override;
	};

} } }
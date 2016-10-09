#pragma once
#include "sp/sp.h"
#include "sp/String.h"

#include "Widget.h"

namespace sp { namespace graphics { namespace ui {

	class UIButton : public Widget
	{
	protected:
		String m_Value;
		Font* m_Font;
		maths::vec2 m_Pos;

	public:
		UIButton(css::CSSManager* cssManager, tinyxml2::XMLElement *domElement);

		void OnUpdate(const css::CSSBounds& space) override;
		void OnRender(Renderer2D& renderer) override;

		bool OnMousePressed(events::MousePressedEvent& e) override;

		inline void SetValue(const String& label) { m_Value = label; }
		inline const String& GetValue() const { return m_Value; }

		inline void SetFont(Font* font) { m_Font = font; }
		inline const Font& GetFont() const { return *m_Font; }

		float GetWidth() override;
		float GetHeight() override;
	};

} } }
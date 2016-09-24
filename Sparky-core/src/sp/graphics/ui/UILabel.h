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
		uint m_Size;
		maths::vec2 m_Pos;

	public:
		UILabel(css::CSSManager* cssManager, const String& value, const maths::vec2& pos, uint size);

		virtual void OnUpdate() override;
		virtual void OnRender(Renderer2D& renderer) override;

		inline void SetValue(const String& label) { m_Value = label; }
		inline const String& GetValue() const { return m_Value; }

		inline void SetFont(Font* font) { m_Font = font; }
		inline const Font& GetFont() const { return *m_Font; }

	};

} } }
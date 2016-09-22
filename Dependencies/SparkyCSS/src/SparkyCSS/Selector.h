#pragma once
#include <sp/graphics/ui/Widget.h>

namespace sp { namespace css {
		
	class CSSSelector
	{
	public:
		enum SelectorType
		{
			CLASS,
			ID,
			NAME
		};

	private:
		SelectorType m_ST;

	public:
		CSSSelector(SelectorType st)
			: m_ST(st) { }

		virtual bool Applies(graphics::ui::Widget* widget) = 0;
	};

	class CSSNameSelector : public CSSSelector
	{
		String m_Name;

	public:
		CSSNameSelector(const String& name)
			: m_Name(name), CSSSelector(NAME) {}

		bool Applies(graphics::ui::Widget* widget)
		{
			return widget->GetName() == m_Name;
		}
	};

} }
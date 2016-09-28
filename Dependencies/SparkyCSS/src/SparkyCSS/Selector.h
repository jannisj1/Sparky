#pragma once
#include <vector>
#include <unordered_map>
#include <sp/utils/Log.h>
#include <sp/system/Memory.h>

namespace sp { namespace css {

	struct UIElementCSSInfo
	{
		UIElementCSSInfo() {}
		String ID;
		String Name; // e.g. label, button...
		std::vector<String> Classes;
	};

	class CSSSelector
	{
	public:
		enum class SelectorType
		{
			CLASS,
			ID,
			NAME,
			ALL,
			LIST
		};

	private:
		SelectorType m_ST;

	public:
		CSSSelector(SelectorType st)
			: m_ST(st) { }

		virtual bool Applies(const UIElementCSSInfo* cssInfo) = 0;
	};

	class CSSNameSelector : public CSSSelector
	{
		String m_Name;

	public:
		CSSNameSelector(const String& name)
			: m_Name(name), CSSSelector(SelectorType::NAME) {}

		bool Applies(const UIElementCSSInfo* cssInfo)
		{
			return cssInfo->Name == m_Name;
		}
	};

	class CSSIDSelector : public CSSSelector
	{
		String m_ID;

	public:
		CSSIDSelector(const String& id)
			: m_ID(id), CSSSelector(SelectorType::ID) {}

		bool Applies(const UIElementCSSInfo* cssInfo)
		{
			return cssInfo->ID == m_ID;
		}
	};

	class CSSClassSelector : public CSSSelector
	{
		String m_Class;

	public:
		CSSClassSelector(const String& _class)
			: m_Class(_class), CSSSelector(SelectorType::CLASS) {}

		bool Applies(const UIElementCSSInfo* cssInfo)
		{
			for (auto& r : cssInfo->Classes)
			{
				if (r == m_Class) return true;
			}

			return false;
		}
	};

	class CSSAllSelector : public CSSSelector
	{
	public:
		CSSAllSelector()
			: CSSSelector(SelectorType::ALL) {}

		bool Applies(const UIElementCSSInfo* cssInfo)
		{
			return true;
		}
	};

	class CSSListSelector : public CSSSelector
	{
		CSSSelector *m_First, *m_Second;

	public:
		CSSListSelector(CSSSelector* first, CSSSelector* second)
			: m_First(first), m_Second(second), CSSSelector(SelectorType::LIST) {}

		bool Applies(const UIElementCSSInfo* cssInfo)
		{
			return m_First->Applies(cssInfo) || m_Second->Applies(cssInfo);
		}
	};

} }
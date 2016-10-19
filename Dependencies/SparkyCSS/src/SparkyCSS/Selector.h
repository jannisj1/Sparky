#pragma once
#include <vector>
#include <unordered_map>
#include <sp/utils/Log.h>
#include <sp/system/Memory.h>

namespace sp { namespace css {

	enum UIState {
		IDLE,
		HOVER,
		FOCUSED,
		ACTIVE
	};

	struct UIElementCSSInfo
	{
		UIElementCSSInfo() {}
		String ID;
		String Name;
		std::vector<String> Classes;
		UIState State;
		CSSBounds InnerBounds;
		const UIElementCSSInfo* Parent = nullptr;
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
			LIST,
			PSEUDO,
			FALSE
		};

	private:
		SelectorType m_ST;

	public:
		CSSSelector(SelectorType st)
			: m_ST(st) { }

		virtual bool Applies(const UIElementCSSInfo *cssInfo) = 0;
		virtual uint32 GetSpecificity(const UIElementCSSInfo *cssInfo) = 0;
	};

	class CSSFalseSelector : public CSSSelector
	{
	public:
		CSSFalseSelector() : CSSSelector(SelectorType::FALSE) {}
		bool Applies(const UIElementCSSInfo *cssInfo) { return false; }
		uint32 GetSpecificity(const UIElementCSSInfo *cssInfo) { return 0U; }
	};

	class CSSNameSelector : public CSSSelector
	{
		String m_Name;

	public:
		CSSNameSelector(const String& name)
			: m_Name(name), CSSSelector(SelectorType::NAME) {}

		bool Applies(const UIElementCSSInfo *cssInfo)
		{
			return cssInfo->Name == m_Name;
		}

		uint32 GetSpecificity(const UIElementCSSInfo *cssInfo) { return (1U << 8U); }
	};

	class CSSIDSelector : public CSSSelector
	{
		String m_ID;

	public:
		CSSIDSelector(const String& id)
			: m_ID(id), CSSSelector(SelectorType::ID) {}

		bool Applies(const UIElementCSSInfo *cssInfo)
		{
			return cssInfo->ID == m_ID;
		}

		uint32 GetSpecificity(const UIElementCSSInfo *cssInfo) { return (1U << 24U); }
	};

	class CSSClassSelector : public CSSSelector
	{
		String m_Class;
		CSSSelector* m_Child;

	public:
		CSSClassSelector(const String& _class, CSSSelector *child = nullptr)
			: m_Class(_class), m_Child(child), CSSSelector(SelectorType::CLASS) {}

		bool Applies(const UIElementCSSInfo *cssInfo)
		{
			for (auto& r : cssInfo->Classes)
			{
				if (r == m_Class && (m_Child) ? m_Child->Applies(cssInfo) : true) return true;
			}

			return false;
		}

		uint32 GetSpecificity(const UIElementCSSInfo *cssInfo) 
		{
			if (m_Child)
				return (1U << 16U) + m_Child->GetSpecificity(cssInfo);
			
			return (1U << 16U);
		}
	};

	class CSSAllSelector : public CSSSelector
	{
	public:
		CSSAllSelector()
			: CSSSelector(SelectorType::ALL) {}

		bool Applies(const UIElementCSSInfo *cssInfo)
		{
			return true;
		}

		uint32 GetSpecificity(const UIElementCSSInfo *cssInfo) { return (1U); }
	};

	class CSSListSelector : public CSSSelector
	{
		CSSSelector *m_First, *m_Second;

	public:
		CSSListSelector(CSSSelector *first, CSSSelector *second)
			: m_First(first), m_Second(second), CSSSelector(SelectorType::LIST) {}

		bool Applies(const UIElementCSSInfo *cssInfo)
		{
			return m_First->Applies(cssInfo) || m_Second->Applies(cssInfo);
		}

		uint32 GetSpecificity(const UIElementCSSInfo *cssInfo) 
		{ 
			uint32 res = 0U;

			if (m_First->Applies(cssInfo)) res += m_First->GetSpecificity(cssInfo);
			if (m_Second->Applies(cssInfo)) res += m_Second->GetSpecificity(cssInfo);

			return res;
		}
	};

	class CSSInsideSelector : public CSSSelector
	{
		CSSSelector *m_First, *m_Second;

	public:
		CSSInsideSelector(CSSSelector *first, CSSSelector *second)
			: m_First(first), m_Second(second), CSSSelector(SelectorType::LIST) {}

		bool Applies(const UIElementCSSInfo *cssInfo)
		{
			if (m_Second->Applies(cssInfo))
			{
				const UIElementCSSInfo *parent = cssInfo->Parent;
				
				while (parent)
				{
					if (m_First->Applies(parent))
					{
						return true;
					}
					parent = parent->Parent;
				}
			}

			return false;
		}

		uint32 GetSpecificity(const UIElementCSSInfo *cssInfo)
		{
			uint32 res = 0U;

			res += m_First->GetSpecificity(cssInfo);
			res += m_Second->GetSpecificity(cssInfo);
			res += (1U << 8U);

			return res;
		}
	};

	// Pseudo-Selectors

	class CSSHoverSelector : public CSSSelector
	{
		CSSSelector *m_Child;

	public:
		CSSHoverSelector(CSSSelector *child)
			: m_Child(child), CSSSelector(SelectorType::PSEUDO) {}

		bool Applies(const UIElementCSSInfo *cssInfo)
		{
			return cssInfo->State == HOVER && m_Child->Applies(cssInfo);
		}

		uint32 GetSpecificity(const UIElementCSSInfo *cssInfo) { return (1U << 16U) + m_Child->GetSpecificity(cssInfo); }
	};

	class CSSFocusSelector : public CSSSelector
	{
		CSSSelector *m_Child;

	public:
		CSSFocusSelector(CSSSelector *child)
			: m_Child(child), CSSSelector(SelectorType::PSEUDO) {}

		bool Applies(const UIElementCSSInfo *cssInfo)
		{
			return cssInfo->State == FOCUSED && m_Child->Applies(cssInfo);
		}

		uint32 GetSpecificity(const UIElementCSSInfo *cssInfo) { return (1U << 16U) + m_Child->GetSpecificity(cssInfo); }
	};

	class CSSActiveSelector : public CSSSelector
	{
		CSSSelector *m_Child;

	public:
		CSSActiveSelector(CSSSelector *child)
			: m_Child(child), CSSSelector(SelectorType::PSEUDO) {}

		bool Applies(const UIElementCSSInfo *cssInfo)
		{
			return cssInfo->State == ACTIVE && m_Child->Applies(cssInfo);
		}

		uint32 GetSpecificity(const UIElementCSSInfo *cssInfo) { return (1U << 16U) + m_Child->GetSpecificity(cssInfo); }
	};

} }
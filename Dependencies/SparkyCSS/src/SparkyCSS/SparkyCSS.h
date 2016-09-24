#pragma once
#include <vector>
#include <unordered_map>
#include <sp/utils/Log.h>
#include <sp/system/Memory.h>
#include <sp/app/Application.h>

namespace sp { namespace css {

	enum CSSKey
	{
		PADDING,
		PADDING_TOP,
		PADDING_RIGHT,
		PADDING_BOTTOM,
		PADDING_LEFT,

		MARGIN,
		MARGIN_TOP,
		MARGIN_RIGHT,
		MARGIN_BOTTOM,
		MARGIN_LEFT
	};

	struct UIElementCSSInfo
	{
		UIElementCSSInfo(const String& name) : Name(name) { }
		String ID;
		String Name; // e.g. label, button...
		std::vector<String> Classes;
	};

	// All value types

	enum LengthUnit
	{
		PIXEL,
		PERCENT
	};

	class CSSValue
	{
	public:
		enum class ValueType
		{
			LENGTH
		};

	private:
		ValueType m_ValueType;

	public:
		CSSValue(ValueType vt)
			: m_ValueType(vt) { }

		virtual String ToString() = 0;

	};

	class CSSLength : public CSSValue
	{
		float m_Val;
		LengthUnit m_Lu;

	public:
		CSSLength(float val, LengthUnit lu)
			: m_Val(val), m_Lu(lu), CSSValue(CSSValue::ValueType::LENGTH) 
		{
			if (lu == PERCENT)
				m_Val /= 100.0f;
		}

		String ToString() override
		{
			return std::to_string(m_Val) + " " + std::to_string((int)m_Lu);
		}

		float ToPixel(bool horizontal)
		{
			switch (m_Lu)
			{
			case sp::css::PIXEL:
				return m_Val;
				break;
			case sp::css::PERCENT:
				
				if(horizontal)
					return Window::GetWindowClass(nullptr)->GetWidth() * m_Val;
				else
					return Window::GetWindowClass(nullptr)->GetHeight() * m_Val;

				break;
			default:
				return 0.0f;
				break;
			}
		}
	};

	// All selector types

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

		virtual bool Applies(const UIElementCSSInfo* cssInfo) = 0;
	};

	class CSSNameSelector : public CSSSelector
	{
		String m_Name;

	public:
		CSSNameSelector(const String& name)
			: m_Name(name), CSSSelector(NAME) {}

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
			: m_ID(id), CSSSelector(NAME) {}

		bool Applies(const UIElementCSSInfo* cssInfo)
		{
			return cssInfo->ID == m_ID;
		}
	};

	typedef std::vector<std::pair<std::vector<CSSSelector*>, std::unordered_map<sp::css::CSSKey, sp::css::CSSValue*>>> CSSRules;

	class CSSParser
	{
	public:
		static void Parse(CSSRules& rules, const String& css);

	};

} }

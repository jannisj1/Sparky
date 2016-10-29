#pragma once
#include <sp/sp.h>
#include <SparkyCSS/SparkyCSS.h>

namespace sp { namespace css {

	class CSSManager
	{
		CSSRules m_Rules;

	public:
		CSSManager();
		~CSSManager();

		inline uint GetWidth() const { return Application::GetApplication().GetWindowWidth(); }
		inline uint GetHeight() const { return Application::GetApplication().GetWindowHeight(); }

		void EvalCSS(const String& css);
		void EvalPrivateCSS(std::unordered_map<sp::css::CSSKey, sp::css::CSSValue*>& PrivateCSSRules, const String& css);
		CSSValue* GetValue(const std::unordered_map<sp::css::CSSKey, sp::css::CSSValue*>& PrivateCSSRules, const UIElementCSSInfo& cssinfo, CSSKey key);
		
		template<class T>
		T* Get(const std::unordered_map<sp::css::CSSKey, sp::css::CSSValue*>& PrivateCSSRules, const UIElementCSSInfo& cssinfo, CSSKey key)
		{
			return (T*)GetValue(PrivateCSSRules, cssinfo, key);
		}
	};

} }
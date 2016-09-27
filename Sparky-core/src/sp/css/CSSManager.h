#pragma once
#include <SparkyCSS/SparkyCSS.h>

namespace sp { namespace css {

	class CSSManager
	{
		CSSRules m_Rules;

	public:
		CSSManager();
		~CSSManager();

		inline float GetWidth() const { return Application::GetApplication().GetWindowWidth(); }
		inline float GetHeight() const { return Application::GetApplication().GetWindowHeight(); }

		void EvalCSS(const String& css);
		CSSValue* GetValue(const UIElementCSSInfo& cssinfo, CSSKey key);
		
		template<class T>
		T* Get(const UIElementCSSInfo& cssinfo, CSSKey key)
		{
			return (T*)GetValue(cssinfo, key);
		}
	};

} }
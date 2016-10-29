#include <sp/sp.h>
#include "CSSManager.h"

namespace sp { namespace css {
	
	CSSManager::CSSManager()
	{
		CSSParser::ParseMasterCSS(m_Rules);
	}

	CSSManager::~CSSManager()
	{
		for (auto& rule: m_Rules)
		{
			spdel rule.first;
			
			for (auto val : rule.second)
			{
				spdel val.second;
			}
		}
	}
	
	void CSSManager::EvalCSS(const String& css)
	{
		CSSParser::Parse(m_Rules, css);
	}
	
	CSSValue* CSSManager::GetValue(const std::unordered_map<sp::css::CSSKey, sp::css::CSSValue*>& PrivateCSSRules, const UIElementCSSInfo& cssinfo, CSSKey key)
	{
		CSSValue* current = nullptr;
		uint32 specificity = 0;

		for (auto& rule : m_Rules)
		{
			if (rule.first->Applies(&cssinfo))
			{
				if(rule.first->GetSpecificity(&cssinfo) >= specificity)
					if (rule.second.find(key) != rule.second.end())
					{
						current = rule.second[key];
						specificity = rule.first->GetSpecificity(&cssinfo);
					}
			}
		}

		if (PrivateCSSRules.find(key) != PrivateCSSRules.end())
		{
			current = PrivateCSSRules.at(key);
		}

		SP_ASSERT(current, "Could not find css-property (did you forget to include it in master.css?)");
		
		return current; 
	}

	void CSSManager::EvalPrivateCSS(std::unordered_map<sp::css::CSSKey, sp::css::CSSValue*>& PrivateCSSRules, const String& css)
	{
		CSSParser::Parse(PrivateCSSRules, css);
	}

} }
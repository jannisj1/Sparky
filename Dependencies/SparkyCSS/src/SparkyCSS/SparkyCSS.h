#pragma once
#include <sp/sp.h>
#include <sp/String.h>
#include <sp/utils/Log.h>
#include <sp/system/Memory.h>

#include "Selector.h"
#include "Value.h"

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

	typedef std::vector<std::pair<std::vector<CSSSelector*>, std::unordered_map<sp::css::CSSKey, std::vector<sp::css::CSSValue*>>>> CSSRules;

	class CSSParser
	{
	public:
		static void Parse(CSSRules& rules, const String& css);

	};

} }

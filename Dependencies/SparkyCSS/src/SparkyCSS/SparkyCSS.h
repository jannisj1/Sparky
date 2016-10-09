#pragma once
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
		MARGIN_LEFT,

		WIDTH,
		HEIGHT,

		COLOR,

		BACKGROUND_COLOR,
		BACKGROUND,

		FONT_SIZE,
		FLOW_CHILDREN
	};

	typedef std::vector<std::pair<CSSSelector*, std::unordered_map<sp::css::CSSKey, sp::css::CSSValue*>>> CSSRules;

	class CSSParser
	{
	public:
		static void Parse(CSSRules& rules, const String& css);
	};

} }

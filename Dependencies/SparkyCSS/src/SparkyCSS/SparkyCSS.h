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
		FLOW_CHILDREN,

		BORDER,

		BORDER_STYLE,
		BORDER_TOP_STYLE,
		BORDER_RIGHT_STYLE,
		BORDER_BOTTOM_STYLE,
		BORDER_LEFT_STYLE,

		BORDER_WIDTH,
		BORDER_TOP_WIDTH,
		BORDER_RIGHT_WIDTH,
		BORDER_BOTTOM_WIDTH,
		BORDER_LEFT_WIDTH,

		BORDER_COLOR,
		BORDER_TOP_COLOR,
		BORDER_RIGHT_COLOR,
		BORDER_BOTTOM_COLOR,
		BORDER_LEFT_COLOR,
	};

	typedef std::vector<std::pair<CSSSelector*, std::unordered_map<sp::css::CSSKey, sp::css::CSSValue*>>> CSSRules;

	class CSSParser
	{
	public:
		static void ParseMasterCSS(CSSRules& rules);
		static void Parse(CSSRules& rules, const String& css);
	};

} }

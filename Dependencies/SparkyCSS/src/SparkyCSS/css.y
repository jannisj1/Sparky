%{
#include <iostream>
#include "lexer.h"
#include "SparkyCSS.h"

using namespace sp::css;

/*
	typedef std::vector<
				std::pair<
					std::vector<CSSSelector*>, 
					std::unordered_map
					<
						sp::css::CSSKey, 
						sp::css::CSSValue*
					>
				>
			> CSSRules;
*/

CSSRules *res_map;

void yyerror (const char *s);

/*
 * (c) Dean McNamee <dean@gmail.com>, 2012.
 * C++ port by Konstantin Käfer <mail@kkaefer.com>, 2014.
 *
 * https://github.com/deanm/css-color-parser-js
 * https://github.com/kkaefer/css-color-parser-cpp
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

std::unordered_map<String, CSSColor>  color_map {
    { "transparent", { 0, 0, 0, 0 } }, { "aliceblue", { 240, 248, 255, 1 } },
    { "antiquewhite", { 250, 235, 215, 1 } }, { "aqua", { 0, 255, 255, 1 } },
    { "aquamarine", { 127, 255, 212, 1 } }, { "azure", { 240, 255, 255, 1 } },
    { "beige", { 245, 245, 220, 1 } }, { "bisque", { 255, 228, 196, 1 } },
    { "black", { 0, 0, 0, 1 } }, { "blanchedalmond", { 255, 235, 205, 1 } },
    { "blue", { 0, 0, 255, 1 } }, { "blueviolet", { 138, 43, 226, 1 } },
    { "brown", { 165, 42, 42, 1 } }, { "burlywood", { 222, 184, 135, 1 } },
    { "cadetblue", { 95, 158, 160, 1 } }, { "chartreuse", { 127, 255, 0, 1 } },
    { "chocolate", { 210, 105, 30, 1 } }, { "coral", { 255, 127, 80, 1 } },
    { "cornflowerblue", { 100, 149, 237, 1 } }, { "cornsilk", { 255, 248, 220, 1 } },
    { "crimson", { 220, 20, 60, 1 } }, { "cyan", { 0, 255, 255, 1 } },
    { "darkblue", { 0, 0, 139, 1 } }, { "darkcyan", { 0, 139, 139, 1 } },
    { "darkgoldenrod", { 184, 134, 11, 1 } }, { "darkgray", { 169, 169, 169, 1 } },
    { "darkgreen", { 0, 100, 0, 1 } }, { "darkgrey", { 169, 169, 169, 1 } },
    { "darkkhaki", { 189, 183, 107, 1 } }, { "darkmagenta", { 139, 0, 139, 1 } },
    { "darkolivegreen", { 85, 107, 47, 1 } }, { "darkorange", { 255, 140, 0, 1 } },
    { "darkorchid", { 153, 50, 204, 1 } }, { "darkred", { 139, 0, 0, 1 } },
    { "darksalmon", { 233, 150, 122, 1 } }, { "darkseagreen", { 143, 188, 143, 1 } },
    { "darkslateblue", { 72, 61, 139, 1 } }, { "darkslategray", { 47, 79, 79, 1 } },
    { "darkslategrey", { 47, 79, 79, 1 } }, { "darkturquoise", { 0, 206, 209, 1 } },
    { "darkviolet", { 148, 0, 211, 1 } }, { "deeppink", { 255, 20, 147, 1 } },
    { "deepskyblue", { 0, 191, 255, 1 } }, { "dimgray", { 105, 105, 105, 1 } },
    { "dimgrey", { 105, 105, 105, 1 } }, { "dodgerblue", { 30, 144, 255, 1 } },
    { "firebrick", { 178, 34, 34, 1 } }, { "floralwhite", { 255, 250, 240, 1 } },
    { "forestgreen", { 34, 139, 34, 1 } }, { "fuchsia", { 255, 0, 255, 1 } },
    { "gainsboro", { 220, 220, 220, 1 } }, { "ghostwhite", { 248, 248, 255, 1 } },
    { "gold", { 255, 215, 0, 1 } }, { "goldenrod", { 218, 165, 32, 1 } },
    { "gray", { 128, 128, 128, 1 } }, { "green", { 0, 128, 0, 1 } },
    { "greenyellow", { 173, 255, 47, 1 } }, { "grey", { 128, 128, 128, 1 } },
    { "honeydew", { 240, 255, 240, 1 } }, { "hotpink", { 255, 105, 180, 1 } },
    { "indianred", { 205, 92, 92, 1 } }, { "indigo", { 75, 0, 130, 1 } },
    { "ivory", { 255, 255, 240, 1 } }, { "khaki", { 240, 230, 140, 1 } },
    { "lavender", { 230, 230, 250, 1 } }, { "lavenderblush", { 255, 240, 245, 1 } },
    { "lawngreen", { 124, 252, 0, 1 } }, { "lemonchiffon", { 255, 250, 205, 1 } },
    { "lightblue", { 173, 216, 230, 1 } }, { "lightcoral", { 240, 128, 128, 1 } },
    { "lightcyan", { 224, 255, 255, 1 } }, { "lightgoldenrodyellow", { 250, 250, 210, 1 } },
    { "lightgray", { 211, 211, 211, 1 } }, { "lightgreen", { 144, 238, 144, 1 } },
    { "lightgrey", { 211, 211, 211, 1 } }, { "lightpink", { 255, 182, 193, 1 } },
    { "lightsalmon", { 255, 160, 122, 1 } }, { "lightseagreen", { 32, 178, 170, 1 } },
    { "lightskyblue", { 135, 206, 250, 1 } }, { "lightslategray", { 119, 136, 153, 1 } },
    { "lightslategrey", { 119, 136, 153, 1 } }, { "lightsteelblue", { 176, 196, 222, 1 } },
    { "lightyellow", { 255, 255, 224, 1 } }, { "lime", { 0, 255, 0, 1 } },
    { "limegreen", { 50, 205, 50, 1 } }, { "linen", { 250, 240, 230, 1 } },
    { "magenta", { 255, 0, 255, 1 } }, { "maroon", { 128, 0, 0, 1 } },
    { "mediumaquamarine", { 102, 205, 170, 1 } }, { "mediumblue", { 0, 0, 205, 1 } },
    { "mediumorchid", { 186, 85, 211, 1 } }, { "mediumpurple", { 147, 112, 219, 1 } },
    { "mediumseagreen", { 60, 179, 113, 1 } }, { "mediumslateblue", { 123, 104, 238, 1 } },
    { "mediumspringgreen", { 0, 250, 154, 1 } }, { "mediumturquoise", { 72, 209, 204, 1 } },
    { "mediumvioletred", { 199, 21, 133, 1 } }, { "midnightblue", { 25, 25, 112, 1 } },
    { "mintcream", { 245, 255, 250, 1 } }, { "mistyrose", { 255, 228, 225, 1 } },
    { "moccasin", { 255, 228, 181, 1 } }, { "navajowhite", { 255, 222, 173, 1 } },
    { "navy", { 0, 0, 128, 1 } }, { "oldlace", { 253, 245, 230, 1 } },
    { "olive", { 128, 128, 0, 1 } }, { "olivedrab", { 107, 142, 35, 1 } },
    { "orange", { 255, 165, 0, 1 } }, { "orangered", { 255, 69, 0, 1 } },
    { "orchid", { 218, 112, 214, 1 } }, { "palegoldenrod", { 238, 232, 170, 1 } },
    { "palegreen", { 152, 251, 152, 1 } }, { "paleturquoise", { 175, 238, 238, 1 } },
    { "palevioletred", { 219, 112, 147, 1 } }, { "papayawhip", { 255, 239, 213, 1 } },
    { "peachpuff", { 255, 218, 185, 1 } }, { "peru", { 205, 133, 63, 1 } },
    { "pink", { 255, 192, 203, 1 } }, { "plum", { 221, 160, 221, 1 } },
    { "powderblue", { 176, 224, 230, 1 } }, { "purple", { 128, 0, 128, 1 } },
    { "red", { 255, 0, 0, 1 } }, { "rosybrown", { 188, 143, 143, 1 } },
    { "royalblue", { 65, 105, 225, 1 } }, { "saddlebrown", { 139, 69, 19, 1 } },
    { "salmon", { 250, 128, 114, 1 } }, { "sandybrown", { 244, 164, 96, 1 } },
    { "seagreen", { 46, 139, 87, 1 } }, { "seashell", { 255, 245, 238, 1 } },
    { "sienna", { 160, 82, 45, 1 } }, { "silver", { 192, 192, 192, 1 } },
    { "skyblue", { 135, 206, 235, 1 } }, { "slateblue", { 106, 90, 205, 1 } },
    { "slategray", { 112, 128, 144, 1 } }, { "slategrey", { 112, 128, 144, 1 } },
    { "snow", { 255, 250, 250, 1 } }, { "springgreen", { 0, 255, 127, 1 } },
    { "steelblue", { 70, 130, 180, 1 } }, { "tan", { 210, 180, 140, 1 } },
    { "teal", { 0, 128, 128, 1 } }, { "thistle", { 216, 191, 216, 1 } },
    { "tomato", { 255, 99, 71, 1 } }, { "turquoise", { 64, 224, 208, 1 } },
    { "violet", { 238, 130, 238, 1 } }, { "wheat", { 245, 222, 179, 1 } },
    { "white", { 255, 255, 255, 1 } }, { "whitesmoke", { 245, 245, 245, 1 } },
    { "yellow", { 255, 255, 0, 1 } }, { "yellowgreen", { 154, 205, 50, 1 } }
};

// End of excerpt

%}

%error-verbose

%union { int i; float f; String *s; char b; sp::css::CSSLength::LengthUnit lu; sp::css::CSSKey csskey; sp::css::CSSValue *cssval; std::vector<sp::css::CSSValue*> *cssvalues; sp::css::CSSSelector *cssselector; }

%start css

%token _padding
%token _padding_top
%token _padding_right
%token _padding_bottom
%token _padding_left

%token _margin
%token _margin_top
%token _margin_right
%token _margin_bottom
%token _margin_left

%token _color
%token _background_color

%token _pixel
%token _em

%token _font_size

%type<csskey> key
%type<cssvalues> values
%type<lu> length_unit
%type<f> number
%type<cssval> length
%type<cssval> color
%type<cssselector> selector

%token<s> _identifier
%token<f> _float

%%

css: rules
	| 

rules: rule rules 
	| rule
	|

rule: selectors '{' key_value_pairs '}'

selectors: selector				{ res_map->push_back(std::make_pair($1, std::unordered_map<CSSKey, CSSValue*>())); }

selector: _identifier			{ $$ = spnew CSSNameSelector(*$1); }
	| '.' _identifier			{ $$ = spnew CSSClassSelector(*$2); }
	| selector '.' _identifier	{ $$ = spnew CSSClassSelector(*$3, $1); }
	| '#' _identifier			{ $$ = spnew CSSIDSelector(*$2); }
	| '*'						{ $$ = spnew CSSAllSelector(); }
	| selector ',' selector		{ $$ = spnew CSSListSelector($1, $3); }
	| selector ':' _identifier	{ 
		
		if(*$3 == "hover")
			$$ = spnew CSSHoverSelector($1);
		else
			$$ = spnew CSSFalseSelector();
		}

key_value_pairs: key_value_pair ';' key_value_pairs
	| key_value_pair ';'
	| key_value_pair


key_value_pair: key ':' values { 
	
	switch($1)
	{
	case PADDING:
		if($3->size() == 1)
			{
				res_map->back().second[PADDING] = (*$3)[0];
				res_map->back().second[PADDING_LEFT] = (*$3)[0];
				res_map->back().second[PADDING_RIGHT] = (*$3)[0];
				res_map->back().second[PADDING_TOP] = (*$3)[0];
				res_map->back().second[PADDING_BOTTOM] = (*$3)[0];
			}

		break;

	case MARGIN:
		if($3->size() == 1)
		{
			res_map->back().second[MARGIN] = (*$3)[0];
			res_map->back().second[MARGIN_LEFT] = (*$3)[0];
			res_map->back().second[MARGIN_RIGHT] = (*$3)[0];
			res_map->back().second[MARGIN_TOP] = (*$3)[0];
			res_map->back().second[MARGIN_BOTTOM] = (*$3)[0];
		}
	
		break;

	default:
		res_map->back().second[$1] = (*$3)[0];
	}

	spdel $3;
}

values: length					{ $$ = spnew std::vector<CSSValue*>; $$->push_back($1); }
	| color						{ $$ = spnew std::vector<CSSValue*>; $$->push_back($1); }

key: _padding					{ $$ = PADDING; }
	| _padding_top				{ $$ = PADDING_TOP; } 
	| _padding_right			{ $$ = PADDING_RIGHT; } 
	| _padding_bottom			{ $$ = PADDING_BOTTOM; } 
	| _padding_left				{ $$ = PADDING_LEFT; }
	
	| _margin					{ $$ = MARGIN; } 
	| _margin_top				{ $$ = MARGIN_TOP; } 
	| _margin_right				{ $$ = MARGIN_RIGHT; } 
	| _margin_bottom			{ $$ = MARGIN_BOTTOM; } 
	| _margin_left				{ $$ = MARGIN_LEFT; }

	| _color					{ $$ = COLOR; }
	| _background_color			{ $$ = BACKGROUND_COLOR; }

	| _font_size				{ $$ = FONT_SIZE; }

length: number length_unit		{ $$ = spnew CSSLength($1, $2); }

length_unit: _pixel				{ $$ = CSSLength::PIXEL; }
			| '%'				{ $$ = CSSLength::PERCENT; }
			| _em				{ $$ = CSSLength::EM; }


color: _identifier				{ $$ = spnew CSSColor(color_map[*$1]); }

number: _float					{ $$ = $1; }

%%

void yyerror(const char* s)
{
	SP_ERROR("SparkyCSS-Error: ", s, "( ln.", yylineno, ")");
}
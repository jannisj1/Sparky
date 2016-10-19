%{
#include <iostream>
#include "lexer.h"
#include "SparkyCSS.h"

using namespace sp::css;

CSSRules *res_map;

void yyerror (const char *s);

void push_value_vector(sp::css::CSSValue *val);
std::vector<sp::css::CSSValue*> *get_value_vector_ownership();

void add_key_value_pair(sp::css::CSSKey key, const std::vector<sp::css::CSSValue*>& v);

extern std::unordered_map<String, sp::css::CSSColor> color_map;

%}

%error-verbose

%union { int i; float f; String *s; char b; sp::css::CSSLength::LengthUnit lu; sp::css::CSSFlowDirection *fd; sp::css::CSSKey csskey; sp::css::CSSValue *cssval; std::vector<sp::css::CSSValue*> *cssvalues; sp::css::CSSSelector *cssselector; }

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
%token _background

%token _flow_children

%token _font_size

%token _pixel
%token _em
%token _rgb
%token _rgba

%token _down
%token _up
%token _left
%token _right
%token _down_wrap
%token _up_wrap
%token _left_wrap
%token _right_wrap
%token _static

%token _width
%token _height

%token _fit_children

%token _border;

%token _border_style;
%token _border_top_style;
%token _border_right_style;
%token _border_bottom_style;
%token _border_left_style;

%token _solid;
%token _none;

%token _border_width;
%token _border_top_width;
%token _border_right_width;
%token _border_bottom_width;
%token _border_left_width;

%token _border_color;
%token _border_top_color;
%token _border_right_color;
%token _border_bottom_color;
%token _border_left_color;

%type<csskey> key
%type<lu> length_unit
%type<fd> flow_direction
%type<f> number color_number
%type<cssselector> selector

%token<s> _identifier
%token<f> _float

%%

css: rules 

rules: rule rules 
	| rule
	|

rule: selectors '{' key_value_pairs '}'

selectors: selector				{ res_map->push_back(std::make_pair($1, std::unordered_map<CSSKey, CSSValue*>())); }

selector: _identifier			{ $$ = spnew CSSNameSelector(*$1); }
	| '.' _identifier			{ $$ = spnew CSSClassSelector(*$2); }
	| selector '.' _identifier	{ $$ = spnew CSSClassSelector(*$3, $1); }
	| '#' _identifier			{ $$ = spnew CSSIDSelector(*$2); }
	| selector selector			{ $$ = spnew CSSInsideSelector($1, $2); }
	| '*'						{ $$ = spnew CSSAllSelector(); }
	| selector ',' selector		{ $$ = spnew CSSListSelector($1, $3); }
	| selector ':' _identifier	{ 
		
		if(*$3 == "hover")
			$$ = spnew CSSHoverSelector($1);
		else if(*$3 == "focus")
			$$ = spnew CSSFocusSelector($1);
		else if(*$3 == "active")
			$$ = spnew CSSActiveSelector($1);
		else
		{
			yyerror("Unknown pseudo selector");
			$$ = spnew CSSFalseSelector();
		}

	}

key_value_pairs: key_value_pair ';' key_value_pairs
	| key_value_pair ';'
	| key_value_pair


key_value_pair: key ':' values { 
	std::vector<sp::css::CSSValue*> *vec = get_value_vector_ownership();
	add_key_value_pair($1, *vec);
	spdel vec;
}

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
	| _background				{ $$ = BACKGROUND; }

	| _font_size				{ $$ = FONT_SIZE; }

	| _flow_children			{ $$ = FLOW_CHILDREN; }

	| _width					{ $$ = WIDTH; }
	| _height					{ $$ = HEIGHT; }

	| _border					{ $$ = BORDER; }

	| _border_style				{ $$ = BORDER_STYLE; }
	| _border_top_style			{ $$ = BORDER_TOP_STYLE; }
	| _border_right_style		{ $$ = BORDER_RIGHT_STYLE; }
	| _border_bottom_style		{ $$ = BORDER_BOTTOM_STYLE; }
	| _border_left_style		{ $$ = BORDER_LEFT_STYLE; }

	| _border_width				{ $$ = BORDER_WIDTH; }
	| _border_top_width			{ $$ = BORDER_TOP_WIDTH; }
	| _border_right_width		{ $$ = BORDER_RIGHT_WIDTH; }
	| _border_bottom_width		{ $$ = BORDER_BOTTOM_WIDTH; }
	| _border_left_width		{ $$ = BORDER_LEFT_WIDTH; }
	
	| _border_color				{ $$ = BORDER_COLOR; }
	| _border_top_color			{ $$ = BORDER_TOP_COLOR; }
	| _border_right_color		{ $$ = BORDER_RIGHT_COLOR; }
	| _border_bottom_color		{ $$ = BORDER_BOTTOM_COLOR; }
	| _border_left_color		{ $$ = BORDER_LEFT_COLOR; }

values: values ',' value
	| values value
	| value

value: length
	| color
	| flow_direction
	| border_style

length: number length_unit		{ push_value_vector(spnew CSSLength($1, $2)); }
	| _fit_children				{ push_value_vector(spnew CSSLength(0.0f, CSSLength::FIT_CHILDREN)); }

length_unit: _pixel				{ $$ = CSSLength::PIXEL; }
			| '%'				{ $$ = CSSLength::PERCENT; }
			| _em				{ $$ = CSSLength::EM; }

color: _identifier				{ push_value_vector(spnew CSSColor(color_map[*$1])); }
	| _rgb '(' color_number ',' color_number ',' color_number ')'	{ push_value_vector(spnew CSSColor((byte)$3, (byte)$5, (byte)$7)); }
	| _rgba '(' color_number ',' color_number ',' color_number ',' number ')'	{ push_value_vector(spnew CSSColor((byte)$3, (byte)$5, (byte)$7, $9 * 255.0f)); }

color_number: number			{ $$ = $1; }
	| number '%'				{ $$ = ($1 / 100.0f) * 255.0f; }

number: _float					{ $$ = $1; }

flow_direction: _down			{ push_value_vector(spnew CSSFlowDirection(CSSFlowDirection::DOWN)); }
	| _up						{ push_value_vector(spnew CSSFlowDirection(CSSFlowDirection::UP)); }
	| _left						{ push_value_vector(spnew CSSFlowDirection(CSSFlowDirection::LEFT)); }
	| _right					{ push_value_vector(spnew CSSFlowDirection(CSSFlowDirection::RIGHT)); }
	| _down_wrap				{ push_value_vector(spnew CSSFlowDirection(CSSFlowDirection::DOWN, true)); }
	| _up_wrap					{ push_value_vector(spnew CSSFlowDirection(CSSFlowDirection::UP, true)); }
	| _left_wrap				{ push_value_vector(spnew CSSFlowDirection(CSSFlowDirection::LEFT, true)); }
	| _right_wrap				{ push_value_vector(spnew CSSFlowDirection(CSSFlowDirection::RIGHT, true)); }
	| _static					{ push_value_vector(spnew CSSFlowDirection(CSSFlowDirection::STATIC)); }

border_style: _solid			{ push_value_vector(spnew CSSBorderStyle(CSSBorderStyle::SOLID)); }
	| _none						{ push_value_vector(spnew CSSBorderStyle(CSSBorderStyle::NONE)); }
%%

void yyerror(const char* s)
{
	SP_ERROR("SparkyCSS-Error: ", s, "(ln.", yylineno, ")");
}

static std::vector<sp::css::CSSValue*> *current_value_vec = nullptr;

void push_value_vector(sp::css::CSSValue *val)
{
	if(!current_value_vec)
		current_value_vec = spnew std::vector<sp::css::CSSValue*>();

	current_value_vec->push_back(val);
}

std::vector<sp::css::CSSValue*> *get_value_vector_ownership()
{
	std::vector<sp::css::CSSValue*> *res = current_value_vec;
	current_value_vec = nullptr;
	return res;
}
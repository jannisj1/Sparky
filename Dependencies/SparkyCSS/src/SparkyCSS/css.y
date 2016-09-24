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

%}

%error-verbose

%union { int i; float f; String *s; char b; sp::css::LengthUnit lu; sp::css::CSSKey csskey; sp::css::CSSValue *cssval; std::vector<sp::css::CSSValue*> *cssvalues; }

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

%token _pixel_suffix

%type<csskey> key
%type<cssvalues> values
%type<lu> length_unit
%type<f> number
%type<cssval> length

%token<s> _identifier
%token<f> _float

%%

css: rules
	| ;

rules: rule rules 
	| rule

rule: selector_list '{' key_value_pairs '}'

selector_list: _identifier		{ res_map->push_back(std::make_pair(std::vector<CSSSelector*>{{ spnew CSSNameSelector(*$1) }}, std::unordered_map<sp::css::CSSKey, sp::css::CSSValue*>())); }
	| '#' _identifier			{ res_map->push_back(std::make_pair(std::vector<CSSSelector*>{{ spnew CSSIDSelector(*$2) }}, std::unordered_map<sp::css::CSSKey, sp::css::CSSValue*>())); }

key_value_pairs: key_value_pair ';' key_value_pairs
	| key_value_pair
	| 

key_value_pair: key ':' values { 
	
	if($1 == PADDING)
	{
		if($3->size() == 1)
		{
			res_map->back().second[PADDING_LEFT] = (*$3)[0];
			res_map->back().second[PADDING_RIGHT] = (*$3)[0];
			res_map->back().second[PADDING_TOP] = (*$3)[0];
			res_map->back().second[PADDING_BOTTOM] = (*$3)[0];
		}
	}
	else if($1 == MARGIN)
	{
		if($3->size() == 1)
		{
			res_map->back().second[MARGIN_LEFT] = (*$3)[0];
			res_map->back().second[MARGIN_RIGHT] = (*$3)[0];
			res_map->back().second[MARGIN_TOP] = (*$3)[0];
			res_map->back().second[MARGIN_BOTTOM] = (*$3)[0];
		}
	}
	else
	{
		res_map->back().second[$1] = (*$3)[0];
	}
	
	spdel $3;
}

values: length					{ $$ = spnew std::vector<CSSValue*>; $$->push_back($1); }

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

length: number length_unit		{ $$ = spnew CSSLength($1, $2); }

length_unit: _pixel_suffix		{ $$ = PIXEL; }
			| '%'				{ $$ = PERCENT; }

number: _float					{ $$ = $1; }

%%

void yyerror(const char* s)
{
	SP_ERROR("SparkyCSS-Error: ", s, "( ln.", yylineno, ")");
}
%{
#include <string>
#include <iostream>
#include "SparkyCSS.h"
#include "parser.h"

%}

%option noyywrap
%option yylineno

%%

"/*"((\*+[^/*])|([^*]))*\**"*/" ;
"//"[^\n]*						;

"padding" return _padding;
"padding-top" return _padding_top;
"padding-right" return _padding_right;
"padding-bottom" return _padding_bottom;
"padding-left" return _padding_left;

"margin" return _margin;
"margin-top" return _margin_top;
"margin-right" return _margin_right;
"margin-bottom" return _margin_bottom;
"margin-left" return _margin_left;

"color" return _color;
"background-color" return _background_color;

"px" return _pixel;
"em" return _em;

"font-size" return _font_size;

([0-9]+) |
([0-9]*[.][0-9]+)			{ yylval.f = std::stof(yytext); return _float; }

[_a-zA-Z][_a-zA-Z0-9]*		{ yylval.s = new std::string(yytext); return _identifier; }

[ \n\t\r]			;
.					return yytext[0];

%%
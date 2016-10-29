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
"background" return _background;

"font-size" return _font_size;

"flow-children" return _flow_children;

"down" return _down;
"right" return _right;

"down-wrap" return _down_wrap;
"right-wrap" return _right_wrap;

"no-flow" return _no_flow;

"width" return _width;
"height" return _height;

"fit-children" return _fit_children;

"px" return _pixel;
"em" return _em;

"rgb" return _rgb;
"rgba" return _rgba;


"border" return _border;

"border-style" return _border_style;
"border-top-style" return _border_top_style;
"border-right-style" return _border_right_style;
"border-bottom-style" return _border_bottom_style;
"border-left-style" return _border_left_style;

"solid" return _solid;
"none" return _none;

"border-width" return _border_width;
"border-top-width" return _border_top_width;
"border-right-width" return _border_right_width;
"border-bottom-width" return _border_bottom_width;
"border-left-width" return _border_left_width;

"border-color" return _border_color;
"border-top-color" return _border_top_color;
"border-right-color" return _border_right_color;
"border-bottom-color" return _border_bottom_color;
"border-left-color" return _border_left_color;

"justify-content" return _justify_content;

"flex-end" return _end;
"end" return _end;
"flex-start" return _start;
"start" return _start;
"center" return _center;
"space-around" return _space_around;
"space-between" return _space_between;

"align-items" return _align_items;

"position" return _position;

"relative" return _relative;
"absolute" return _absolute;
"fixed" return _fixed;
"static" return _static;

"left" return _left;
"top" return _top;

"display" return _display;
"auto" return _auto;

([0-9]+) |
([0-9]*[.][0-9]+)			{ yylval.f = std::stof(yytext); return _float; }

[_a-zA-Z][_a-zA-Z0-9]*		{ yylval.s = new std::string(yytext); return _identifier; }

[ \n\t\r]			;
.					return yytext[0];

%%
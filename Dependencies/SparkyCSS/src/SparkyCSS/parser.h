/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     _padding = 258,
     _padding_top = 259,
     _padding_right = 260,
     _padding_bottom = 261,
     _padding_left = 262,
     _margin = 263,
     _margin_top = 264,
     _margin_right = 265,
     _margin_bottom = 266,
     _margin_left = 267,
     _color = 268,
     _background_color = 269,
     _background = 270,
     _flow_children = 271,
     _font_size = 272,
     _pixel = 273,
     _em = 274,
     _rgb = 275,
     _rgba = 276,
     _down = 277,
     _right = 278,
     _down_wrap = 279,
     _right_wrap = 280,
     _no_flow = 281,
     _width = 282,
     _height = 283,
     _fit_children = 284,
     _border = 285,
     _border_style = 286,
     _border_top_style = 287,
     _border_right_style = 288,
     _border_bottom_style = 289,
     _border_left_style = 290,
     _solid = 291,
     _none = 292,
     _border_width = 293,
     _border_top_width = 294,
     _border_right_width = 295,
     _border_bottom_width = 296,
     _border_left_width = 297,
     _border_color = 298,
     _border_top_color = 299,
     _border_right_color = 300,
     _border_bottom_color = 301,
     _border_left_color = 302,
     _justify_content = 303,
     _end = 304,
     _start = 305,
     _center = 306,
     _space_around = 307,
     _space_between = 308,
     _align_items = 309,
     _position = 310,
     _relative = 311,
     _absolute = 312,
     _fixed = 313,
     _static = 314,
     _left = 315,
     _top = 316,
     _auto = 317,
     _display = 318,
     _identifier = 319,
     _float = 320
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 23 "css.y"
 int i; float f; String *s; char b; sp::css::CSSLength::LengthUnit lu; sp::css::CSSFlowDirection *fd; sp::css::CSSKey csskey; sp::css::CSSValue *cssval; std::vector<sp::css::CSSValue*> *cssvalues; sp::css::CSSSelector *cssselector; 

/* Line 2058 of yacc.c  */
#line 125 "parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PARSER_H_INCLUDED  */

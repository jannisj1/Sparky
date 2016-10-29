/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "css.y"

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


/* Line 371 of yacc.c  */
#line 88 "parser.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
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
/* Line 387 of yacc.c  */
#line 23 "css.y"
 int i; float f; String *s; char b; sp::css::CSSLength::LengthUnit lu; sp::css::CSSFlowDirection *fd; sp::css::CSSKey csskey; sp::css::CSSValue *cssval; std::vector<sp::css::CSSValue*> *cssvalues; sp::css::CSSSelector *cssselector; 

/* Line 387 of yacc.c  */
#line 199 "parser.cpp"
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

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 227 "parser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   161

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNRULES -- Number of states.  */
#define YYNSTATES  126

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   320

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    69,     2,    74,     2,     2,
      75,    76,    70,     2,    71,     2,    68,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    72,    73,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    66,     2,    67,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    11,    16,    18,    20,
      23,    27,    30,    33,    35,    39,    43,    47,    50,    52,
      53,    57,    59,    61,    63,    65,    67,    69,    71,    73,
      75,    77,    79,    81,    83,    85,    87,    89,    91,    93,
      95,    97,    99,   101,   103,   105,   107,   109,   111,   113,
     115,   117,   119,   121,   123,   125,   127,   129,   131,   133,
     135,   137,   141,   144,   146,   148,   150,   152,   154,   156,
     158,   160,   163,   165,   167,   169,   171,   173,   182,   193,
     195,   198,   200,   202,   204,   206,   208,   210,   212,   214,
     216,   218,   220,   222,   224,   226,   228,   230,   232,   233
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      78,     0,    -1,    79,    -1,    80,    79,    -1,    80,    -1,
      -1,    81,    66,    83,    67,    -1,    82,    -1,    64,    -1,
      68,    64,    -1,    82,    68,    64,    -1,    69,    64,    -1,
      82,    82,    -1,    70,    -1,    82,    71,    82,    -1,    82,
      72,    64,    -1,    84,    73,    83,    -1,    84,    73,    -1,
      84,    -1,    -1,    85,    72,    86,    -1,     3,    -1,     4,
      -1,     5,    -1,     6,    -1,     7,    -1,     8,    -1,     9,
      -1,    10,    -1,    11,    -1,    12,    -1,    13,    -1,    14,
      -1,    15,    -1,    17,    -1,    16,    -1,    27,    -1,    28,
      -1,    30,    -1,    31,    -1,    32,    -1,    33,    -1,    34,
      -1,    35,    -1,    38,    -1,    39,    -1,    40,    -1,    41,
      -1,    42,    -1,    43,    -1,    44,    -1,    45,    -1,    46,
      -1,    47,    -1,    48,    -1,    54,    -1,    55,    -1,    60,
      -1,    61,    -1,    63,    -1,    64,    -1,    86,    71,    87,
      -1,    86,    87,    -1,    87,    -1,    88,    -1,    90,    -1,
      93,    -1,    94,    -1,    95,    -1,    96,    -1,    97,    -1,
      92,    89,    -1,    29,    -1,    18,    -1,    74,    -1,    19,
      -1,    64,    -1,    20,    75,    91,    71,    91,    71,    91,
      76,    -1,    21,    75,    91,    71,    91,    71,    91,    71,
      92,    76,    -1,    92,    -1,    92,    74,    -1,    65,    -1,
      22,    -1,    23,    -1,    24,    -1,    25,    -1,    26,    -1,
      36,    -1,    37,    -1,    49,    -1,    50,    -1,    51,    -1,
      52,    -1,    53,    -1,    59,    -1,    56,    -1,    57,    -1,
      58,    -1,    -1,    62,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   120,   120,   122,   123,   124,   126,   128,   130,   131,
     132,   133,   134,   135,   136,   137,   153,   154,   155,   156,
     159,   166,   167,   168,   169,   170,   172,   173,   174,   175,
     176,   178,   180,   181,   183,   185,   187,   188,   190,   192,
     193,   194,   195,   196,   198,   199,   200,   201,   202,   204,
     205,   206,   207,   208,   210,   211,   213,   214,   215,   217,
     219,   228,   229,   230,   233,   234,   235,   236,   237,   238,
     239,   242,   243,   246,   247,   248,   251,   252,   253,   256,
     257,   259,   262,   263,   264,   265,   266,   269,   270,   273,
     274,   275,   276,   277,   280,   281,   282,   283,   286,   287
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "_padding", "_padding_top",
  "_padding_right", "_padding_bottom", "_padding_left", "_margin",
  "_margin_top", "_margin_right", "_margin_bottom", "_margin_left",
  "_color", "_background_color", "_background", "_flow_children",
  "_font_size", "_pixel", "_em", "_rgb", "_rgba", "_down", "_right",
  "_down_wrap", "_right_wrap", "_no_flow", "_width", "_height",
  "_fit_children", "_border", "_border_style", "_border_top_style",
  "_border_right_style", "_border_bottom_style", "_border_left_style",
  "_solid", "_none", "_border_width", "_border_top_width",
  "_border_right_width", "_border_bottom_width", "_border_left_width",
  "_border_color", "_border_top_color", "_border_right_color",
  "_border_bottom_color", "_border_left_color", "_justify_content", "_end",
  "_start", "_center", "_space_around", "_space_between", "_align_items",
  "_position", "_relative", "_absolute", "_fixed", "_static", "_left",
  "_top", "_auto", "_display", "_identifier", "_float", "'{'", "'}'",
  "'.'", "'#'", "'*'", "','", "':'", "';'", "'%'", "'('", "')'", "$accept",
  "css", "rules", "rule", "selectors", "selector", "key_value_pairs",
  "key_value_pair", "key", "values", "value", "length", "length_unit",
  "color", "color_number", "number", "flow_direction", "border_style",
  "content_justification", "position", "display", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   123,   125,    46,    35,
      42,    44,    58,    59,    37,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    77,    78,    79,    79,    79,    80,    81,    82,    82,
      82,    82,    82,    82,    82,    82,    83,    83,    83,    83,
      84,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    86,    86,    86,    87,    87,    87,    87,    87,    87,
      87,    88,    88,    89,    89,    89,    90,    90,    90,    91,
      91,    92,    93,    93,    93,    93,    93,    94,    94,    95,
      95,    95,    95,    95,    96,    96,    96,    96,    97,    97
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     0,     4,     1,     1,     2,
       3,     2,     2,     1,     3,     3,     3,     2,     1,     0,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     8,    10,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     8,     0,     0,    13,     0,     2,     4,     0,     7,
       9,    11,     1,     3,    19,     0,     0,     0,    12,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    35,    34,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,     0,
      18,     0,     9,    14,    15,     6,    17,    98,    16,     0,
       0,    82,    83,    84,    85,    86,    72,    87,    88,    89,
      90,    91,    92,    93,    95,    96,    97,    94,    99,    76,
      81,    20,    63,    64,    65,     0,    66,    67,    68,    69,
      70,     0,     0,    98,    62,    73,    75,    74,    71,     0,
      79,     0,    61,     0,    80,     0,     0,     0,     0,     0,
       0,     0,    77,     0,     0,    78
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,     7,     8,    18,    59,    60,    61,    91,
      92,    93,   108,    94,   109,   110,    96,    97,    98,    99,
     100
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -71
static const yytype_int8 yypact[] =
{
     -14,   -71,   -49,   -46,   -71,    19,   -71,   -14,   -40,    59,
     -71,   -71,   -71,   -71,    -3,   -42,   -14,   -30,    59,   -71,
     -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,
     -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,
     -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,
     -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -47,
     -25,   -23,   -71,    59,   -71,   -71,    -3,    96,   -71,   -12,
      -1,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,
     -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,
     -71,    44,   -71,   -71,   -71,    -2,   -71,   -71,   -71,   -71,
     -71,    10,    10,    96,   -71,   -71,   -71,   -71,   -71,     5,
       3,     7,   -71,    10,   -71,    10,    12,    14,    10,    10,
      13,    15,   -71,    10,    16,   -71
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -71,   -71,    83,   -71,   -71,    46,    25,   -71,   -71,   -71,
     -70,   -71,   -71,   -71,   -31,   -44,   -71,   -71,   -71,   -71,
     -71
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    10,   105,   106,    11,    12,
      65,   104,    62,    95,    34,    35,    14,    36,    37,    38,
      39,    40,    41,   112,    64,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,     9,    95,    66,    67,
       1,    53,    54,     9,     2,     3,     4,    55,    56,    95,
      57,    58,    63,   101,    69,    70,    71,    72,    73,    74,
      75,   111,   107,    76,   102,    90,   113,   114,   115,   124,
      77,    78,   116,   118,   117,   119,   123,   120,   121,   122,
      13,    68,   125,    79,    80,    81,    82,    83,     0,     0,
      84,    85,    86,    87,     0,     0,    88,     0,    89,    90,
       0,     0,     0,     0,     0,   103,    69,    70,    71,    72,
      73,    74,    75,     1,     0,    76,     0,    15,     3,     4,
      16,    17,    77,    78,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    79,    80,    81,    82,    83,
       0,     0,    84,    85,    86,    87,     0,     0,    88,     0,
      89,    90
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-71)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    64,    18,    19,    64,     0,
      67,    91,    64,    67,    27,    28,    66,    30,    31,    32,
      33,    34,    35,   103,    64,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,     0,    91,    73,    72,
      64,    54,    55,     7,    68,    69,    70,    60,    61,   103,
      63,    64,    16,    75,    20,    21,    22,    23,    24,    25,
      26,   102,    74,    29,    75,    65,    71,    74,    71,   123,
      36,    37,   113,    71,   115,    71,    71,   118,   119,    76,
       7,    66,    76,    49,    50,    51,    52,    53,    -1,    -1,
      56,    57,    58,    59,    -1,    -1,    62,    -1,    64,    65,
      -1,    -1,    -1,    -1,    -1,    71,    20,    21,    22,    23,
      24,    25,    26,    64,    -1,    29,    -1,    68,    69,    70,
      71,    72,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    49,    50,    51,    52,    53,
      -1,    -1,    56,    57,    58,    59,    -1,    -1,    62,    -1,
      64,    65
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    64,    68,    69,    70,    78,    79,    80,    81,    82,
      64,    64,     0,    79,    66,    68,    71,    72,    82,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    27,    28,    30,    31,    32,    33,
      34,    35,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    54,    55,    60,    61,    63,    64,    83,
      84,    85,    64,    82,    64,    67,    73,    72,    83,    20,
      21,    22,    23,    24,    25,    26,    29,    36,    37,    49,
      50,    51,    52,    53,    56,    57,    58,    59,    62,    64,
      65,    86,    87,    88,    90,    92,    93,    94,    95,    96,
      97,    75,    75,    71,    87,    18,    19,    74,    89,    91,
      92,    91,    87,    71,    74,    71,    91,    91,    71,    71,
      91,    91,    76,    71,    92,    76
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 7:
/* Line 1792 of yacc.c  */
#line 128 "css.y"
    { res_map->push_back(std::make_pair((yyvsp[(1) - (1)].cssselector), std::unordered_map<CSSKey, CSSValue*>())); }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 130 "css.y"
    { (yyval.cssselector) = spnew CSSNameSelector(*(yyvsp[(1) - (1)].s)); }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 131 "css.y"
    { (yyval.cssselector) = spnew CSSClassSelector(*(yyvsp[(2) - (2)].s)); }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 132 "css.y"
    { (yyval.cssselector) = spnew CSSClassSelector(*(yyvsp[(3) - (3)].s), (yyvsp[(1) - (3)].cssselector)); }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 133 "css.y"
    { (yyval.cssselector) = spnew CSSIDSelector(*(yyvsp[(2) - (2)].s)); }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 134 "css.y"
    { (yyval.cssselector) = spnew CSSInsideSelector((yyvsp[(1) - (2)].cssselector), (yyvsp[(2) - (2)].cssselector)); }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 135 "css.y"
    { (yyval.cssselector) = spnew CSSAllSelector(); }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 136 "css.y"
    { (yyval.cssselector) = spnew CSSListSelector((yyvsp[(1) - (3)].cssselector), (yyvsp[(3) - (3)].cssselector)); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 137 "css.y"
    { 
		
		if(*(yyvsp[(3) - (3)].s) == "hover")
			(yyval.cssselector) = spnew CSSHoverSelector((yyvsp[(1) - (3)].cssselector));
		else if(*(yyvsp[(3) - (3)].s) == "focus")
			(yyval.cssselector) = spnew CSSFocusSelector((yyvsp[(1) - (3)].cssselector));
		else if(*(yyvsp[(3) - (3)].s) == "active")
			(yyval.cssselector) = spnew CSSActiveSelector((yyvsp[(1) - (3)].cssselector));
		else
		{
			yyerror("Unknown pseudo selector");
			(yyval.cssselector) = spnew CSSFalseSelector();
		}

	}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 159 "css.y"
    { 
	std::vector<sp::css::CSSValue*> *vec = get_value_vector_ownership();
	add_key_value_pair((yyvsp[(1) - (3)].csskey), *vec);
	spdel vec;
}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 166 "css.y"
    { (yyval.csskey) = PADDING; }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 167 "css.y"
    { (yyval.csskey) = PADDING_TOP; }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 168 "css.y"
    { (yyval.csskey) = PADDING_RIGHT; }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 169 "css.y"
    { (yyval.csskey) = PADDING_BOTTOM; }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 170 "css.y"
    { (yyval.csskey) = PADDING_LEFT; }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 172 "css.y"
    { (yyval.csskey) = MARGIN; }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 173 "css.y"
    { (yyval.csskey) = MARGIN_TOP; }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 174 "css.y"
    { (yyval.csskey) = MARGIN_RIGHT; }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 175 "css.y"
    { (yyval.csskey) = MARGIN_BOTTOM; }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 176 "css.y"
    { (yyval.csskey) = MARGIN_LEFT; }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 178 "css.y"
    { (yyval.csskey) = COLOR; }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 180 "css.y"
    { (yyval.csskey) = BACKGROUND_COLOR; }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 181 "css.y"
    { (yyval.csskey) = BACKGROUND; }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 183 "css.y"
    { (yyval.csskey) = FONT_SIZE; }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 185 "css.y"
    { (yyval.csskey) = FLOW_CHILDREN; }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 187 "css.y"
    { (yyval.csskey) = WIDTH; }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 188 "css.y"
    { (yyval.csskey) = HEIGHT; }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 190 "css.y"
    { (yyval.csskey) = BORDER; }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 192 "css.y"
    { (yyval.csskey) = BORDER_STYLE; }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 193 "css.y"
    { (yyval.csskey) = BORDER_TOP_STYLE; }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 194 "css.y"
    { (yyval.csskey) = BORDER_RIGHT_STYLE; }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 195 "css.y"
    { (yyval.csskey) = BORDER_BOTTOM_STYLE; }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 196 "css.y"
    { (yyval.csskey) = BORDER_LEFT_STYLE; }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 198 "css.y"
    { (yyval.csskey) = BORDER_WIDTH; }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 199 "css.y"
    { (yyval.csskey) = BORDER_TOP_WIDTH; }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 200 "css.y"
    { (yyval.csskey) = BORDER_RIGHT_WIDTH; }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 201 "css.y"
    { (yyval.csskey) = BORDER_BOTTOM_WIDTH; }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 202 "css.y"
    { (yyval.csskey) = BORDER_LEFT_WIDTH; }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 204 "css.y"
    { (yyval.csskey) = BORDER_COLOR; }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 205 "css.y"
    { (yyval.csskey) = BORDER_TOP_COLOR; }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 206 "css.y"
    { (yyval.csskey) = BORDER_RIGHT_COLOR; }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 207 "css.y"
    { (yyval.csskey) = BORDER_BOTTOM_COLOR; }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 208 "css.y"
    { (yyval.csskey) = BORDER_LEFT_COLOR; }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 210 "css.y"
    { (yyval.csskey) = JUSTIFY_CONTENT; }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 211 "css.y"
    { (yyval.csskey) = ALIGN_ITEMS; }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 213 "css.y"
    { (yyval.csskey) = POSITION; }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 214 "css.y"
    { (yyval.csskey) = X; }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 215 "css.y"
    { (yyval.csskey) = Y; }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 217 "css.y"
    { (yyval.csskey) = DISPLAY; }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 219 "css.y"
    { 
		if(*(yyvsp[(1) - (1)].s) == "x") (yyval.csskey) = X;
		else if(*(yyvsp[(1) - (1)].s) == "y") (yyval.csskey) = Y;
		else
		{
			SP_ERROR("Unknown Css-Property: ", *(yyvsp[(1) - (1)].s));
		}
	 }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 242 "css.y"
    { push_value_vector(spnew CSSLength((yyvsp[(1) - (2)].f), (yyvsp[(2) - (2)].lu))); }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 243 "css.y"
    { push_value_vector(spnew CSSLength(0.0f, CSSLength::FIT_CHILDREN)); }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 246 "css.y"
    { (yyval.lu) = CSSLength::PIXEL; }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 247 "css.y"
    { (yyval.lu) = CSSLength::PERCENT; }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 248 "css.y"
    { (yyval.lu) = CSSLength::EM; }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 251 "css.y"
    { push_value_vector(spnew CSSColor(color_map[*(yyvsp[(1) - (1)].s)])); }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 252 "css.y"
    { push_value_vector(spnew CSSColor((byte)(yyvsp[(3) - (8)].f), (byte)(yyvsp[(5) - (8)].f), (byte)(yyvsp[(7) - (8)].f))); }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 253 "css.y"
    { push_value_vector(spnew CSSColor((byte)(yyvsp[(3) - (10)].f), (byte)(yyvsp[(5) - (10)].f), (byte)(yyvsp[(7) - (10)].f), (yyvsp[(9) - (10)].f) * 255.0f)); }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 256 "css.y"
    { (yyval.f) = (yyvsp[(1) - (1)].f); }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 257 "css.y"
    { (yyval.f) = ((yyvsp[(1) - (2)].f) / 100.0f) * 255.0f; }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 259 "css.y"
    { (yyval.f) = (yyvsp[(1) - (1)].f); }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 262 "css.y"
    { push_value_vector(spnew CSSFlowDirection(CSSFlowDirection::DOWN)); }
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 263 "css.y"
    { push_value_vector(spnew CSSFlowDirection(CSSFlowDirection::RIGHT)); }
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 264 "css.y"
    { push_value_vector(spnew CSSFlowDirection(CSSFlowDirection::DOWN, true)); }
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 265 "css.y"
    { push_value_vector(spnew CSSFlowDirection(CSSFlowDirection::RIGHT, true)); }
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 266 "css.y"
    { push_value_vector(spnew CSSFlowDirection(CSSFlowDirection::NOFLOW)); }
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 269 "css.y"
    { push_value_vector(spnew CSSBorderStyle(CSSBorderStyle::SOLID)); }
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 270 "css.y"
    { push_value_vector(spnew CSSBorderStyle(CSSBorderStyle::NONE)); }
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 273 "css.y"
    { push_value_vector(spnew CSSContentJustification(CSSContentJustification::END)); }
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 274 "css.y"
    { push_value_vector(spnew CSSContentJustification(CSSContentJustification::START)); }
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 275 "css.y"
    { push_value_vector(spnew CSSContentJustification(CSSContentJustification::CENTER)); }
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 276 "css.y"
    { push_value_vector(spnew CSSContentJustification(CSSContentJustification::SPACE_AROUND)); }
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 277 "css.y"
    { push_value_vector(spnew CSSContentJustification(CSSContentJustification::SPACE_BETWEEN)); }
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 280 "css.y"
    {  push_value_vector(spnew CSSPosition(CSSPosition::STATIC)); }
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 281 "css.y"
    {  push_value_vector(spnew CSSPosition(CSSPosition::RELATIVE)); }
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 282 "css.y"
    {  push_value_vector(spnew CSSPosition(CSSPosition::ABSOLUTE)); }
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 283 "css.y"
    {  push_value_vector(spnew CSSPosition(CSSPosition::FIXED)); }
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 287 "css.y"
    {  push_value_vector(spnew CSSDisplay(CSSDisplay::AUTO)); }
    break;


/* Line 1792 of yacc.c  */
#line 2058 "parser.cpp"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 290 "css.y"


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
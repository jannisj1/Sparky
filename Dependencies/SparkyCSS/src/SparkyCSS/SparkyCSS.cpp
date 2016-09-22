#include "SparkyCSS.h"
#include "parser.h"
#include "lexer.h"

extern sp::css::CSSRules *res_map; // res_map defined in parser.cpp (parser.y)

namespace sp { namespace css {

	// CSSRules

	void CSSParser::Parse(CSSRules& rules,  const String& css)
	{
		res_map = &rules; 
		
		yyset_lineno(1);
		yy_scan_bytes(css.data(), css.length());
		yyparse();

		return;
	}

} }
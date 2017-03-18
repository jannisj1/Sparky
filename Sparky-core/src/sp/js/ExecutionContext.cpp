#include <sp/sp.h>
#include "ExecutionContext.h"

#include <sstream>

namespace sp { namespace js {
	
	ExecutionContext::ExecutionContext(uint flags)
		: m_Flags(flags)
	{
		
	}

	ExecutionContext::~ExecutionContext()
	{

	}

	String ExecutionContext::EvaluateDomExpression(const String& val)
	{
		std::stringstream expression;
		std::stringstream result;

		bool inExpression = false;
		int32 curlyStack = 0;

		for (uint32 i = 0; i < val.length(); i++)
		{
			if (!inExpression)
			{
				if (val[i] == '{' && val[i > 0 ? i - 1 : 0] == '$')
				{
					inExpression = true;
					curlyStack = 0;
				}
				else if(val[i] != '$' && val[i + 1 < val.length() ? i + 1 : i] != '{')
				{
					result << val[i];
				}
			}
			else
			{
				if (val[i] == '{')
					curlyStack++;
				else if (val[i] == '}')
				{
					if (curlyStack == 0)
					{
						result << EvaluateString(expression.str());
						expression.str(std::string());

						inExpression = false;
						continue;
					}
					curlyStack--;
				}

				expression << val[i];
			}
		}

		return result.str();
	}

} }

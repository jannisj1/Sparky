#pragma once
#include <sp/sp.h>
#include <sp/String.h>

namespace sp { namespace js {

	enum ExecutionFlags {
		TRANSPILE_TO_ES_5 = 1,
	};

	class ExecutionContext
	{
		uint m_Flags;
		friend class ExecutionEngine;

	public:
		ExecutionContext(uint flags);
		~ExecutionContext();

		virtual void EvaluateNoTransform(const String& src, const String& filename = "inline") = 0;
		
		virtual void Evaluate(const String& src, const String& filename = "inline") = 0;
		virtual String EvaluateString(const String& src, const String& filename = "inline") = 0;
		virtual int32 EvaluateInt32(const String& src, const String& filename = "inline") = 0;
		virtual double EvaluateDouble(const String& src, const String& filename = "inline") = 0;

		String EvaluateDomExpression(const String& val);
	};

} }

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

	public:
		ExecutionContext(uint flags);
		~ExecutionContext();

		virtual void Evaluate(const String& src, const String& filename = "inline") = 0;
	};

} }

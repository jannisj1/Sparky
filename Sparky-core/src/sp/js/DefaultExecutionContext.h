#pragma once
#include "ExecutionContext.h"
#include "duktape.h"

namespace sp { namespace js {

	class DefaultExecutionContext : public ExecutionContext
	{
		duk_context *m_Ctx;
		uint m_Flags;

	public:
		DefaultExecutionContext(uint flags);
		~DefaultExecutionContext();

		void Evaluate(const String& src, const String& filename = "inline") override;
	};

} }
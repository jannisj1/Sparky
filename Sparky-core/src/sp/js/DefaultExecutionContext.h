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

		void EvaluateNoTransform(const String& src, const String& filename = "inline") override;
		void Evaluate(const String& src, const String& filename = "inline") override;
		String EvaluateString(const String& src, const String& filename = "inline") override;
		int32 EvaluateInt32(const String& src, const String& filename = "inline") override;
		double EvaluateDouble(const String& src, const String& filename = "inline") override;

	private:
		String BabelTransform(const String& src);
	};

} }
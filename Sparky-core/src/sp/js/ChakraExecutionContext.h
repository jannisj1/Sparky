#pragma once
#include "ExecutionContext.h"

#include <ChakraCore.h>

namespace sp { namespace js {

	class ChakraExecutionContext : public ExecutionContext
	{
		uint m_Flags;

		JsContextRef m_Context;
		uint32 m_CurrentSourceContext = 0;

	public:
		ChakraExecutionContext(uint flags, JsRuntimeHandle runtime);
		~ChakraExecutionContext();

		void EvaluateNoTransform(const String& src, const String& filename = "inline") override;
		void Evaluate(const String& src, const String& filename = "inline") override;
		String EvaluateString(const String& src, const String& filename = "inline") override;
		int32 EvaluateInt32(const String& src, const String& filename = "inline") override;
		double EvaluateDouble(const String& src, const String& filename = "inline") override;

	private:
		void SetCallback(JsValueRef object, const wchar_t *propertyName, JsNativeFunction callback, void *callbackState);
	};

} }

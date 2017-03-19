#pragma once
#include "ExecutionEngine.h"
#include "ChakraExecutionContext.h"

#include <ChakraCore.h>

namespace sp { namespace js {

	class ChakraEngine : public ExecutionEngine
	{
		JsRuntimeHandle m_Runtime;

	public:
		ChakraEngine();
		~ChakraEngine();

	protected:
		ExecutionContext *NewContext() override;
	};

} }

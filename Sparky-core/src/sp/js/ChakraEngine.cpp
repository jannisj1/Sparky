#include <sp/sp.h>
#include <sp/system/Memory.h>

#include "ChakraEngine.h"
#include "ChakraExecutionContext.h"

namespace sp { namespace js {

	ChakraEngine::ChakraEngine()
		: ExecutionEngine(0)
	{
		JsCreateRuntime(JsRuntimeAttributeNone, nullptr, &m_Runtime);
	}

	ChakraEngine::~ChakraEngine()
	{

	}

	ExecutionContext *ChakraEngine::NewContext()
	{
		return spnew ChakraExecutionContext(m_Flags, m_Runtime);
	}

} }

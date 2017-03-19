#include "sp/sp.h"
#include "sp/system/Memory.h"
#include "DefaultEngine.h"

namespace sp { namespace js {

	DefaultEngine::DefaultEngine()
		: ExecutionEngine(ExecutionFlags::TRANSPILE_TO_ES_5)
	{

	}

	DefaultEngine::~DefaultEngine()
	{

	}

	ExecutionContext *DefaultEngine::NewContext()
	{
		return spnew DefaultExecutionContext(m_Flags);
	}

} }
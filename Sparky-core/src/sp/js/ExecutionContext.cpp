#include <sp/sp.h>
#include "ExecutionContext.h"

namespace sp { namespace js {
	
	ExecutionContext::ExecutionContext(uint flags)
		: m_Flags(flags)
	{
		
	}

	ExecutionContext::~ExecutionContext()
	{

	}

} }

#pragma once
#include <sp/sp.h>
#include "ExecutionEngine.h"
#include "DefaultExecutionContext.h"

namespace sp { namespace js {

	class DefaultEngine : public ExecutionEngine
	{

	public:
		DefaultEngine();
		~DefaultEngine();

	protected:
		ExecutionContext *NewContext() override;

	};

} }

#pragma once
#include "sp/sp.h"
#include "ExecutionContext.h"

namespace sp { namespace js {

	class ExecutionEngine
	{
		std::vector<ExecutionContext*> m_Contexts;
	protected:
		uint m_Flags;

	public:
		ExecutionEngine(uint flags);
		virtual ~ExecutionEngine();

		ExecutionContext *CreateNewContext();

		static ExecutionEngine *Get();

	protected:
		virtual ExecutionContext *NewContext() = 0;
	};

} }

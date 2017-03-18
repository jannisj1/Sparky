#include <sp/sp.h>
#include <sp/system/Memory.h>
#include <sp/system/VFS.h>
#include <sp/utils/Log.h>

#include "ExecutionEngine.h"
#include "DefaultEngine.h"

namespace sp { namespace js {

	static ExecutionEngine *instance = nullptr;

	ExecutionEngine::ExecutionEngine(uint flags)
		: m_Flags(flags)
	{

	}

	ExecutionEngine::~ExecutionEngine()
	{
		for (ExecutionContext *c : m_Contexts)
			spdel c;
	}

	ExecutionContext *ExecutionEngine::CreateNewContext()
	{
		ExecutionContext *context = NewContext();
		m_Contexts.push_back(context);

		if (context->m_Flags & ExecutionFlags::TRANSPILE_TO_ES_5)
		{
			context->EvaluateNoTransform(VFS::Get()->ReadTextFile("/ui/babel.min.js"));
		}

		return context;
	}

	ExecutionEngine *ExecutionEngine::Get()
	{
		if (!instance)
		{
			instance = spnew DefaultEngine;
		}

		return instance;
	}

} }
#pragma once

#undef DEBUG
#include <jsapi.h>
#include <js/Initialization.h>
#define DEBUG

#include <sp/String.h>
#include <sp/system/Memory.h>

namespace sp { namespace spjs {

	class ExecutionEngine;

	class Script
	{
		JS::RootedScript *m_RS = nullptr;
		JS::MutableHandleScript *m_MHS = nullptr;

		friend class ExecutionEngine;
	public:
		Script();
		~Script();
	};

} }
#pragma once
#include "Script.h"
#include <sp/String.h>
#include <sp/utils/Log.h>

namespace sp { namespace js {

	class ExecutionEngine
	{
		JSContext *m_Context;
		JS::RootedObject *m_Global;
		JS::RootedValue *m_Retval;

	public:
		ExecutionEngine();
		~ExecutionEngine();

		JS::RootedValue *EvalScript(const String& script);
		void RunScript(const Script *script);
		Script *CompileScript(const String& script);

	private:
		void HandleLastError();
	};

} }
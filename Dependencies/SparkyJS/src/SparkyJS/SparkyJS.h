#pragma once
#include "Script.h"
#include <sp/String.h>
#include <sp/utils/Log.h>
#include <condition_variable>
#include <mutex>

namespace sp { namespace spjs {

	class ExecutionEngine
	{
		enum Cmdtype {
			WAIT,
			EXIT,
			EVAL
		};

		JSContext *m_Context;
		JS::RootedObject *m_Global;
		JS::RootedValue *m_Retval;
		JSAutoCompartment *m_AC;

		std::vector<Script*> m_Scripts;

		String m_CurrentFilename;
		String m_CurrentCode;
		Script m_CurrentSript;

		Cmdtype m_CurrentCmd;

		std::mutex m_Mutex;
		std::condition_variable m_JSExeccv;
		bool m_Prepared = false, m_WorkDone = false, m_StartWorking;

	public:
		ExecutionEngine();
		~ExecutionEngine();

		void EvalScript(const String& script, const String& filename = "inline");
	
	private:
		void RunScript(const Script *script);
		Script *CompileScript(const String& script, const String& filename = "inline");

		inline JSContext *GetContext() const { return m_Context; }

	private:
		void StartEngine();
		void HandleLastError();
	};

} }
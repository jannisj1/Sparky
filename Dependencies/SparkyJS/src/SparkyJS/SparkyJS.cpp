#include "SparkyJS.h"
#include "ShellPrincipals.h"
#include "Bindings.h"
#include <sp/utils/Log.h>
#include <thread>
#include <chrono>

namespace sp { namespace spjs {

	// Needed?
	void wr(JSContext* cx, const char* msg, JSErrorReport* er)
	{
		printf("Some Warning\n");
	}

	ExecutionEngine::ExecutionEngine()
	{
		std::thread t1(&ExecutionEngine::StartEngine, this);
		t1.detach();
	}

	ExecutionEngine::~ExecutionEngine()
	{
		for (auto s : m_Scripts) spdel s;

		spdel m_AC;

		spdel m_Retval;
		spdel m_Global;
		JS_DestroyContext(m_Context);
		JS_ShutDown();
	}

	void ExecutionEngine::StartEngine()
	{
		std::unique_lock<std::mutex> lock(m_Mutex);

		JS_Init();
		m_Context = JS_NewContext(8192);
		SP_ASSERT(m_Context);

		JS_SetFutexCanWait(m_Context);
		JS::SetWarningReporter(m_Context, wr);

		JS_SetGCParameter(m_Context, JSGC_MAX_BYTES, 0xffffffff);

		JS_SetTrustedPrincipals(m_Context, &ShellPrincipals::fullyTrusted);
		JS_SetSecurityCallbacks(m_Context, &ShellPrincipals::securityCallbacks);
		JS_InitDestroyPrincipalsCallback(m_Context, ShellPrincipals::destroy);

		if (!JS::InitSelfHostedCode(m_Context))
		{
			JS_DestroyContext(m_Context);
			JS_ShutDown();
			SP_ASSERT(false);
		}

		m_Global = spnew JS::RootedObject(m_Context, JS_NewGlobalObject(m_Context, &global_class, nullptr, JS::FireOnNewGlobalHook, JS::CompartmentOptions()));
		m_Retval = spnew JS::RootedValue(m_Context);

		m_AC = spnew JSAutoCompartment(m_Context, *m_Global);
		JS_InitStandardClasses(m_Context, *m_Global);
		JS_DefineFunctions(m_Context, *m_Global, myjs_global_functions);

		while (true)
		{
			while (!m_StartWorking)
			{
				m_JSExeccv.wait(lock);
			}

			switch (m_CurrentCmd)
			{
			case EXIT:
				//TODO
				break;
			case EVAL:
				JS::CompileOptions opts(m_Context, JSVersion::JSVERSION_LATEST);
				opts.setFileAndLine(m_CurrentFilename.c_str(), 1);

				if (!JS::Evaluate(m_Context, opts, m_CurrentCode.c_str(), m_CurrentCode.length(), m_Retval))
					HandleLastError();
				break;
			}
			
			m_StartWorking = false;
		}
	}

	void ExecutionEngine::EvalScript(const String& script, const String& filename)
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		
		m_CurrentCode = script;
		m_CurrentFilename = filename;
		m_CurrentCmd = EVAL;

		m_StartWorking = true;
		m_JSExeccv.notify_one();
	}
	
	Script *ExecutionEngine::CompileScript(const String& script, const String& filename_)
	{
		SP_ASSERT(false);
		
		Script *ret = spnew Script();

		ret->m_RS = spnew JS::RootedScript(m_Context);
		ret->m_MHS = spnew JS::MutableHandleScript(ret->m_RS);

		const char *filename = filename_.c_str();
		int lineno = 1;
		JS::CompileOptions opts(m_Context, JSVersion::JSVERSION_LATEST);
		opts.setFileAndLine(filename, lineno);
		opts.setColumn(1);

		if (!JS::Compile(m_Context, opts, script.c_str(), script.length(), *ret->m_MHS))
			HandleLastError();

		m_Scripts.push_back(ret);
		
		return ret;
	}

	void ExecutionEngine::RunScript(const Script *script)
	{
		SP_ASSERT(false);
		JS_ExecuteScript(m_Context, *script->m_MHS);
	}

	void ExecutionEngine::HandleLastError()
	{
		JS::RootedValue rval(m_Context);

		JS::RootedValue v(m_Context);
		JS::MutableHandle<JS::Value> mh(&v);
		JS_GetPendingException(m_Context, mh);
		JSObject* obj = &mh.toObject();
		JS::RootedObject ro(m_Context);
		ro.set(obj);
		JS::MutableHandle<JSObject*> mho(&ro);
		JS::Handle<JSObject*> ho(mho);

		JS_DefineProperty(m_Context, *m_Global, "__lastErrorInternal__", ho, 0);
		SP_ERROR("SparkyJS-Error ln. ", JS_GetReservedSlot(obj, 4).toInt32(), ":", JS_GetReservedSlot(obj, 5).toInt32(), " in ", JS_EncodeString(m_Context, JS_GetReservedSlot(obj, 3).toString()));
		auto script = "__internal_log_error__(__lastErrorInternal__.toString());";

		JS::CompileOptions opts(m_Context, JSVersion::JSVERSION_LATEST);
		opts.setFileAndLine("error", 1);
		opts.setColumn(1);

		JS::Evaluate(m_Context, opts, script, strlen(script), &rval);
	}

} }
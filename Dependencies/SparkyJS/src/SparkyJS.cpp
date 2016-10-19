#include "SparkyJS.h"

namespace sp { namespace js {
	
	class ShellPrincipals final : public JSPrincipals {
		uint32_t bits;

		static uint32_t getBits(JSPrincipals* p) {
			if (!p)
				return 0xffff;
			return static_cast<ShellPrincipals*>(p)->bits;
		}

	public:
		explicit ShellPrincipals(uint32_t bits, int32_t refcount = 0) : bits(bits) {
			this->refcount = refcount;
		}

		bool write(JSContext* cx, JSStructuredCloneWriter* writer) override {

			return JS_WriteUint32Pair(writer, bits, 0);
		}

		static void destroy(JSPrincipals* principals) {
			MOZ_ASSERT(principals != &fullyTrusted);
			MOZ_ASSERT(principals->refcount == 0);
			js_delete(static_cast<const ShellPrincipals*>(principals));
		}

		static bool subsumes(JSPrincipals* first, JSPrincipals* second) {
			uint32_t firstBits = getBits(first);
			uint32_t secondBits = getBits(second);
			return (firstBits | secondBits) == firstBits;
		}

		static JSSecurityCallbacks securityCallbacks;

		static ShellPrincipals fullyTrusted;
	};

	JSSecurityCallbacks ShellPrincipals::securityCallbacks = {
		nullptr,
		subsumes
	};

	ShellPrincipals ShellPrincipals::fullyTrusted(-1, 1);
	
	// TODO do this properly
	void wr(JSContext* cx, const char* msg, JSErrorReport* er)
	{
		printf("Some Warning\n");
	}

	static JSClass global_class = {
		"global",
		JSCLASS_GLOBAL_FLAGS,
		nullptr,
		JS_GlobalObjectTraceHook
	};

	bool interal_log(JSContext* cx, unsigned int argc, JS::Value* vp)
	{
		JS::CallArgs c = JS::CallArgsFromVp(argc, vp);
		SP_INFO(JS_EncodeString(cx, c[0].toString()));
		return true;
	}

	bool interal_log_warning(JSContext* cx, unsigned int argc, JS::Value* vp)
	{
		JS::CallArgs c = JS::CallArgsFromVp(argc, vp);
		SP_WARN(JS_EncodeString(cx, c[0].toString()));
		return true;
	}

	bool interal_log_error(JSContext* cx, unsigned int argc, JS::Value* vp)
	{
		JS::CallArgs c = JS::CallArgsFromVp(argc, vp);
		SP_ERROR(JS_EncodeString(cx, c[0].toString()));
		return true;
	}

	static JSFunctionSpec myjs_global_functions[] = {
		JS_FS("__internal_log__", interal_log, 1, 0),
		JS_FS("__internal_log_warning__", interal_log_warning, 1, 0),
		JS_FS("__internal_log_error__", interal_log_error, 1, 0),
		JS_FS_END
	};

	ExecutionEngine::ExecutionEngine()
	{
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

		JS_InitStandardClasses(m_Context, *m_Global);
		JS_DefineFunctions(m_Context, *m_Global, myjs_global_functions);
	}

	ExecutionEngine::~ExecutionEngine()
	{
		spdel m_Retval;
		spdel m_Global;
		JS_DestroyContext(m_Context);
		JS_ShutDown();
	}

	JS::RootedValue *ExecutionEngine::EvalScript(const String& script)
	{
		const char *filename = "";
		int lineno = 1;
		JS::CompileOptions opts(m_Context, JSVersion::JSVERSION_LATEST);
		opts.setFileAndLine(filename, lineno);

		bool ok = JS::Evaluate(m_Context, opts, script.c_str(), script.length(), m_Retval);
		if (!ok) HandleLastError();

		return m_Retval;
	}

	

	void ExecutionEngine::RunScript(const Script *script)
	{

	}

	Script *ExecutionEngine::CompileScript(const String& script)
	{
		return nullptr;
	}

	void ExecutionEngine::HandleLastError()
	{
		JS::RootedValue v(m_Context);
		JS::MutableHandle<JS::Value> mh(&v);
		JS_GetPendingException(m_Context, mh);
		JSObject* obj = &mh.toObject();
		JS::RootedObject ro(m_Context);
		ro.set(obj);
		JS::MutableHandle<JSObject*> mho(&ro);
		JS::Handle<JSObject*> ho(mho);

		JS_DefineProperty(m_Context, *m_Global, "__lastErrorInternal__", ho, 0);
		//std::cout << "Line " << JS_GetReservedSlot(obj, 4).toInt32() << ": ";
		EvalScript("__internal_log_error__(__lastErrorInternal__.toString());");
	}

} }
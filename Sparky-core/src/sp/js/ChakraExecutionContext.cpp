#include "sp/sp.h"
#include "sp/utils/Log.h"
#include "sp/system/MemoryManager.h"
#include "sp/app/Application.h"

#include "ChakraExecutionContext.h"

namespace sp { namespace js {

	static JsValueRef CALLBACK chakra_spjs_info(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
	{
		const wchar_t *msg;
		size_t msgLen;

		JsStringToPointer(arguments[1], &msg, &msgLen);
		
		SP_INFO(msg);

		return JS_INVALID_REFERENCE;
	}

	static JsValueRef CALLBACK chakra_spjs_warn(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
	{
		const wchar_t *msg;
		size_t msgLen;

		JsStringToPointer(arguments[1], &msg, &msgLen);

		SP_WARN(msg);

		return JS_INVALID_REFERENCE;
	}

	static JsValueRef CALLBACK chakra_spjs_error(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
	{
		const wchar_t *msg;
		size_t msgLen;

		JsStringToPointer(arguments[1], &msg, &msgLen);

		SP_ERROR(msg);

		return JS_INVALID_REFERENCE;
	}

	static JsValueRef CALLBACK chakra_spjs_assert(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
	{
		const wchar_t *msg;
		size_t msgLen;

		bool condition;
		JsBooleanToBool(arguments[1], &condition);
		JsStringToPointer(arguments[2], &msg, &msgLen);

		SP_ASSERT(condition, msg);

		return JS_INVALID_REFERENCE;
	}

	static JsValueRef CALLBACK chakra_spjs_get_fps(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
	{
		JsValueRef returnValue;
		JsDoubleToNumber((double)Application::GetApplication().GetFPS(), &returnValue);
		return returnValue;
	}

	static JsValueRef CALLBACK chakra_spjs_get_ups(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
	{
		JsValueRef returnValue;
		JsDoubleToNumber((double)Application::GetApplication().GetUPS(), &returnValue);
		return returnValue;
	}

	static JsValueRef CALLBACK chakra_spjs_get_frametime(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
	{
		JsValueRef returnValue;
		JsDoubleToNumber((double)Application::GetApplication().GetFrametime(), &returnValue);
		return returnValue;
	}

	static JsValueRef CALLBACK chakra_spjs_get_total_allocated(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
	{
		JsValueRef returnValue;
		JsDoubleToNumber((double)sp::internal::MemoryManager().Get()->GetMemoryStats().totalAllocated, &returnValue);
		return returnValue;
	}

	static JsValueRef CALLBACK chakra_spjs_get_total_freed(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
	{
		JsValueRef returnValue;
		JsDoubleToNumber((double)sp::internal::MemoryManager().Get()->GetMemoryStats().totalFreed, &returnValue);
		return returnValue;
	}

	static JsValueRef CALLBACK chakra_spjs_get_current_used(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
	{
		JsValueRef returnValue;
		JsDoubleToNumber((double)sp::internal::MemoryManager().Get()->GetMemoryStats().currentUsed, &returnValue);
		return returnValue;
	}

	static JsValueRef CALLBACK chakra_spjs_get_total_allocations(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
	{
		JsValueRef returnValue;
		JsDoubleToNumber((double)sp::internal::MemoryManager().Get()->GetMemoryStats().totalAllocations, &returnValue);
		return returnValue;
	}

	static JsValueRef CALLBACK chakra_spjs_exit(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState)
	{
		Application::GetApplication().Stop();
		return JS_INVALID_REFERENCE;
	}

	ChakraExecutionContext::ChakraExecutionContext(uint flags, JsRuntimeHandle runtime)
		: ExecutionContext(flags)
	{
		JsCreateContext(runtime, &m_Context);
		JsSetCurrentContext(m_Context);
		
		JsValueRef global;
		JsGetGlobalObject(&global);

		SetCallback(global, L"__spjs_log_info", chakra_spjs_info, nullptr);
		SetCallback(global, L"__spjs_log_warn", chakra_spjs_warn, nullptr);
		SetCallback(global, L"__spjs_log_error", chakra_spjs_error, nullptr);
		SetCallback(global, L"__spjs_log_assert", chakra_spjs_assert, nullptr);

		SetCallback(global, L"__spjs_get_fps", chakra_spjs_get_fps, nullptr);
		SetCallback(global, L"__spjs_get_ups", chakra_spjs_get_ups, nullptr);
		SetCallback(global, L"__spjs_get_frametime", chakra_spjs_get_frametime, nullptr);
		SetCallback(global, L"__spjs_get_total_allocated", chakra_spjs_get_total_allocated, nullptr);
		SetCallback(global, L"__spjs_get_total_freed", chakra_spjs_get_total_freed, nullptr);
		SetCallback(global, L"__spjs_get_current_used", chakra_spjs_get_current_used, nullptr);
		SetCallback(global, L"__spjs_get_total_allocations", chakra_spjs_get_total_allocations, nullptr);

		SetCallback(global, L"__spjs_exit", chakra_spjs_exit, nullptr);
	}

	ChakraExecutionContext::~ChakraExecutionContext()
	{
		JsSetCurrentContext(JS_INVALID_REFERENCE);
	}

	void ChakraExecutionContext::SetCallback(JsValueRef object, const wchar_t *propertyName, JsNativeFunction callback, void *callbackState)
	{
		JsPropertyIdRef propertyId;
		JsGetPropertyIdFromName(propertyName, &propertyId);
		JsValueRef function;
		JsCreateFunction(callback, callbackState, &function);
		JsSetProperty(object, propertyId, function, true);
	}

	void ChakraExecutionContext::EvaluateNoTransform(const String& src, const String& filename)
	{
		JsValueRef returnValue;

		JsSetCurrentContext(m_Context);
		if (JsRunScript(std::wstring(src.begin(), src.end()).c_str(), m_CurrentSourceContext++, std::wstring(filename.begin(), filename.end()).c_str(), &returnValue) != JsNoError)
		{
			JsValueRef exception;
			JsGetAndClearException(&exception);

			JsPropertyIdRef messageName;
			JsValueRef messageValue;

			const wchar_t *message;
			size_t length;

			JsGetPropertyIdFromName(L"message", &messageName);
			JsGetProperty(exception, messageName, &messageValue);
			JsStringToPointer(messageValue, &message, &length);

			SP_ERROR("sp-js error: ", message);
		}
	}

	void ChakraExecutionContext::Evaluate(const String& src, const String& filename)
	{
		JsValueRef returnValue;

		JsSetCurrentContext(m_Context);
		if (JsRunScript(std::wstring(src.begin(), src.end()).c_str(), m_CurrentSourceContext++, std::wstring(filename.begin(), filename.end()).c_str(), &returnValue) != JsNoError)
		{
			JsValueRef exception;
			JsGetAndClearException(&exception);

			JsPropertyIdRef messageName;
			JsValueRef messageValue;

			const wchar_t *message;
			size_t length;

			JsGetPropertyIdFromName(L"message", &messageName);
			JsGetProperty(exception, messageName, &messageValue);
			JsStringToPointer(messageValue, &message, &length);

			SP_ERROR("sp-js error: ", message);
		}
	}

	String ChakraExecutionContext::EvaluateString(const String& src, const String& filename)
	{
		JsValueRef returnValue;

		JsSetCurrentContext(m_Context);
		if (JsRunScript(std::wstring(src.begin(), src.end()).c_str(), m_CurrentSourceContext++, std::wstring(filename.begin(), filename.end()).c_str(), &returnValue) != JsNoError)
		{
			JsValueRef exception;
			JsGetAndClearException(&exception);

			JsPropertyIdRef messageName;
			JsValueRef messageValue;

			const wchar_t *message;
			size_t length;

			JsGetPropertyIdFromName(L"message", &messageName);
			JsGetProperty(exception, messageName, &messageValue);
			JsStringToPointer(messageValue, &message, &length);

			SP_ERROR("sp-js error: ", message);
			
			std::wstring strMesssage(message);
			return std::string(strMesssage.begin(), strMesssage.end());
		}
		
		JsValueRef str;
		JsConvertValueToString(returnValue, &str);
		
		const wchar_t *strPtr;
		size_t stringLength;
		JsStringToPointer(str, &strPtr, &stringLength);

		std::wstring res(strPtr);
		return std::string(res.begin(), res.end());
	}

	int32 ChakraExecutionContext::EvaluateInt32(const String& src, const String& filename)
	{
		JsValueRef returnValue;

		JsSetCurrentContext(m_Context);
		if (JsRunScript(std::wstring(src.begin(), src.end()).c_str(), m_CurrentSourceContext++, std::wstring(filename.begin(), filename.end()).c_str(), &returnValue) != JsNoError)
		{
			// Get error message
			JsValueRef exception;
			JsGetAndClearException(&exception);

			JsPropertyIdRef messageName;
			JsValueRef messageValue;

			const wchar_t *message;
			size_t length;

			JsGetPropertyIdFromName(L"message", &messageName);
			JsGetProperty(exception, messageName, &messageValue);
			JsStringToPointer(messageValue, &message, &length);

			SP_ERROR("sp-js error: ", message);
			return 0;
		}

		JsValueRef number;
		JsConvertValueToNumber(returnValue, &number);
		
		double res;
		JsNumberToDouble(number, &res);

		return (int32)res;
	}

	double ChakraExecutionContext::EvaluateDouble(const String& src, const String& filename)
	{
		JsValueRef returnValue;

		JsSetCurrentContext(m_Context);
		if(JsRunScript(std::wstring(src.begin(), src.end()).c_str(), m_CurrentSourceContext++, std::wstring(filename.begin(), filename.end()).c_str(), &returnValue) != JsNoError)
		{
			// Get error message
			JsValueRef exception;
			JsGetAndClearException(&exception);

			JsPropertyIdRef messageName;
			JsValueRef messageValue;

			const wchar_t *message;
			size_t length;

			JsGetPropertyIdFromName(L"message", &messageName);
			JsGetProperty(exception, messageName, &messageValue);
			JsStringToPointer(messageValue, &message, &length);

			SP_ERROR("sp-js error: ", message);
			return 0.0;
		}

		JsValueRef number;
		JsConvertValueToNumber(returnValue, &number);

		double res;
		JsNumberToDouble(number, &res);

		return res;
	}

} }

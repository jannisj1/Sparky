#include <sp/sp.h>
#include <sp/utils/Log.h>
#include "ChakraExecutionContext.h"

namespace sp { namespace js {

	ChakraExecutionContext::ChakraExecutionContext(uint flags, JsRuntimeHandle runtime)
		: ExecutionContext(flags)
	{
		JsCreateContext(runtime, &m_Context);
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

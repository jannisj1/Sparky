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
		JS::RootedValue *m_Retval, *m_Retval2;
		JSAutoCompartment *m_AC;

		std::vector<Script*> m_Scripts;

		String m_CurrentFilename;
		String m_CurrentCode;
		Script m_CurrentSript;

		Cmdtype m_CurrentCmd;

		std::mutex m_Mutex, m_Mutex2;
		std::condition_variable m_JSExeccv;
		bool m_WorkDone = false, m_StartWorking;

		int m_ID;

		enum class ExposedValueType {
			DOUBLE,
			FLOAT,
			INT32,
			STRING
		};

		std::vector<std::pair<std::pair<ExposedValueType, bool>, void*>> m_ExposedValues;

	public:
		ExecutionEngine();
		~ExecutionEngine();

		JS::RootedValue *EvalScript(const String& script, const String& filename = "inline");
		
		String EvalString(const String& s);
		String ToString(JS::RootedValue *v);

		template<class T>
		void Expose(const String& name, T& val)
		{
			std::lock_guard<std::mutex> lock(m_Mutex2);
			String code = "var " + name + "= new __internal_class_expose_wrapper__(" + std::to_string(m_ID) + "," + std::to_string(m_ExposedValues.size()) + ", false);";
			EvalScript(code);
			m_ExposedValues.push_back(std::make_pair(std::make_pair(ToValueType<T>(), false), &val));
		}

		template<class T>
		void Expose(const String& name, const T& val)
		{
			std::lock_guard<std::mutex> lock(m_Mutex2);
			String code = "var " + name + "= new __internal_class_expose_wrapper__(" + std::to_string(m_ID) + "," + std::to_string(m_ExposedValues.size()) + ", true);";
			EvalScript(code);
			m_ExposedValues.push_back(std::make_pair(std::make_pair(ToValueType<T>(), true), (void*)spnew T(val)));
		}

	private:
		void RunScript(const Script *script);
		Script *CompileScript(const String& script, const String& filename = "inline");

		inline JSContext *GetContext() const { return m_Context; }

	private:
		void StartEngine();
		void HandleLastError();

		friend bool SetValue(JSContext* cx, unsigned int argc, JS::Value* vp);
		friend bool GetValue(JSContext* cx, unsigned int argc, JS::Value* vp);

		template<class T>
		inline ExposedValueType ToValueType()
		{
			SP_ASSERT(false, "Can't expose value of type " + typeid(T).name());
		}

		template<>
		inline ExposedValueType ToValueType<double>()
		{
			return ExposedValueType::DOUBLE;
		}

		template<>
		inline ExposedValueType ToValueType<float>()
		{
			return ExposedValueType::FLOAT;
		}

		template<>
		inline ExposedValueType ToValueType<int32>()
		{
			return ExposedValueType::INT32;
		}

		template<>
		inline ExposedValueType ToValueType<String>()
		{
			return ExposedValueType::STRING;
		}
	};

} }
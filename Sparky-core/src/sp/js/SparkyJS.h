#pragma once
#include "Script.h"
#include <sp/String.h>
#include <sp/utils/Log.h>
#include <condition_variable>
#include <mutex>
#include <SparkyCSS/SparkyCSS.h>

namespace sp { namespace graphics { namespace ui { class Widget; } } }

namespace sp { namespace spjs {

	class DomElement 
	{
	protected:
		css::UIElementCSSInfo m_CSSInfo;
		std::vector<DomElement*> m_DomChildren;

	public:
		DomElement();
		~DomElement();
	protected:
		virtual void SetCSSProperties(const String& css) = 0;
		void ExposeToJS();

	private:
		friend bool SetStyle(JSContext* cx, unsigned int argc, JS::Value* vp);
	};

	class SP_API ExecutionEngine
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
			STRING,
			VEC2,
			VEC3
		};

		std::vector<std::pair<std::pair<ExposedValueType, bool>, void*>> m_ExposedValues;
		sp::graphics::ui::Widget *m_DomRoot;

	public:
		ExecutionEngine();
		~ExecutionEngine();

		JS::RootedValue *EvalScript(const String& script, const String& filename = "inline");
		
		String EvalString(const String& s);
		String ToString(JS::RootedValue *v);
		template<class T>
		void EvalSetterExpression(const String& setterExpression, T val)
		{
			std::stringstream varName;
			bool expStarted = false;
			for (char c : setterExpression)
			{
				if (c == '$') expStarted = true;
				else if (expStarted)
				{
					varName << c;
				}
			}
			
			JS_DefineProperty(m_Context, *m_Global, "__internal_set_value_val__", val, 0);
			EvalScript("__internal_set_value__('" + varName.str() + "', __internal_set_value_val__);");
		}

		template<class T>
		JS::Value ToJSValue(T val)
		{
			SP_ASSERT(false);
		}

		template<>
		JS::Value ToJSValue<double>(double val)
		{
			return JS::DoubleValue(val);
		}

		template<>
		JS::Value ToJSValue<float>(float val)
		{
			return JS::Float32Value(val);
		}

		template<>
		JS::Value ToJSValue<int32>(int32 val)
		{
			return JS::Int32Value(val);
		}

		template<>
		JS::Value ToJSValue<String>(String val)
		{
			return JS::StringValue(JS_NewStringCopyN(m_Context, val.c_str(), val.length()));
		}

		template<class T>
		void Expose(const String& name, T& val)
		{
			std::lock_guard<std::mutex> lock(m_Mutex2);
			ExposedValueType vt = ToValueType<T>();

			// 0: number, 1: string, 2: vec2, 3: vec3
			int internalValueType;
			switch (vt)
			{
			case ExposedValueType::FLOAT:
			case ExposedValueType::DOUBLE:
			case ExposedValueType::INT32:
				internalValueType = 0;
				break;
			case ExposedValueType::STRING:
				internalValueType = 1;
				break;
			case ExposedValueType::VEC2:
				internalValueType = 2;
				break;
			case ExposedValueType::VEC3:
				internalValueType = 3;
				break;
			default:
				SP_ASSERT(false);
			}

			String code = "var " + name + "= new __internal_class_expose_wrapper__(" + std::to_string(m_ID) + "," + std::to_string(m_ExposedValues.size()) + ", false, " + std::to_string(internalValueType) + ");";
			EvalScript(code);
			m_ExposedValues.push_back(std::make_pair(std::make_pair(vt, false), &val));
		}

		template<class T>
		void Expose(const String& name, const T& val)
		{
			std::lock_guard<std::mutex> lock(m_Mutex2);
			ExposedValueType vt = ToValueType<T>();

			// 0: number, 1: string, 2: vec2, 3: vec3
			int internalValueType;
			switch (vt)
			{
			case ExposedValueType::FLOAT:
			case ExposedValueType::DOUBLE:
			case ExposedValueType::INT32:
				internalValueType = 0;
				break;
			case ExposedValueType::STRING:
				internalValueType = 1;
				break;
			case ExposedValueType::VEC2:
				internalValueType = 2;
				break;
			case ExposedValueType::VEC3:
				internalValueType = 3;
				break;
			default:
				SP_ASSERT(false);
			}

			String code = "var " + name + "= new __internal_class_expose_wrapper__(" + std::to_string(m_ID) + "," + std::to_string(m_ExposedValues.size()) + ", true, " + std::to_string(internalValueType) + ");";
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

		template<>
		inline ExposedValueType ToValueType<maths::vec2>()
		{
			return ExposedValueType::VEC2;
		}

		template<>
		inline ExposedValueType ToValueType<maths::vec3>()
		{
			return ExposedValueType::VEC3;
		}
	};

} }
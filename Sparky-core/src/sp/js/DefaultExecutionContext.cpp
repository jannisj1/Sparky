#include <sp/sp.h>
#include <sp/utils/Log.h>
#include <sp/system/VFS.h>
#include "DefaultExecutionContext.h"

namespace sp { namespace js {

	DefaultExecutionContext::DefaultExecutionContext(uint flags)
		: ExecutionContext(flags)
	{
		m_Ctx = duk_create_heap_default();

		const char *transformCode =
			R"delimiter(

function __spjs_transform_babel(code) {
	try {
		return Babel.transform(code, { presets: ['es2015', 'react', 'stage-0'] }).code;
	} catch (ex) {
		//log.error(ex.message);
		return "babel error";
	}
};

)delimiter";

		if (duk_peval_string(m_Ctx, transformCode) != 0)
		{
			SP_ERROR(duk_safe_to_string(m_Ctx, -1));
		}

		duk_pop(m_Ctx);
	}

	DefaultExecutionContext::~DefaultExecutionContext()
	{

	}

	void DefaultExecutionContext::Evaluate(const String& src, const String& filename)
	{
		if (duk_peval_string(m_Ctx, BabelTransform(src).c_str()) != 0) {
			SP_ERROR("sp-js error (", filename, "): ", duk_safe_to_string(m_Ctx, -1));
		}

		duk_pop(m_Ctx);
	}

	String DefaultExecutionContext::EvaluateString(const String& src, const String& filename /*= "inline"*/)
	{
		if (duk_peval_string(m_Ctx, BabelTransform(src).c_str()) != 0) {
			SP_ERROR("sp-js error (", filename, "): ", duk_safe_to_string(m_Ctx, -1));
		}

		String res(duk_to_string(m_Ctx, -1));

		duk_pop(m_Ctx);

		return res;
	}

	int32 DefaultExecutionContext::EvaluateInt32(const String& src, const String& filename /*= "inline"*/)
	{
		if (duk_peval_string(m_Ctx, BabelTransform(src).c_str()) != 0) {
			SP_ERROR("sp-js error (", filename, "): ", duk_safe_to_string(m_Ctx, -1));
		}

		int32 res = duk_to_int32(m_Ctx, -1);

		duk_pop(m_Ctx);

		return res;
	}

	double DefaultExecutionContext::EvaluateDouble(const String& src, const String& filename /*= "inline"*/)
	{
		if (duk_peval_string(m_Ctx, BabelTransform(src).c_str()) != 0) {
			SP_ERROR("sp-js error (", filename, "): ", duk_safe_to_string(m_Ctx, -1));
		}

		double res = duk_to_number(m_Ctx, -1);

		duk_pop(m_Ctx);

		return res;
	}

	void DefaultExecutionContext::EvaluateNoTransform(const String& src, const String& filename /*= "inline"*/)
	{
		duk_push_string(m_Ctx, src.c_str());
		if (duk_peval(m_Ctx) != 0) {
			SP_ERROR("sp-js error (", filename, "): ", duk_safe_to_string(m_Ctx, -1));
		}

		duk_pop(m_Ctx);
	}

	String DefaultExecutionContext::BabelTransform(const String& src)
	{
		duk_eval_string(m_Ctx, "__spjs_transform_babel");
		duk_push_string(m_Ctx, src.c_str());
		duk_call(m_Ctx, 1);
		
		String res;
		
		const char* strData = duk_safe_to_string(m_Ctx, -1);
		if (strData)
			res = strData;

		duk_pop(m_Ctx);

		return res;
	}

} }

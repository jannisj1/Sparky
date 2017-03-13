#include <sp/sp.h>
#include <sp/utils/Log.h>
#include "DefaultExecutionContext.h"

namespace sp { namespace js {

	DefaultExecutionContext::DefaultExecutionContext(uint flags)
		: ExecutionContext(flags)
	{
		m_Ctx = duk_create_heap_default();
	}

	DefaultExecutionContext::~DefaultExecutionContext()
	{

	}

	void DefaultExecutionContext::Evaluate(const String& src, const String& filename)
	{
		duk_push_string(m_Ctx, src.c_str());
		if (duk_peval(m_Ctx) != 0) {
			SP_ERROR("sp-js error (", filename, "): ", duk_safe_to_string(m_Ctx, -1));
		}

		duk_pop(m_Ctx);
	}

} }

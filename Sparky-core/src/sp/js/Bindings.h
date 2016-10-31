#pragma once
#include <sp/app/Application.h>
#include <sp/system/MemoryManager.h>

namespace sp { namespace spjs {

	static JSClass global_class = {
		"global",
		JSCLASS_GLOBAL_FLAGS,
		nullptr,
		JS_GlobalObjectTraceHook
	};

	bool internal_log(JSContext* cx, unsigned int argc, JS::Value* vp)
	{
		JS::CallArgs c = JS::CallArgsFromVp(argc, vp);
		SP_INFO(JS_EncodeString(cx, c[0].toString()));
		return true;
	}

	bool internal_log_warning(JSContext* cx, unsigned int argc, JS::Value* vp)
	{
		JS::CallArgs c = JS::CallArgsFromVp(argc, vp);
		SP_WARN(JS_EncodeString(cx, c[0].toString()));
		return true;
	}

	bool internal_log_error(JSContext* cx, unsigned int argc, JS::Value* vp)
	{
		JS::CallArgs c = JS::CallArgsFromVp(argc, vp);
		SP_ERROR(JS_EncodeString(cx, c[0].toString()));
		return true;
	}

	bool internal_get_fps(JSContext* cx, unsigned int argc, JS::Value* vp)
	{
		*vp = JS::Int32Value(Application::GetApplication().GetFPS());
		return true;
	}

	bool internal_get_ups(JSContext* cx, unsigned int argc, JS::Value* vp)
	{
		*vp = JS::Int32Value(Application::GetApplication().GetUPS());
		return true;
	}

	bool internal_get_frametime(JSContext* cx, unsigned int argc, JS::Value* vp)
	{
		*vp = JS::Float32Value(Application::GetApplication().GetFrametime());
		return true;
	}

	bool internal_get_totalAllocated(JSContext* cx, unsigned int argc, JS::Value* vp)
	{
		*vp = JS::DoubleValue(sp::internal::MemoryManager().Get()->GetMemoryStats().totalAllocated);
		return true;
	}

	bool internal_get_totalFreed(JSContext* cx, unsigned int argc, JS::Value* vp)
	{
		*vp = JS::DoubleValue(sp::internal::MemoryManager().Get()->GetMemoryStats().totalFreed);
		return true;
	}

	bool internal_get_currentUsed(JSContext* cx, unsigned int argc, JS::Value* vp)
	{
		*vp = JS::DoubleValue(sp::internal::MemoryManager().Get()->GetMemoryStats().currentUsed);
		return true;
	}

	bool internal_get_totalAllocations(JSContext* cx, unsigned int argc, JS::Value* vp)
	{
		*vp = JS::DoubleValue(sp::internal::MemoryManager().Get()->GetMemoryStats().totalAllocations);
		return true;
	}

	bool internal_exit(JSContext* cx, unsigned int argc, JS::Value* vp)
	{
		Application::GetApplication().Stop();
		return true;
	}

	static JSFunctionSpec myjs_global_functions[] = {
		JS_FS("__internal_exit__", internal_exit, 0, 0),
		JS_FS("__internal_log__", internal_log, 1, 0),
		JS_FS("__internal_log_warning__", internal_log_warning, 1, 0),
		JS_FS("__internal_log_error__", internal_log_error, 1, 0),
		JS_FS("__internal_get_fps__", internal_get_fps, 0, 0),
		JS_FS("__internal_get_ups__", internal_get_ups, 0, 0),
		JS_FS("__internal_get_frametime__", internal_get_frametime, 0, 0),
		JS_FS("__internal_get_totalAllocated__", internal_get_totalAllocated, 0, 0),
		JS_FS("__internal_get_totalFreed__", internal_get_totalFreed, 0, 0),
		JS_FS("__internal_get_currentUsed__", internal_get_currentUsed, 0, 0),
		JS_FS("__internal_get_totalAllocations__", internal_get_totalAllocations, 0, 0),
		JS_FS_END
	};

} }
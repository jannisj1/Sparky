#pragma once
#include <sp/app/Application.h>
#include <sp/system/MemoryManager.h>

namespace sp { namespace js {

	void spjs_info(const String& info);
	void spjs_warn(const String& info);
	void spjs_error(const String& info);
	void spjs_assert(bool condition, const String& info);
	uint spjs_get_fps();
	uint spjs_get_ups();
	float spjs_get_frametime();
	int64 spjs_get_total_allocated();
	int64 spjs_get_total_freed();
	int64 spjs_get_current_used();
	int64 spjs_get_total_allocations();
	void spjs_exit();

} }

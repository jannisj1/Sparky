#include <sp/sp.h>
#include <sp/app/Application.h>
#include <sp/system/MemoryManager.h>
#include <sp/utils/Log.h>

namespace sp { namespace js {

	void spjs_info(const String& info)
	{
		SP_INFO(info);
	}

	void spjs_warn(const String& info)
	{
		SP_WARN(info);
	}

	void spjs_error(const String& info)
	{
		SP_ERROR(info);
	}

	void spjs_assert(bool condition, const String& info)
	{
		SP_ASSERT(condition, info);
	}

	uint spjs_get_fps()
	{
		return Application::GetApplication().GetFPS();
	}

	uint spjs_get_ups()
	{
		return Application::GetApplication().GetUPS();
	}

	float spjs_get_frametime()
	{
		return Application::GetApplication().GetFrametime();
	}

	int64 spjs_get_total_allocated()
	{
		return sp::internal::MemoryManager().Get()->GetMemoryStats().totalAllocated;
	}

	int64 spjs_get_total_freed()
	{
		return sp::internal::MemoryManager().Get()->GetMemoryStats().totalFreed;
	}

	int64 spjs_get_current_used()
	{
		return sp::internal::MemoryManager().Get()->GetMemoryStats().currentUsed;
	}

	int64 spjs_get_total_allocations()
	{
		return sp::internal::MemoryManager().Get()->GetMemoryStats().totalAllocations;
	}

	void spjs_exit()
	{
		Application::GetApplication().Stop();
	}

} }

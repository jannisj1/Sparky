#include "sp/sp.h"

namespace sp { namespace js {

	const char *sparky_js_src =
R"sparkyjs_delim(

class log {
    static info(x) {
        __spjs_log_info(x.toString());
    }

    static warn(x) {
        __spjs_log_warning(x.toString());
    }

    static error(x) {
        __spjs_log_error(x.toString());
    }

    static assert(condition, x) {
        __spjs_log_assert(Boolean(condition), x.toString());
    }
}

function __spjs_memory_size_to_string(bytes){
    function round(bytes) {
        return Math.round(bytes * 100) / 100.0;
    }

    const gb = 1024 * 1024 * 1024;
    const mb = 1024 * 1024;
    const kb = 1024;

    if (bytes >= gb)
        return round(bytes / gb) + " GB";
    else if (bytes >= mb)
        return round(bytes / mb) + " MB";
    else if (bytes >= kb)
        return round(bytes / kb) + " KB";
    else
        return bytes + " bytes";
}

class __spjs_class_memory_size {
    constructor(bytes) {
        this.bytes = bytes;
    }

    toString() {
        return __spjs_memory_size_to_string(this.bytes);
    }
}

class __spjs_class_memory {
    constructor() {}

    get totalAllocated() {
        return new __spjs_class_memory_size(__spjs_get_total_allocated());
    }

    get totalFreed() {
        return new __spjs_class_memory_size(__spjs_get_total_freed());
    }

    get currentUsed() {
        return new __spjs_class_memory_size(__spjs_get_current_used());
    }

    get totalAllocations() {
        return __spjs_get_total_allocations();
    }

    toString() {
        return "{ totalAllocated: " + this.totalAllocated +
            ", totalFreed: " + this.totalFreed +
            ", currentUsed: " + this.currentUsed +
            ", totalAllocations: " + this.totalAllocations + " }";
    }
}

class app {
    constructor() {}

    static get fps() {
        return __spjs_get_fps();
    }

    static get ups() {
        return __spjs_get_ups();
    }

    static get frameTime() {
        return __spjs_get_frametime();
    }

    static get memory() {
        return new __spjs_class_memory();
    }

    static exit() {
        __spjs_exit();
    }
}


)sparkyjs_delim";

	}
}

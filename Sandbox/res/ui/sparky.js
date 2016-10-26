function __internal_toString__(obj) {
    return obj.toString();
}

class log {
    static info(x) {
        __internal_log__(x.toString());
    }

    static warn(x) {
        __internal_log_warning__(x.toString());
    }

    static error(x){
        __internal_log_error__(x.toString());
    }
}

function __internal_memory_size_to_string__(val){
    function round(val) {
        return Math.round(val * 100) / 100.0;
    }

    const gb = 1024 * 1024 * 1024;
    const mb = 1024 * 1024;
    const kb = 1024;

    if (val >= gb)
        return round(val / gb) + " GB";
    else if (val >= mb)
        return round(val / mb) + " MB";
    else if (val >= kb)
        return round(val / kb) + " KB";
    else
        return val + " bytes";
}

class __internal_class_memory_size__ {
    constructor(val) {
        this.value = val;
    }

    toString() {
        return __internal_memory_size_to_string__(this.value);
    }
}

class __internal_class_memory__ {
    constructor() { }

    get totalAllocated() {
        return new __internal_class_memory_size__(__internal_get_totalAllocated__());
    }

    get totalFreed() {
        return new __internal_class_memory_size__(__internal_get_totalFreed__());
    }

    get currentUsed() {
        return new __internal_class_memory_size__(__internal_get_currentUsed__());
    }

    get totalAllocations() {
        return __internal_get_totalAllocations__();
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
        return __internal_get_fps__();
    }

    static get frameTime() {
        return __internal_get_frametime__();
    }

    static get memory() {
        return new __internal_class_memory__();
    }

    
}

class __internal_class_expose_wrapper__ {
    constructor(eeID, valueID, const_) { 
        this.eeID = eeID | 0; 
        this.valueID = valueID | 0;
        this.isConst = const_;
    }

    get() {
        return __internal_get_exposed_value__(this.eeID, this.valueID);
    }

    set(val) {
        if (!this.isConst)
            __internal_set_exposed_value__(this.eeID, this.valueID, val);
        else
            log.error("Can't set a const value!"); //TODO: Throw exception
    }

    toString() {
        return this.get().toString();
    }
}
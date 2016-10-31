function __internal_toString__(obj) {
    return obj.toString();
}

function makeVec3(x_, y_, z_) {
    return { x: x_, y: y_, z: z_ };
}

function makeVec2(x_, y_) {
    return { x: x_, y: y_ };
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

    static get ups() {
        return __internal_get_ups__();
    }

    static get frameTime() {
        return __internal_get_frametime__();
    }

    static get memory() {
        return new __internal_class_memory__();
    }

    static exit() {
        __internal_exit__();
    }
}

var __internal__enum_exposed_type__ = {
    NUMBER: 0,
    STRING: 1,
    VEC2: 2,
    VEC3: 3
};

class __internal_class_expose_wrapper__ {
    constructor(eeID, valueID, const_, type) { 
        this.__internal_eeID__ = eeID|0;
        this.__internal_valueID__ = valueID|0;
        this.__internal_isConst__ = const_;
        this.__internal_type__ = type;
    }

    get() {
        return __internal_get_exposed_value__(this.__internal_eeID__, this.__internal_valueID__);
    }

    set(val) {
        if (!this.isConst) {
            switch(this.__internal_type__) {
                case __internal__enum_exposed_type__.NUMBER:
                    val = Number(val);
                    break;
                case __internal__enum_exposed_type__.STRING:
                    val = val.toString();
                    break;
                case __internal__enum_exposed_type__.VEC2:
                    __internal_set_exposed_value__(this.__internal_eeID__, this.__internal_valueID__, Number(val.x), Number(val.y));
                    return;
                case __internal__enum_exposed_type__.VEC3:
                    __internal_set_exposed_value__(this.__internal_eeID__, this.__internal_valueID__, Number(val.x), Number(val.y), Number(val.z));
                    return;
                default:
                    log.error("Internal JS-Error: Unkown Type...");
            }

            __internal_set_exposed_value__(this.__internal_eeID__, this.__internal_valueID__, val);
        }
        else
            log.error("Can't set a const value!"); //TODO: Throw exception
    }

    toString() {
        return this.get().toString();
    }
}

function __internal_set_value__(property, value) {
    global[property].set(value);
}


function $(id) {
    return new __internal_class_domElement_class__(__internal_get_internal_element_id_by_id__(id));
}

class __internal_style_class__ {
    constructor(id) {
        this.__internal_ID__ = id|0;
    }

    set width(value) {
        __internal_set_style__(this.__internal_ID__, "width:" + value);
        setInterval(function(){ log.error("moin"); }, 20);
    }

}

class __internal_class_domElement_class__ {
    constructor(id) {
        this.__internal_ID__ = id|0;
    }
    
    get style() {
        return new __internal_style_class__(this.__internal_ID__);
    }
}


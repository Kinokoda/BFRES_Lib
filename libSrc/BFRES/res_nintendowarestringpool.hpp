#pragma once

namespace vp::res {
    
    struct ResNintendoWareStringPool {
        u32   magic;
        u32   reserve0;
        void *reserve1;
        u32   string_count;
        u32   empty_string;
    };
}
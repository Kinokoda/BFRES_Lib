#pragma once

#include <cstdint>

namespace vp::res {
    
    struct ResNintendoWareStringPool {
        uint32_t   magic;
        uint32_t   reserve0;
        void      *reserve1;
        uint32_t   string_count;
        uint32_t   empty_string;
    };
}
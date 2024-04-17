#pragma once

#include <cstdint>

namespace vp::res {

    enum class BfresAnimCurveFrameDataType {
        Float = 0x0,
        F16   = 0x1,
        U8    = 0x2,
    };
    enum class BfresAnimCurveValueDataType {
        Float = 0,
        S32   = 0,
        S16   = 1,
        S8    = 2,
    };
    enum class BfresAnimCurveCurveType {
        CubicFloat,
        LinearFloat,
        BakedFloat,
        StepInteger,
        BakedInteger,
        StepBoolean,
        BakedBoolean,
    };
    enum class BfresAnimCurveWrapMode {
        Clamp,
        Repeat,
        Mirror,
        RelativeRepeat,
    };

    struct ResBfresAnimCurve {
        union {
            float      *frame_array_f32;
            int16_t    *frame_array_f16;
            uint8_t    *frame_array_u8;
        };
        union {
            float     *value_array_f32;
            int32_t   *value_array_s32;
            int16_t   *value_array_s16;
            int8_t    *value_array_s8;
        };
        uint16_t   frame_data_type : 2;
        uint16_t   value_data_type : 2;
        uint16_t   curve_type      : 3;
        uint16_t   reserve0        : 1;
        uint16_t   pre_wrap_mode   : 2;
        uint16_t   reserve1        : 2;
        uint16_t   post_wrap_mode  : 2;
        uint16_t   reserve2        : 2;
        uint16_t   frame_count;
        uint32_t   base_value;
        float start_key;
        float end_key;
        float frame_data_scale;
        float frame_data_add;
        float frame_delta;
        uint32_t   reserve3;
    };
    static_assert(sizeof(ResBfresAnimCurve) == 0x30);
}


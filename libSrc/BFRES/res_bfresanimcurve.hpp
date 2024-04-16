#pragma once

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
            float *frame_array_f32;
            s16   *frame_array_f16;
            u8    *frame_array_u8;
        };
        union {
            float *value_array_f32;
            s32   *value_array_s32;
            s16   *value_array_s16;
            s8    *value_array_s8;
        };
        u16   frame_data_type : 2;
        u16   value_data_type : 2;
        u16   curve_type      : 3;
        u16   reserve0        : 1;
        u16   pre_wrap_mode   : 2;
        u16   reserve1        : 2;
        u16   post_wrap_mode  : 2;
        u16   reserve2        : 2;
        u16   frame_count;
        u32   base_value;
        float start_key;
        float end_key;
        float frame_data_scale;
        float frame_data_add;
        float frame_delta;
        u32   reserve3;
    };
    static_assert(sizeof(ResBfresAnimCurve) == 0x30);
}

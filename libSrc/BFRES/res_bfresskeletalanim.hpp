#pragma once

#include "res_bfresanimcurve.hpp"
#include "res_gfxcommon.hpp"
#include "res_nintendowaredictionary.hpp"
#include "res_bfresskeleton.hpp"
#include "../usefulFunctions/usefulStructs.h"

namespace vp::res {

    enum class BfresBoneAnimCurveType : uint16_t {
        ScaleX      = (1 << 0),
        ScaleY      = (1 << 1),
        ScaleZ      = (1 << 2),
        RotateX     = (1 << 3),
        RotateY     = (1 << 4),
        RotateZ     = (1 << 5),
        RotateW     = (1 << 6),
        TranslateX  = (1 << 7),
        TranslateY  = (1 << 8),
        TranslateZ  = (1 << 9),
    };

    struct ResBfresBoneAnimResultDefault {
        util::Vector3f translate;
        util::Vector4f rotate;
        util::Vector3f scale;
    };
    static_assert(sizeof(ResBfresBoneAnimResultDefault) == sizeof(float) * 10);

    struct ResBfresBoneAnim {
        const char                    *bone_name;
        ResBfresAnimCurve             *anim_curve_array;
        ResBfresBoneAnimResultDefault *default_result;
        ResGfxUserData                *user_data_array;
        ResNintendoWareDictionary     *user_data_dictionary;
        uint32_t                            reserve0            : 3;
        uint32_t                            is_use_scale        : 1;
        uint32_t                            is_use_rotation     : 1;
        uint32_t                            is_use_translation  : 1;
        uint32_t                            curve_type          : 10;
        uint32_t                            reserve1            : 5;
        uint32_t                            transform_mode      : 5;
        uint32_t                            reserve2            : 6;
        uint8_t                             reserve3;
        uint8_t                             reserve4;
        uint8_t                             anim_curve_count;
        uint8_t                             reserve5;
        uint32_t                            base_curve_index;
        uint16_t                            user_data_count;
        uint16_t                            reserve6;
    };
    static_assert(sizeof(ResBfresBoneAnim) == 0x38);

    struct ResBfresSkeletalAnim {
        uint32_t                        magic;
        uint32_t                        is_baked       : 1;
        uint32_t                        reserve0       : 1;
        uint32_t                        is_looping     : 1;
        uint32_t                        reserve1       : 5;
        uint32_t                        scale_mode     : 2;
        uint32_t                        reserve2       : 2;
        uint32_t                        rotation_mode  : 1;
        uint32_t                        reserve3       : 19;
        const char                *animation_name;
        const char                *reserve4;
        ResBfresSkeleton          *user_bound_skeleton;
        uint16_t                       *bind_table;
        ResBfresBoneAnim          *bone_anim_array;
        ResGfxUserData            *user_data_array;
        ResNintendoWareDictionary *user_data_dictionary;
        uint32_t                        frame_count;
        uint32_t                        total_anim_curves;
        uint32_t                        baked_size;
        uint16_t                        bone_anim_count;
        uint16_t                        user_data_count;

        static constexpr uint32_t cMagic = 0x46534B41;
    };
    static_assert(sizeof(ResBfresSkeletalAnim) == 0x50);
}

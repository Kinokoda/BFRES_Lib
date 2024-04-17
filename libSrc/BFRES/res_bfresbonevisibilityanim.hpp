#pragma once

#include <cstdint>
#include "res_bfresmodel.hpp"

namespace vp::res {
    struct ResBfresModel;  // Forward declaration

    struct ResBfresBoneVisibilityAnim {
        uint32_t                         magic;
        uint32_t                         is_baked        : 1;
        uint32_t                         reserve0        : 1;
        uint32_t                         is_looping      : 1;
        uint32_t                         reserve1        : 29;
        const char                       *animation_name;
        const char                       *reserve2;
        ResBfresModel                    *user_bound_model;
        uint16_t                         *bind_table;
        ResBfresAnimCurve                *anim_curve_array;
        bool                             *default_result_array;
        const char                       **bound_bone_names;
        ResGfxUserData                   *user_data_array;
        ResNintendoWareDictionary        *user_data_dictionary;
        uint32_t                         frame_count;
        uint32_t                         baked_size;
        uint16_t                         bone_count;
        uint16_t                         anim_curve_count;
        uint16_t                         user_data_count;
        uint16_t                         reserve3;

        static constexpr uint32_t cMagic = 0x46425653;
    };
    static_assert(sizeof(ResBfresBoneVisibilityAnim) == 0x60);
}

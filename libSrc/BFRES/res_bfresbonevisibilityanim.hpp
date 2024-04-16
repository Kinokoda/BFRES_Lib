#pragma once

namespace vp::res {

    struct ResBfresBoneVisibilityAnim {
        u32                         magic;
        u32                         is_baked        : 1;
        u32                         reserve0        : 1;
        u32                         is_looping      : 1;
        u32                         reserve1        : 29;
        const char                 *animation_name;
        const char                 *reserve2;
        ResBfresModel              *user_bound_model;
        u16                        *bind_table;
        ResBfresAnimCurve          *anim_curve_array;
        bool                       *default_result_array;
        const char                **bound_bone_names;
        ResGfxUserData             *user_data_array;
        ResNintendoWareDictionary  *user_data_dictionary;
        u32                         frame_count;
        u32                         baked_size;
        u16                         bone_count;
        u16                         anim_curve_count;
        u16                         user_data_count;
        u16                         reserve3;

        static constexpr u32 cMagic = util::TCharCode32("FBVS");
    };
    static_assert(sizeof(ResBfresBoneVisibilityAnim) == 0x60);
}

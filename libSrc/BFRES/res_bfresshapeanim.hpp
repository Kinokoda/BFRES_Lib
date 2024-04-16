#pragma once

namespace vp::res {

    struct ResBfresKeyShapeAnim {
        const char *name;
        u8          anim_curve_index;
        u8          reserve0;
        u16         reserve1;
        u32         reserve2;
    };
    static_assert(sizeof(ResBfresKeyShapeAnim) == 0x10);

    struct ResBfresVertexShapeAnim {
        const char           *name;
        ResBfresAnimCurve    *anim_curve_array;
        float                *default_shapes;
        ResBfresKeyShapeAnim *key_shape_array;
        u16                   anim_curve_count;
        u16                   key_shape_anim_count;
        u32                   base_curve;
        u32                   base_key_shape_anim;
        u32                   reverse0;
    };
    static_assert(sizeof(ResBfresVertexShapeAnim) == 0x30);

    struct ResBfresShapeAnim {
        u32                        magic;
        u32                        is_baked        : 1;
        u32                        reserve0        : 1;
        u32                        is_looping      : 1;
        u32                        reserve1        : 29;
        const char                *animation_name;
        const char                *reserve2;
        ResBfresModel             *user_bound_model;
        u16                       *bind_table;
        ResBfresVertexShapeAnim   *vertex_shape_anim_array;
        ResGfxUserData            *user_data_array;
        ResNintendoWareDictionary *user_data_dictionary;
        u32                        frame_count;
        u32                        baked_size;
        u16                        user_data_count;
        u16                        vertex_shape_anim_count;
        u16                        total_key_shape_anims;
        u16                        total_anim_curves;

        static constexpr u32 cMagic = util::TCharCode32("FSHA");
    };
    static_assert(sizeof(ResBfresShapeAnim) == 0x50);
}

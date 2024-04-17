#pragma once

#include <cstdint>
#include "res_bfresanimcurve.hpp"
#include "res_bfresmodel.hpp"

namespace vp::res {

    struct ResBfresKeyShapeAnim {
        const char *name;
        uint8_t          anim_curve_index;
        uint8_t          reserve0;
        uint16_t         reserve1;
        uint32_t         reserve2;
    };
    static_assert(sizeof(ResBfresKeyShapeAnim) == 0x10);

    struct ResBfresVertexShapeAnim {
        const char           *name;
        ResBfresAnimCurve    *anim_curve_array;
        float                *default_shapes;
        ResBfresKeyShapeAnim *key_shape_array;
        uint16_t                   anim_curve_count;
        uint16_t                   key_shape_anim_count;
        uint32_t                   base_curve;
        uint32_t                   base_key_shape_anim;
        uint32_t                   reverse0;
    };
    static_assert(sizeof(ResBfresVertexShapeAnim) == 0x30);

    struct ResBfresShapeAnim {
        uint32_t                        magic;
        uint32_t                        is_baked        : 1;
        uint32_t                        reserve0        : 1;
        uint32_t                        is_looping      : 1;
        uint32_t                        reserve1        : 29;
        const char                *animation_name;
        const char                *reserve2;
        ResBfresModel             *user_bound_model;
        uint16_t                       *bind_table;
        ResBfresVertexShapeAnim   *vertex_shape_anim_array;
        ResGfxUserData            *user_data_array;
        ResNintendoWareDictionary *user_data_dictionary;
        uint32_t                        frame_count;
        uint32_t                        baked_size;
        uint16_t                        user_data_count;
        uint16_t                        vertex_shape_anim_count;
        uint16_t                        total_key_shape_anims;
        uint16_t                        total_anim_curves;

        static constexpr uint32_t cMagic = 0x46534841;
    };
    static_assert(sizeof(ResBfresShapeAnim) == 0x50);
}

#pragma once

#include <cstdint>
#include "res_bfresanimcurve.hpp"
#include "res_gfxcommon.hpp"
#include "res_nintendowaredictionary.hpp"
#include "res_bfresmodel.hpp"


namespace vp::res {

    struct ResBfresShaderParamAnim {
        const char *shader_param_name;
        uint16_t         base_curve;
        uint16_t         float_curve_count;
        uint16_t         int_curve_count;
        uint16_t         base_constant;
        uint16_t         constant_count;
        uint16_t         material_sub_shader_param_index;
        uint32_t         reserve0;
    };
    static_assert(sizeof(ResBfresShaderParamAnim) == 0x18);

    struct ResBfresTexturePatternAnim {
        const char *texture_name;
        uint16_t         base_curve;
        uint16_t         base_constant;
        uint8_t          material_sub_sampler_index;
        uint8_t          reserve0;
        uint16_t         reserve1;
    };
    static_assert(sizeof(ResBfresTexturePatternAnim) == 0x10);

    struct ResBfresMaterialAnimData {
        const char                 *model_name;
        ResBfresShaderParamAnim    *shader_param_anim_array;
        ResBfresTexturePatternAnim *texture_pattern_anim_array;
        ResBfresAnimCurve          *anim_curve_array;
        void                       *constant_array;
        uint16_t                         base_shader_param_curve_index;
        uint16_t                         base_texture_pattern_curve_index;
        uint16_t                         base_visibility_curve_index;
        uint16_t                         visibility_curve_index;
        uint16_t                         visibility_constant_index;
        uint16_t                         shader_param_anim_count;
        uint16_t                         texture_pattern_anim_count;
        uint16_t                         constant_count;
        uint16_t                         anim_curve_count;
        uint16_t                         reserve0;
        uint32_t                         reserve1;
    };
    static_assert(sizeof(ResBfresMaterialAnimData) == 0x40);

    struct ResBfresMaterialAnim  {
        uint32_t                         magic;
        uint32_t                         is_baked        : 1;
        uint32_t                         reserve0        : 1;
        uint32_t                         is_looping      : 1;
        uint32_t                         reserve1        : 29;
        const char                 *animation_name;
        const char                 *reserve2;
        ResBfresModel              *user_bound_model;
        uint16_t                        *bind_table;
        ResBfresMaterialAnimData   *material_anim_data_array;
        void                      **user_texture_view_array;
        const char                **texture_name_array;
        ResGfxUserData             *user_data_array;
        ResNintendoWareDictionary  *user_data_dictionary;
        uint64_t                        *user_texture_descriptor_slot_array;
        uint32_t                         frame_count;
        uint32_t                         bake_size;
        uint16_t                         user_data_count;
        uint16_t                         per_material_anim_count;
        uint16_t                         total_anim_curves;
        uint16_t                         shader_param_anim_count;
        uint16_t                         texture_pattern_anim_count;
        uint16_t                         material_visibility_anim_count;
        uint16_t                         texture_count;
        uint16_t                         reserve3;

        static constexpr uint32_t cMagic = 0x464D4141;

        void BindTexture(GfxBindTextureCallback bind_callback, ResBntx *res_bntx) {
            for (uint32_t i = 0; i < texture_count; ++i) {
                if (user_texture_view_array[i] != nullptr && user_texture_descriptor_slot_array[i] != 0xffff'ffff'ffff'ffff) { continue; }
        
                GfxBindTextureReturn ret       = (bind_callback)(res_bntx, texture_name_array[i] + 2);
                user_texture_view_array[i]            = ret.texture_view;
                user_texture_descriptor_slot_array[i] = ret.texture_view_decriptor_slot;
            }
        }
    };
    static_assert(sizeof(ResBfresMaterialAnim) == 0x70);
}

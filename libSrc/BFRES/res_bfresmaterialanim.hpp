#pragma once

namespace vp::res {

    struct ResBfresShaderParamAnim {
        const char *shader_param_name;
        u16         base_curve;
        u16         float_curve_count;
        u16         int_curve_count;
        u16         base_constant;
        u16         constant_count;
        u16         material_sub_shader_param_index;
        u32         reserve0;
    };
    static_assert(sizeof(ResBfresShaderParamAnim) == 0x18);

    struct ResBfresTexturePatternAnim {
        const char *texture_name;
        u16         base_curve;
        u16         base_constant;
        u8          material_sub_sampler_index;
        u8          reserve0;
        u16         reserve1;
    };
    static_assert(sizeof(ResBfresTexturePatternAnim) == 0x10);

    struct ResBfresMaterialAnimData {
        const char                 *model_name;
        ResBfresShaderParamAnim    *shader_param_anim_array;
        ResBfresTexturePatternAnim *texture_pattern_anim_array;
        ResBfresAnimCurve          *anim_curve_array;
        void                       *constant_array;
        u16                         base_shader_param_curve_index;
        u16                         base_texture_pattern_curve_index;
        u16                         base_visibility_curve_index;
        u16                         visibility_curve_index;
        u16                         visibility_constant_index;
        u16                         shader_param_anim_count;
        u16                         texture_pattern_anim_count;
        u16                         constant_count;
        u16                         anim_curve_count;
        u16                         reserve0;
        u32                         reserve1;
    };
    static_assert(sizeof(ResBfresMaterialAnimData) == 0x40);

    struct ResBfresMaterialAnim  {
        u32                         magic;
        u32                         is_baked        : 1;
        u32                         reserve0        : 1;
        u32                         is_looping      : 1;
        u32                         reserve1        : 29;
        const char                 *animation_name;
        const char                 *reserve2;
        ResBfresModel              *user_bound_model;
        u16                        *bind_table;
        ResBfresMaterialAnimData   *material_anim_data_array;
        void                      **user_texture_view_array;
        const char                **texture_name_array;
        ResGfxUserData             *user_data_array;
        ResNintendoWareDictionary  *user_data_dictionary;
        u64                        *user_texture_descriptor_slot_array;
        u32                         frame_count;
        u32                         bake_size;
        u16                         user_data_count;
        u16                         per_material_anim_count;
        u16                         total_anim_curves;
        u16                         shader_param_anim_count;
        u16                         texture_pattern_anim_count;
        u16                         material_visibility_anim_count;
        u16                         texture_count;
        u16                         reserve3;

        static constexpr u32 cMagic = util::TCharCode32("FMAA");

        void BindTexture(GfxBindTextureCallback bind_callback, ResBntx *res_bntx) {
            for (u32 i = 0; i < texture_count; ++i) {
                if (user_texture_view_array[i] != nullptr && user_texture_descriptor_slot_array[i] != 0xffff'ffff'ffff'ffff) { continue; }
        
                GfxBindTextureReturn ret       = (bind_callback)(res_bntx, texture_name_array[i] + 2);
                user_texture_view_array[i]            = ret.texture_view;
                user_texture_descriptor_slot_array[i] = ret.texture_view_decriptor_slot;
            }
        }
    };
    static_assert(sizeof(ResBfresMaterialAnim) == 0x70);
}

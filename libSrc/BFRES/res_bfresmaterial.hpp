#pragma once

#include <cstdint>
#include "res_nintendowaredictionary.hpp"
#include "res_gfxcommon.hpp"
#include "../usefulFunctions/usefulStructs.h"

namespace vp::res {
    
    enum class BfresRenderInfoDataType : uint8_t {
        S32    = 0x0,
        Float  = 0x1,
        String = 0x2
    };

    struct ResBfresRenderInfo {
        const char                    *render_info_name;
        BfresRenderInfoDataType       data_type;
        uint8_t                       reserve0;
        uint16_t                      reserve1;
        uint32_t                      reserve2;
    };
    static_assert(sizeof(ResBfresRenderInfo) == 0x10);

    enum class BfresShaderParamDataType : uint8_t {
        Bool                      = 0x0,
        Vec2Bool                  = 0x1,
        Vec3Bool                  = 0x2,
        Vec4Bool                  = 0x3,
        S32                       = 0x4,
        Vec2S32                   = 0x5,
        Vec3S32                   = 0x6,
        Vec4S32                   = 0x7,
        U32                       = 0x8,
        Vec2U32                   = 0x9,
        Vec3U32                   = 0xa,
        Vec4U32                   = 0xb,
        Float                     = 0xc,
        Vec2Float                 = 0xd,
        Vec3Float                 = 0xe,
        Vec4Float                 = 0xf,
        Matrix22f                 = 0x11,
        Matrix23f                 = 0x12,
        Matrix24f                 = 0x13,
        Matrix32f                 = 0x15,
        Matrix33f                 = 0x16,
        Matrix34f                 = 0x17,
        Matrix42f                 = 0x19,
        Matrix43f                 = 0x1a,
        Matrix44f                 = 0x1b,
        Srt2d                     = 0x1c,
        Srt3d                     = 0x1d,
        SrtTexture                = 0x1e,
        SrtTextureWithUserPointer = 0x1f,
    };
    
    struct ResBfresSrt2d {
        util::Vector2f scale;
        float          rotation;
        util::Vector2f translation;
    };

    struct ResBfresSrt3d {
        util::Vector3f scale;
        util::Vector3f rotation;
        util::Vector3f translation;
    };

    enum class BfresSrtMode : uint32_t {
        Maya      = 0,
        Max       = 1,
        SoftImage = 2,
    };

    struct ResBfresTextureSrt {
        BfresSrtMode   srt_mode;
        util::Vector2f scale;
        float          rotation;
        util::Vector2f translation;
    };

    struct ResBfresTextureSrtWithUserPointer {
        BfresSrtMode    srt_mode;
        util::Vector2f  scale;
        float           rotation;
        util::Vector2f  translation;
        void            *user_pointer;
    };

    struct ResBfresShaderParam;

    using ConvertTextureSrtFunction = uint32_t (*)(void*, const void*, ResBfresShaderParam*, void*);

    struct ResBfresShaderParam {
        ConvertTextureSrtFunction        *convert_texture_srt_callback;
        const char                       *shader_param_name;
        uint16_t                         shader_param_offset;
        BfresShaderParamDataType         data_type;
        uint8_t                          reserve0;
        uint32_t                         reserve1;
    };
    static_assert(sizeof(ResBfresShaderParam) == 0x18);


    struct ResBfresShaderReflection {
        const char                      *shader_archive_name;
        const char                      *shader_name;
        ResBfresRenderInfo              *render_info_array;
        ResNintendoWareDictionary       *render_info_dictionary;
        ResBfresShaderParam             *shader_param_array;
        ResNintendoWareDictionary       *shader_param_dictionary;
        ResNintendoWareDictionary       *vertex_attribute_dictionary;
        ResNintendoWareDictionary       *sampler_dictionary;
        ResNintendoWareDictionary       *static_shader_option_dictionary;
        uint16_t                        render_info_count;
        uint16_t                        shader_param_count;
        uint16_t                        shader_param_data_size;
        uint16_t                        reserve0;
        uint64_t                        reserve1;
    };
    static_assert(sizeof(ResBfresShaderReflection) == 0x58);


    struct ResBfresMaterialShaderData {
        ResBfresShaderReflection       *shader_reflection;
        const char                     **vertex_attribute_name_array;
        uint8_t                        *vertex_attribute_index_array;
        const char                     **sampler_name_array;
        uint8_t                        *sampler_index_array;
        uint32_t                       *static_shader_option_packed_bool_value_array;
        const char                     **static_shader_option_string_value_array;
        uint16_t                       *static_option_indice_array;
        uint32_t                        reserve0;
        uint8_t                         vertex_attribute_count;
        uint8_t                         sampler_count;
        uint16_t                        bool_static_option_count;
        uint16_t                        total_static_option_count;
        uint16_t                        reserve1;
        uint32_t                        reserve2;
    };
    static_assert(sizeof(ResBfresMaterialShaderData) == 0x50);


    struct ResBfresMaterial {
        uint32_t                          magic;
        uint32_t                          is_material_visible;
        const char                        *material_name;
        ResBfresMaterialShaderData        *material_shader_data;
        void                              **user_texture_view_array;
        const char                        **texture_name_array;
        void                              *sampler_array;
        ResGfxSamplerInfo                 *sampler_info_array;
        ResNintendoWareDictionary         *sampler_dictionary;
        void                              *render_info_value_array;
        uint16_t                          *render_info_value_count_array;
        uint16_t                          *render_info_value_offset_array;
        void                              *shader_param_value_array;
        int32_t                           *shader_param_ubo_offset_array;
        void                              *reserve0;
        ResGfxUserData                    *user_data_array;
        ResNintendoWareDictionary         *user_data_dictionary;
        uint32_t                          *shader_param_convert_flags_array;
        void                              *user_pointer;
        uint64_t                          *user_sampler_descriptor_slot_array;
        uint64_t                          *user_texture_descriptor_slot_array;
        uint16_t                          section_index;
        uint8_t                           sampler_count;
        uint8_t                           texture_count;
        uint16_t                          reserve1;
        uint16_t                          user_data_count;
        uint16_t                          unknown_size;
        uint16_t                          user_shading_model_option_ubo_size;
        uint32_t                          reserve2;

        static constexpr uint32_t cMagic = 0x464D4154;


        void BindTexture(GfxBindTextureCallback bind_callback, ResBntx *res_bntx) {
            for (uint32_t i = 0; i < sampler_count; ++i) {
                if (user_texture_view_array[i] != nullptr && user_texture_descriptor_slot_array[i] != 0xffff'ffff'ffff'ffff) { continue; }

                GfxBindTextureReturn ret              = (bind_callback)(res_bntx, texture_name_array[i] + 2);
                user_texture_descriptor_slot_array[i] = ret.texture_view_decriptor_slot;
                user_texture_view_array[i]            = ret.texture_view;
            }
        }

        inline uint32_t GetStaticShaderOptionIndex(const char *option_name) {
            const uint32_t dic_index = material_shader_data->shader_reflection->static_shader_option_dictionary->FindEntryIndex(option_name);
            return (material_shader_data->static_option_indice_array != nullptr) ? material_shader_data->static_option_indice_array[material_shader_data->total_static_option_count + dic_index] : dic_index;
        }


        constexpr inline bool IsStaticShaderOptionBool(uint32_t option_index) {
            return (material_shader_data->bool_static_option_count > option_index);
        }


        constexpr inline bool IsStaticShaderOptionString(uint32_t option_index) {
            return (material_shader_data->bool_static_option_count < option_index);
        }


        constexpr inline int32_t GetStaticShaderOptionBool(uint32_t option_index) {
            return (material_shader_data->bool_static_option_count <= option_index) ? -1 : ((material_shader_data->static_shader_option_packed_bool_value_array[(option_index / 32)] & 0x7fff'ffff) >> (option_index & 0x1f)) & 1;
        }


        constexpr inline const char *GetStaticShaderOptionString(uint32_t option_index) {
            return (option_index < material_shader_data->bool_static_option_count || material_shader_data->total_static_option_count <= option_index) ? nullptr : material_shader_data->static_shader_option_string_value_array[(option_index - material_shader_data->bool_static_option_count)];
        }


        inline const char *GetShaderVertexAttributeName(const char *attribute_name) {
            for (uint32_t i = 0; i < material_shader_data->vertex_attribute_count; ++i) {
                if (::strcmp(material_shader_data->vertex_attribute_name_array[i] + 2, attribute_name) == 0) { return material_shader_data->shader_reflection->vertex_attribute_dictionary->FindKeyByEntryIndex((material_shader_data->vertex_attribute_index_array != nullptr) ? material_shader_data->vertex_attribute_index_array[i] : i); }
            }
            return nullptr;
        }


        inline const char *GetShaderSamplerName(const char *sampler_name) {
            for (uint32_t i = 0; i < material_shader_data->sampler_count; ++i) {
                if (::strcmp(material_shader_data->sampler_name_array[i] + 2, sampler_name) == 0) { return material_shader_data->shader_reflection->sampler_dictionary->FindKeyByEntryIndex((material_shader_data->sampler_index_array != nullptr) ? material_shader_data->sampler_index_array[i] : i); }
            }
            return nullptr; 
        }


        inline const char *GetTextureName(const char *sampler_name) {
            const uint32_t entry_index = sampler_dictionary->FindEntryIndex(sampler_name);
            return (entry_index != 0xffff'ffff) ? texture_name_array[entry_index] : nullptr;
        }

        inline ResGfxSamplerInfo *GetSamplerInfo(const char *sampler_name) {
            const uint32_t entry_index = sampler_dictionary->FindEntryIndex(sampler_name);
            return (entry_index != 0xffff'ffff) ? std::addressof(sampler_info_array[entry_index]) : nullptr;
        }
    };
    static_assert(sizeof(ResBfresMaterial) == 0xb0);
}

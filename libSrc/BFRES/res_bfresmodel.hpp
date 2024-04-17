#pragma once

#include "res_nintendowaredictionary.hpp"
#include "res_bfresskeletalanim.hpp"
#include "res_bfresmaterialanim.hpp"
#include "res_bfresbonevisibilityanim.hpp"
#include "res_bfresshapeanim.hpp"
#include "res_nintendowarefileheader.hpp"
#include "res_gfxcommon.hpp"
#include "res_bfressceneanim.hpp"
#include "res_bfresskeleton.hpp"
#include "res_bfresshape.hpp"
#include "res_bfresmaterial.hpp"


namespace vp::res {

    struct ResBfresModel {
        uint32_t                        magic;
        uint32_t                        reserve0;
        const char                *model_name;
        const char                *reserve1;
        ResBfresSkeleton          *skeleton;
        ResBfresVertex            *vertex_array;
        ResBfresShape             *shape_array;
        ResNintendoWareDictionary *shape_dictionary;
        ResBfresMaterial          *material_array;
        ResNintendoWareDictionary *material_dictionary;
        ResBfresShaderReflection  *shader_reflection_array;
        ResGfxUserData            *user_data_array;
        ResNintendoWareDictionary *user_data_dictionary;
        void                      *user_pointer;
        uint16_t                        vertex_count;
        uint16_t                        shape_count;
        uint16_t                        material_count;
        uint16_t                        shader_reflection_count;
        uint16_t                        user_data_count;
        uint16_t                        reserve2;
        uint32_t                        reserve3;

        static constexpr uint32_t cMagic = 0x464D444C;

        void BindTexture(GfxBindTextureCallback bind_callback, ResBntx *res_bntx) {
            for (uint32_t i = 0; i < material_count; ++i) {
                material_array[i].BindTexture(bind_callback, res_bntx);
            }
        }
    };
    static_assert(sizeof(ResBfresModel) == 0x78);
}

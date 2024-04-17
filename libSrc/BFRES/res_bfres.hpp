#pragma once

#include "res_nintendowaredictionary.hpp"
#include "res_bfresmodel.hpp"
#include "res_bfresskeletalanim.hpp"
#include "res_bfresmaterialanim.hpp"
#include "res_bfresbonevisibilityanim.hpp"
#include "res_bfresshapeanim.hpp"
#include "res_nintendowarefileheader.hpp"
#include "res_gfxcommon.hpp"
#include "res_bfressceneanim.hpp"


namespace vp::res {

    struct ResBfres : public ResNintendoWareFileHeader {
        const char                 *fres_name;
        ResBfresModel              *model_array;
        ResNintendoWareDictionary  *model_dictionary;
        uint64_t                         reserve0;
        uint64_t                         reserve1;
        uint64_t                         reserve2;
        uint64_t                         reserve3;
        ResBfresSkeletalAnim       *skeletal_anim_array;
        ResNintendoWareDictionary  *skeletal_anim_dictionary;
        ResBfresMaterialAnim       *material_anim_array;
        ResNintendoWareDictionary  *material_anim_dictionary;
        ResBfresBoneVisibilityAnim *bone_visibility_anim_array;
        ResNintendoWareDictionary  *bone_visibility_anim_dictionary;
        ResBfresShapeAnim          *shape_anim_array;
        ResNintendoWareDictionary  *shape_anim_dictionary;
        ResBfresSceneAnim          *scene_anim_array;
        ResNintendoWareDictionary  *scene_anim_dictionary;
        void                       *user_memory_pool;
        ResGfxMemoryPoolInfo       *memory_pool_info;
        ResGfxEmbedFile            *embed_file_array;
        ResNintendoWareDictionary  *embed_file_dictionary;
        void                       *user_pointer;
        const char                 *reserve4;
        uint32_t                         reserve5;
        uint16_t                         model_count;
        uint16_t                         reserve6;
        uint16_t                         reserve7;
        uint16_t                         skeletal_anim_count;
        uint16_t                         material_anim_count;
        uint16_t                         bone_visibility_anim_count;
        uint16_t                         shape_anim_count;
        uint16_t                         scene_anim_count;
        uint16_t                         embed_file_count;
        union {
            uint8_t                      external_options;
            struct {
                uint8_t                  is_external_model_uninitalized : 1;
                uint8_t                  has_external_strings           : 1;
                uint8_t                  holds_external_strings         : 1;
                uint8_t                  is_external_gpu_region         : 1;
                uint8_t                  reserve9                       : 4;
            };
        };
        uint8_t                          reserve10;

        static constexpr uint64_t cMagic = 0x4652455320202020;

        static ResBfres *ResCast(void *file) {
            ResBfres *fres = reinterpret_cast<ResBfres*>(file);
            if (fres == nullptr || fres->ResNintendoWareFileHeader::IsValid(cMagic, 10, 0) == false) { return nullptr; }
            fres->Relocate();
            return fres;
        }

        static bool IsValid(void *file) {
            ResBfres *fres = reinterpret_cast<ResBfres*>(file);
            return fres->ResNintendoWareFileHeader::IsValid(cMagic, 10, 0, 0);
        }
        
        void BindTextures(GfxBindTextureCallback bind_callback, ResBntx *res_bntx) {
            for (uint32_t i = 0; i < model_count; ++i) {
                model_array[i].BindTexture(bind_callback, res_bntx);
            }
            for (uint32_t i = 0; i < material_anim_count; ++i) {
                material_anim_array[i].BindTexture(bind_callback, res_bntx);
            }
        }

        constexpr inline uint64_t GetGpuMemorySize() {
            return (memory_pool_info == nullptr) ? 0xffff'ffff'ffff'ffff : memory_pool_info->size;
        }

        constexpr inline void *GetGpuMemoryRegion() {
            return (memory_pool_info == nullptr) ? nullptr : memory_pool_info->storage;
        }
    };
    static_assert(sizeof(ResBfres) == 0xf0);
}

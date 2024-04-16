#pragma once

namespace vp::res {

    struct ResBfres : public ResNintendoWareFileHeader {
        const char                 *fres_name;
        ResBfresModel              *model_array;
        ResNintendoWareDictionary  *model_dictionary;
        u64                         reserve0;
        u64                         reserve1;
        u64                         reserve2;
        u64                         reserve3;
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
        u32                         reserve5;
        u16                         model_count;
        u16                         reserve6;
        u16                         reserve7;
        u16                         skeletal_anim_count;
        u16                         material_anim_count;
        u16                         bone_visibility_anim_count;
        u16                         shape_anim_count;
        u16                         scene_anim_count;
        u16                         embed_file_count;
        union {
            u8                      external_options;
            struct {
                u8                  is_external_model_uninitalized : 1;
                u8                  has_external_strings           : 1;
                u8                  holds_external_strings         : 1;
                u8                  is_external_gpu_region         : 1;
                u8                  reserve9                       : 4;
            };
        };
        u8                          reserve10;

        static constexpr u64 cMagic = util::TCharCode64("FRES    ");

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
            for (u32 i = 0; i < model_count; ++i) {
                model_array[i].BindTexture(bind_callback, res_bntx);
            }
            for (u32 i = 0; i < material_anim_count; ++i) {
                material_anim_array[i].BindTexture(bind_callback, res_bntx);
            }
        }

        constexpr ALWAYS_INLINE u64 GetGpuMemorySize() {
            return (memory_pool_info == nullptr) ? 0xffff'ffff'ffff'ffff : memory_pool_info->size;
        }

        constexpr ALWAYS_INLINE void *GetGpuMemoryRegion() {
            return (memory_pool_info == nullptr) ? nullptr : memory_pool_info->storage;
        }
    };
    static_assert(sizeof(ResBfres) == 0xf0);
}

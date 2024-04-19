#pragma once

#include <cstdint>
#include "res_gfxcommon.hpp"
#include "res_nintendowaredictionary.hpp"
#include "../usefulFunctions/usefulStructs.h"

namespace vp::res {

    enum class BfresBoneBillboardMode {
        None,
        Child,
        WorldViewVector,
        WorldViewPoint,
        ScreenViewVector,
        ScreenViewPoint,
        YAxisViewVector,
        YAxisViewPoint,
    };
    enum class BfresBoneLocalTransformMode : uint8_t {
        None                    = (1 << 0),
        SegmentScaleCompensate  = (1 << 1),
        ScaleUniform            = (1 << 2),
        ScaleVolumeOne          = (1 << 3),
        NoRotation              = (1 << 4),
        NoTranslation           = (1 << 5),
    };
    enum class BfresBoneHierarchyTransformMode {
        None                    = (1 << 0),
        ScaleUniform            = (1 << 1),
        ScaleVolumeOne          = (1 << 2),
        NoRotation              = (1 << 3),
        NoTranslation           = (1 << 4),
    };

    struct ResBfresBone {
        const char                *bone_name;
        ResGfxUserData            *user_data_array;
        ResNintendoWareDictionary *user_data_dictionary;
        void                      *reserve0;
        uint16_t                        bone_index;
        uint16_t                        bone_parent_index;
        uint16_t                        smooth_bone_index;
        uint16_t                        rigid_bone_index;
        uint16_t                        billboard_index;
        uint16_t                        user_data_count;
        uint32_t                        reserve1                 : 8;
        uint32_t                        unknown0                 : 4;
        uint32_t                        is_bone_visible          : 1;
        uint32_t                        unknown1                 : 3;
        uint32_t                        billboard_mode           : 3;
        uint32_t                        reserve3                 : 1;
        uint32_t                        unknown2                 : 3;
        uint32_t                        local_transform_mode     : 5;
        uint32_t                        hierarchy_transform_mode : 4;
        util::Vector3f             translate;
        util::Vector4f             rotate;
        util::Vector3f             scale;
    };
    static_assert(sizeof(ResBfresBone) == 0x58);

    enum class BfresSkeletonMirrorMode {
        X,
        XY,
        XZ,
    };
    enum class BfresSkeletonScaleMode {
        None,
        Standard,
        Maya,
        SoftImage,
    };
    enum class BfresSkeletonRotationMode {
        Quarternion,
        EulerXYZ,
    };

    struct ResBfresSkeleton {
        uint32_t                        magic;
        uint32_t                        has_user_pointer : 2;
        uint32_t                        reserve0         : 4;
        uint32_t                        mirror_mode      : 2;
        uint32_t                        scale_mode       : 2;
        uint32_t                        reserve1         : 2;
        uint32_t                        rotation_mode    : 2;
        ResNintendoWareDictionary       *bone_dictionary;
        ResBfresBone                    *bone_array;
        uint16_t                        *bone_index_table;
        util::Matrix34f                 *inverse_transformation_matrix_array;
        void                            *user_pointer;
        uint16_t                        *mirrored_bone_index_table;
        uint16_t                        bone_count;
        uint16_t                        smooth_bone_count;
        uint16_t                        rigid_bone_count;
        uint16_t                        reserve2;
        
        static constexpr uint32_t cMagic = 0x46534B4C;
    };
    static_assert(sizeof(ResBfresSkeleton) == 0x40);
}

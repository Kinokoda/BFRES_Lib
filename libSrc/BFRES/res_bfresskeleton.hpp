#pragma once

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
    enum class BfresBoneLocalTransformMode : u8 {
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
        u16                        bone_index;
        u16                        bone_parent_index;
        u16                        smooth_bone_index;
        u16                        rigid_bone_index;
        u16                        billboard_index;
        u16                        user_data_count;
        u32                        reserve1                 : 8;
        u32                        unknown0                 : 4;
        u32                        is_bone_visible          : 1;
        u32                        unknown1                 : 3;
        u32                        billboard_mode           : 3;
        u32                        reserve3                 : 1;
        u32                        unknown2                 : 3;
        u32                        local_transform_mode     : 5;
        u32                        hierarchy_transform_mode : 4;
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
        u32                        magic;
        u32                        has_user_pointer : 2;
        u32                        reserve0         : 4;
        u32                        mirror_mode      : 2;
        u32                        scale_mode       : 2;
        u32                        reserve1         : 2;
        u32                        rotation_mode    : 2;
        ResNintendoWareDictionary *bone_dictionary;
        ResBfresBone              *bone_array;
        u16                       *bone_index_table;
        util::Matrix34f           *inverse_transformation_matrix_array;
        void                      *user_pointer;
        u16                       *mirrored_bone_index_table;
        u16                        bone_count;
        u16                        smooth_bone_count;
        u16                        rigid_bone_count;
        u16                        reserve2;
        
        static constexpr u32 cMagic = util::TCharCode32("FSKL");
    };
    static_assert(sizeof(ResBfresSkeleton) == 0x40);
}

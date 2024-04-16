#pragma once

namespace vp::res {

    struct ResBfresCameraAnimResultDefault {
        float          near;
        float          far;
        float          aspect;
        float          fovy;
        util::Vector3f position;
        util::Vector3f rotation;
        float          twist;
    };
    static_assert(sizeof(ResBfresCameraAnimResultDefault) == 0x2c);

    enum class BfresCameraAnimRotationMode   : u8 {
        Aim,
        EulerZXY,
    };

    enum class BfresCameraAnimProjectionMode : u8 {
        Orthographic,
        Perspective,
    };

    struct ResBfresCameraAnim {
        u32                              magic;
        u32                              is_baked        : 1;
        u32                              reserve0        : 1;
        u32                              is_looping      : 1;
        u32                              reserve1        : 1;
        u32                              rotation_mode   : 1;
        u32                              reserve2        : 1;
        u32                              projection_mode : 1;
        u32                              reserve3        : 25;
        const char                      *animation_name;
        ResBfresAnimCurve               *anim_curve_array;
        ResBfresCameraAnimResultDefault *camera_anim_result_default;
        ResGfxUserData                  *user_data_array;
        ResNintendoWareDictionary       *user_data_dictionary;
        u32                              frame_count;
        u32                              baked_size;
        u16                              user_data_count;
        u8                               anim_curve_count;
        u8                               reserve4;
        u32                              reserve5;

        static constexpr u32 cMagic = util::TCharCode32("FCAM");
    };
    static_assert(sizeof(ResBfresCameraAnim) == 0x40);

    struct ResBfresLightAnimResultDefault {
        s32            enable;
        util::Vector3f position;
        util::Vector3f rotation;
        util::Vector2f distance_attenuation;
        util::Vector2f angle_attenuation;
        util::Vector3f color0;
        util::Vector3f color1;
    };
    static_assert(sizeof(ResBfresLightAnimResultDefault) == 0x44);

    struct ResBfresLightAnim {
        u32                             magic;
        u32                             is_baked                    : 1;
        u32                             reserve0                    : 1;
        u32                             is_looping                  : 1;
        u32                             reserve1                    : 5;
        u32                             is_use_curves               : 1;
        u32                             is_use_enable               : 1;
        u32                             is_use_position             : 1;
        u32                             is_use_rotation             : 1;
        u32                             is_use_distance_attenuation : 1;
        u32                             is_use_angle_attenuation    : 1;
        u32                             is_use_color0               : 1;
        u32                             is_use_color1               : 1;
        u32                             reserve2                    : 16;
        const char                     *animation_name;
        ResBfresAnimCurve              *anim_curve_array;
        ResBfresLightAnimResultDefault *light_anim_result_default;
        ResGfxUserData                 *user_data_array;
        ResNintendoWareDictionary      *user_data_dictionary;
        const char                     *light_type_name;
        const char                     *distance_attenuation_type_name;
        const char                     *angle_attenuation_type_name;
        u32                             frame_count;
        u32                             baked_size;
        u16                             user_data_count;
        u8                              anim_curve_count;
        s8                              light_type;
        s8                              distance_attenuation_type;
        s8                              angle_attenuation_type;
        u16                             reserve3;

        static constexpr u32 cMagic = util::TCharCode32("FLIT");
    };
    static_assert(sizeof(ResBfresLightAnim) == 0x58);

    struct ResBfresFogAnimResultDefault {
        util::Vector2f distance_attenuation;
        util::Vector3f color;
    };
    static_assert(sizeof(ResBfresFogAnimResultDefault) == 0x14);

    struct ResBfresFogAnim {
        u32                           magic;
        u32                           is_baked                    : 1;
        u32                           reserve0                    : 1;
        u32                           is_looping                  : 1;
        u32                           reserve1                    : 29;
        const char                   *animation_name;
        ResBfresAnimCurve            *anim_curve_array;
        ResBfresFogAnimResultDefault *fog_anim_result_default;
        ResGfxUserData               *user_data_array;
        ResNintendoWareDictionary    *user_data_dictionary;
        const char                   *distance_attenuation_type_name;
        u32                           frame_count;
        u32                           baked_size;
        u16                           user_data_count;
        u8                            anim_curve_count;
        s8                            distance_attenuation_type;
        u16                           reserve2;

        static constexpr u32 cMagic = util::TCharCode32("FFOG");
    };
    static_assert(sizeof(ResBfresFogAnim) == 0x48);

    struct ResBfresSceneAnim {
        u32                        magic;
        u32                        reserve0;
        const char                *animation_name;
        const char                *reserve1;
        ResBfresCameraAnim        *camera_anim_array;
        ResNintendoWareDictionary *camera_anim_dictionary;
        ResBfresLightAnim         *light_anim_array;
        ResNintendoWareDictionary *light_anim_dictionary;
        ResBfresFogAnim           *fog_anim_array;
        ResNintendoWareDictionary *fog_anim_dictionary;
        ResGfxUserData            *user_data_array;
        ResNintendoWareDictionary *user_data_dictionary;
        u16                        user_data_count;
        u16                        camera_anim_count;
        u16                        light_anim_count;
        u16                        fog_anim_count;

        static constexpr u32 cMagic = util::TCharCode32("FSCN");
    };
    static_assert(sizeof(ResBfresSceneAnim) == 0x60);
}

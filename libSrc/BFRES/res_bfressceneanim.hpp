#pragma once

#include <cstdint>
#include "res_nintendowaredictionary.hpp"
#include "res_gfxcommon.hpp"
#include "res_bfresanimcurve.hpp"
#include "../usefulFunctions/usefulStructs.h"

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

    enum class BfresCameraAnimRotationMode   : uint8_t {
        Aim,
        EulerZXY,
    };

    enum class BfresCameraAnimProjectionMode : uint8_t {
        Orthographic,
        Perspective,
    };

    struct ResBfresCameraAnim {
        uint32_t                              magic;
        uint32_t                              is_baked        : 1;
        uint32_t                              reserve0        : 1;
        uint32_t                              is_looping      : 1;
        uint32_t                              reserve1        : 1;
        uint32_t                              rotation_mode   : 1;
        uint32_t                              reserve2        : 1;
        uint32_t                              projection_mode : 1;
        uint32_t                              reserve3        : 25;
        const char                      *animation_name;
        ResBfresAnimCurve               *anim_curve_array;
        ResBfresCameraAnimResultDefault *camera_anim_result_default;
        ResGfxUserData                  *user_data_array;
        ResNintendoWareDictionary       *user_data_dictionary;
        uint32_t                              frame_count;
        uint32_t                              baked_size;
        uint16_t                              user_data_count;
        uint8_t                               anim_curve_count;
        uint8_t                               reserve4;
        uint32_t                              reserve5;

        static constexpr uint32_t cMagic = 0x4643414D;
    };
    static_assert(sizeof(ResBfresCameraAnim) == 0x40);

    struct ResBfresLightAnimResultDefault {
        int32_t            enable;
        util::Vector3f position;
        util::Vector3f rotation;
        util::Vector2f distance_attenuation;
        util::Vector2f angle_attenuation;
        util::Vector3f color0;
        util::Vector3f color1;
    };
    static_assert(sizeof(ResBfresLightAnimResultDefault) == 0x44);

    struct ResBfresLightAnim {
        uint32_t                             magic;
        uint32_t                             is_baked                    : 1;
        uint32_t                             reserve0                    : 1;
        uint32_t                             is_looping                  : 1;
        uint32_t                             reserve1                    : 5;
        uint32_t                             is_use_curves               : 1;
        uint32_t                             is_use_enable               : 1;
        uint32_t                             is_use_position             : 1;
        uint32_t                             is_use_rotation             : 1;
        uint32_t                             is_use_distance_attenuation : 1;
        uint32_t                             is_use_angle_attenuation    : 1;
        uint32_t                             is_use_color0               : 1;
        uint32_t                             is_use_color1               : 1;
        uint32_t                             reserve2                    : 16;
        const char                     *animation_name;
        ResBfresAnimCurve              *anim_curve_array;
        ResBfresLightAnimResultDefault *light_anim_result_default;
        ResGfxUserData                 *user_data_array;
        ResNintendoWareDictionary      *user_data_dictionary;
        const char                     *light_type_name;
        const char                     *distance_attenuation_type_name;
        const char                     *angle_attenuation_type_name;
        uint32_t                             frame_count;
        uint32_t                             baked_size;
        uint16_t                             user_data_count;
        uint8_t                              anim_curve_count;
        int8_t                              light_type;
        int8_t                              distance_attenuation_type;
        int8_t                              angle_attenuation_type;
        uint16_t                             reserve3;

        static constexpr uint32_t cMagic = 0x464C4954;
    };
    static_assert(sizeof(ResBfresLightAnim) == 0x58);

    struct ResBfresFogAnimResultDefault {
        util::Vector2f distance_attenuation;
        util::Vector3f color;
    };
    static_assert(sizeof(ResBfresFogAnimResultDefault) == 0x14);

    struct ResBfresFogAnim {
        uint32_t                           magic;
        uint32_t                           is_baked                    : 1;
        uint32_t                           reserve0                    : 1;
        uint32_t                           is_looping                  : 1;
        uint32_t                           reserve1                    : 29;
        const char                   *animation_name;
        ResBfresAnimCurve            *anim_curve_array;
        ResBfresFogAnimResultDefault *fog_anim_result_default;
        ResGfxUserData               *user_data_array;
        ResNintendoWareDictionary    *user_data_dictionary;
        const char                   *distance_attenuation_type_name;
        uint32_t                           frame_count;
        uint32_t                           baked_size;
        uint16_t                           user_data_count;
        uint8_t                            anim_curve_count;
        int8_t                            distance_attenuation_type;
        uint16_t                           reserve2;

        static constexpr uint32_t cMagic = 0x46464F47;
    };
    static_assert(sizeof(ResBfresFogAnim) == 0x48);

    struct ResBfresSceneAnim {
        uint32_t                        magic;
        uint32_t                        reserve0;
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
        uint16_t                        user_data_count;
        uint16_t                        camera_anim_count;
        uint16_t                        light_anim_count;
        uint16_t                        fog_anim_count;

        static constexpr uint32_t cMagic = 0x4653434E;
    };
    static_assert(sizeof(ResBfresSceneAnim) == 0x60);
}

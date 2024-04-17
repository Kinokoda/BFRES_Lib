#pragma once

#include "res_nintendowaredictionary.hpp"
#include "res_gfxcommon.hpp"
#include "../usefulFunctions/usefulStructs.h"

namespace vp::res {

    struct ResBfresVertexBufferStride {
        uint32_t stride;
        uint32_t divisor;
        uint32_t reserve0;
        uint32_t reserve1;
    };
    static_assert(sizeof(ResBfresVertexBufferStride) == 0x10);

    struct ResBfresVertexAttribute {
        const char *attribute_name;
        uint32_t         attribute_format;
        uint16_t         buffer_offset;
        uint8_t          buffer_mask_offset : 6;
        uint8_t          buffer_flag_offset : 2;
        uint8_t          is_dynamic_vbo;
    };
    static_assert(sizeof(ResBfresVertexAttribute) == 0x10);

    struct ResBfresVertex {
        uint32_t                          magic;
        uint32_t                          reserve0;
        ResBfresVertexAttribute     *vertex_attribute_array;
        ResNintendoWareDictionary   *vertex_attribute_dictionary;
        void                        *user_memory_pool_pointer;
        void                        *runtime_vertex_buffer_array;
        void                       **user_vertex_buffer_array;
        ResGfxBufferInfo            *vertex_buffer_info_array;
        ResBfresVertexBufferStride  *vertex_buffer_stride_info_array;
        void                        *user_pointer;
        uint32_t                          base_memory_offset;
        uint8_t                           vertex_attribute_count;
        uint8_t                           vertex_buffer_count;
        uint16_t                          section_index;
        uint32_t                          vertex_count;
        uint16_t                          reserve1;
        uint16_t                          vertex_buffer_alignment;

        static constexpr uint32_t cMagic = 0x46565458;
    };
    static_assert(sizeof(ResBfresVertex) == 0x58);

    struct ResBfresSubMeshRange {
        uint32_t base_memory_offset;
        uint32_t index_count;
    };
    static_assert(sizeof(ResBfresSubMeshRange) == 0x8);

    struct ResBfresMesh {
        ResBfresSubMeshRange *sub_mesh_range_array;
        void                 *user_memory_pool_pointer;
        void                 *user_index_buffer;
        ResGfxBufferInfo     *index_buffer_info;
        uint32_t                   index_buffer_memory_offset;
        uint32_t                   primitive_topology;
        uint32_t                   index_format;
        uint32_t                   index_count;
        uint32_t                   base_index;
        uint16_t                   sub_mesh_count;
        uint16_t                   reserve0;
    };
    static_assert(sizeof(ResBfresMesh) == 0x38);

    struct ResBfresKeyShape {
        uint8_t key_shape_attribute_location_array[18];
        uint8_t reserve[2];
    };
    static_assert(sizeof(ResBfresKeyShape) == 0x14);

    struct ResBfresBounding {
        util::Vector3f center_position;
        util::Vector3f extent;
    };
    static_assert(sizeof(ResBfresBounding) == 0x18);

    struct ResBfresShape {
        uint32_t                        magic;
        uint32_t                        reserve0               : 1;
        uint32_t                        is_bounding_consistent : 1;
        uint32_t                        has_vertex_buffer      : 1;
        uint32_t                        reserve1               : 29;
        const char                *shape_name;
        ResBfresVertex            *vertex;
        ResBfresMesh              *mesh_array;
        uint16_t                       *skin_bone_index_array;
        ResBfresKeyShape          *key_shape_array;
        ResNintendoWareDictionary *key_shape_dictionary;
        ResBfresBounding          *bounding_box_array;
        float                     *bounding_sphere_radius_array;
        void                      *user_pointer;
        uint16_t                        section_index;
        uint16_t                        material_index;
        uint16_t                        bone_index;
        uint16_t                        vertex_index;
        uint16_t                        skin_bone_index_count;
        uint8_t                         max_bone_influences_per_vertex;
        uint8_t                         mesh_count;
        uint8_t                         key_shape_count;
        uint8_t                         target_attribute_count;
        uint16_t                        reserve2;

        static constexpr uint32_t cMagic = 0x46534850;
    };
    static_assert(sizeof(ResBfresShape) == 0x60);
}

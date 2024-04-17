#pragma once

#include <cstdint>

namespace vp::res {

    struct ResBntx;

    struct GfxBindTextureReturn {
        uint64_t   texture_view_decriptor_slot;
        void *texture_view;
    };

    using GfxBindTextureCallback = GfxBindTextureReturn (*) (ResBntx*, const char *);

    enum class GfxMemoryPoolFlags : uint32_t {
        CpuNoAccess  = (1 << 0),
        CpuUncached  = (1 << 1),
        CpuCached    = (1 << 2),
        GpuNoAccess  = (1 << 3),
        GpuUncached  = (1 << 4),
        GpuCached    = (1 << 5),
        ShaderCode   = (1 << 6),
        Compressible = (1 << 7),
        Physical     = (1 << 8),
        Virtual      = (1 << 9),
    };

    enum class GfxGpuAccessFlags : uint32_t {
        VertexBuffer        = (1 << 2),
        IndexBuffer         = (1 << 3),
        UniformBuffer       = (1 << 4),
        Texture             = (1 << 5),
        TransferDestination = (1 << 6),
        RenderTargetColor   = (1 << 7),
        RenderTargetDepth   = (1 << 8),
        IndirectDraw        = (1 << 9),
        DisplayTexture      = (1 << 10),
        Counter             = (1 << 11),
    };

    struct ResGfxMemoryPoolInfo {
        uint32_t   memory_pool_flags;
        uint32_t   size;
        void *storage;
    };
    static_assert(sizeof(ResGfxMemoryPoolInfo) == 0x10);

    struct ResGfxBufferInfo {
        uint32_t size;
        uint32_t gpu_access_flags;
        uint32_t reserve0;
        uint32_t reserve1;
    };
    static_assert(sizeof(ResGfxBufferInfo) == 0x10);

    enum class GfxChannelSource : uint8_t {
        Zero  = 0x0,
        One   = 0x1,
        Red   = 0x2,
        Green = 0x3,
        Blue  = 0x4,
        Alpha = 0x5
    };

    enum class GfxChannelFormat : uint8_t {
        None         = 0x1,
        R8           = 0x2,
        R4G4B4A4     = 0x3,
        R5G5B5A1     = 0x5,
        A1B5G5R5     = 0x6,
        R5G6B5       = 0x7,
        B5G6R5       = 0x8,
        R8G8         = 0x9,
        R16          = 0xa,
        R8G8B8A8     = 0xb,
        B8G8R8A8     = 0xc,
        R9G9B9E5F    = 0xd,
        R10G10B10A2  = 0xe,
        R11G11B10F   = 0xf,
        R16G16       = 0x12,
        D24S8        = 0x13,
        R32          = 0x14,
        R16G16B16A16 = 0x15,
        D32FS8       = 0x16,
        R32G32       = 0x17,
        R32G32B32    = 0x18,
        R32G32B32A32 = 0x19,
        BC1          = 0x1a,
        BC2          = 0x1b,
        BC3          = 0x1c,
        BC4          = 0x1d,
        BC5          = 0x1e,
        BC6H         = 0x1f,
        BC7U         = 0x20,
        ASTC_4x4     = 0x2d,
        ASTC_5x4     = 0x2e,
        ASTC_5x5     = 0x2f,
        ASTC_6x5     = 0x30,
        ASTC_6x6     = 0x31,
        ASTC_8x5     = 0x32,
        ASTC_8x6     = 0x33,
        ASTC_8x8     = 0x34,
        ASTC_10x5    = 0x35,
        ASTC_10x6    = 0x36,
        ASTC_10x8    = 0x37,
        ASTC_10x10   = 0x38,
        ASTC_12x10   = 0x39,
        ASTC_12x12   = 0x3a,
        B5G5R5A1     = 0x3b,
    };

    static constexpr inline uint32_t VariableBlockWidthTable[] = {
        0x10, 0x08, 0x10, 0x08,
        0x08, 0x04, 0x04, 0x05,
        0x05, 0x06, 0x06, 0x08,
        0x08, 0x08, 0x0a, 0x0a,
        0x0a, 0x0a, 0x0c, 0x0c,
    };
    static constexpr inline uint32_t VariableBlockHeightTable[] = {
        0x08, 0x08, 0x08, 0x08,
        0x04, 0x04, 0x04, 0x04,
        0x05, 0x05, 0x06, 0x05,
        0x06, 0x08, 0x05, 0x06,
        0x08, 0x0a, 0x0a, 0x0c,
    };

    static constexpr inline uint32_t PackagedTextureTexelSizeTable[] = {
        0x08, 0x10, 0x10, 0x08,
        0x10, 0x10, 0x10, 0x08,
        0x10, 0x08, 0x08, 0x08,
        0x10, 0x20, 0x20, 0x20,
        0x20, 0x08, 0x08, 0x10,
        0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10,
        0x10, 0x10, 0x10, 0x10,
        0x10, 0x02
    };

    constexpr inline uint32_t CalculateGfxImageSize(GfxChannelFormat channel_format, uint32_t width, uint32_t height, uint32_t depth) {
        uint32_t format = static_cast<uint32_t>(channel_format);

        /* Adjust width and height for compressed formats */
        uint32_t package_format = format - 0x1a;
        if (package_format < 0x21) {
            uint32_t variable_format = format - 0x27;
            uint32_t block_width     = 4;
            uint32_t block_height    = 4;
            if (variable_format < 0x14) {
                block_width  = VariableBlockWidthTable[variable_format];
                block_height = VariableBlockHeightTable[variable_format];
            }

            width  = (block_width != 0)  ? (width  + block_width  - 1) / block_width  : 0;
            height = (block_height != 0) ? (height + block_height - 1) / block_height : 0;
        }

        /* Find texel size */
        uint32_t texel_size = 0;
        if (package_format < 0x22) {
            texel_size = PackagedTextureTexelSizeTable[package_format];
        } else if (format < 0x3) {
            texel_size = 1;
        } else if (format < 0xb) {
            texel_size = 2;
        } else if (format < 0x15) {
            texel_size = 4;
        } else if (format < 0x18) {
            texel_size = 8;
        } else {
            texel_size = 12;
            if (format != 0x18) {
                texel_size = 16;
            }
        }

        /* Calculate */
        return texel_size * width * height * depth;
    }

    enum class GfxTypeFormat : uint8_t {
        Unorm   = 0x1,
        Snorm   = 0x2,
        UInt    = 0x3,
        SInt    = 0x4,
        Float   = 0x5,
        SRGB    = 0x6,
        Depth   = 0x7, /* (Unorm) */
        UScaled = 0x8,
        SScaled = 0x9,
        UFloat  = 0xa
    };

    #define GFX_MAKE_IMAGE_FORMAT(channel_format, type_format) \
        (((static_cast<uint32_t>(channel_format) & 0xFF) << 8) | (static_cast<uint32_t>(type_format) & 0xFF))

    enum class GfxImageFormat : uint32_t {
        R8_Unorm              = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8,           GfxTypeFormat::Unorm),
        R8_Snorm              = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8,           GfxTypeFormat::Snorm),
        R8_UInt               = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8,           GfxTypeFormat::UInt),
        R8_SInt               = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8,           GfxTypeFormat::SInt),
        R4G4B4A4_Unorm        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R4G4B4A4,     GfxTypeFormat::Unorm),
        R5G5B5A1_Unorm        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R5G5B5A1,     GfxTypeFormat::Unorm),
        A1B5G5R5_Unorm        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::A1B5G5R5,     GfxTypeFormat::Unorm),
        R5G6B5_Unorm          = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R5G6B5,       GfxTypeFormat::Unorm),
        B5G6R5_Unorm          = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::B5G6R5,       GfxTypeFormat::Unorm),
        R8G8_Unorm            = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8,         GfxTypeFormat::Unorm),
        R8G8_Snorm            = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8,         GfxTypeFormat::Snorm),
        R8G8_UInt             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8,         GfxTypeFormat::UInt),
        R8G8_SInt             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8,         GfxTypeFormat::SInt),
        R16_Unorm             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16,          GfxTypeFormat::Unorm),
        R16_Snorm             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16,          GfxTypeFormat::Snorm),
        R16_UInt              = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16,          GfxTypeFormat::UInt),
        R16_SInt              = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16,          GfxTypeFormat::SInt),
        R16_Float             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16,          GfxTypeFormat::Float),
        Z16_Depth             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16,          GfxTypeFormat::Depth),
        R8G8B8A8_Unorm        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8B8A8,     GfxTypeFormat::Unorm),
        R8G8B8A8_Snorm        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8B8A8,     GfxTypeFormat::Snorm),
        R8G8B8A8_UInt         = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8B8A8,     GfxTypeFormat::UInt),
        R8G8B8A8_SInt         = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8B8A8,     GfxTypeFormat::SInt),
        R8G8B8A8_SRGB         = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8B8A8,     GfxTypeFormat::SRGB),
        B8G8R8A8_Unorm        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::B8G8R8A8,     GfxTypeFormat::Unorm),
        B8G8R8A8_SRGB         = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::B8G8R8A8,     GfxTypeFormat::SRGB),
        R9G9B9E5F_SharedFloat = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R9G9B9E5F,    GfxTypeFormat::Float),
        R10G10B10A2_Unorm     = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R10G10B10A2,  GfxTypeFormat::Unorm),
        R10G10B10A2_UInt      = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R10G10B10A2,  GfxTypeFormat::UInt),
        R11G11B10F_Float      = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R11G11B10F,   GfxTypeFormat::Float),
        R16G16_Unorm          = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16,       GfxTypeFormat::Unorm),
        R16G16_Snorm          = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16,       GfxTypeFormat::Snorm),
        R16G16_UInt           = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16,       GfxTypeFormat::UInt),
        R16G16_SInt           = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16,       GfxTypeFormat::SInt),
        R16G16_Float          = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16,       GfxTypeFormat::Float),
        D24S8_Depth           = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::D24S8,        GfxTypeFormat::Depth),
        R32_UInt              = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32,          GfxTypeFormat::UInt),
        R32_SInt              = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32,          GfxTypeFormat::SInt),
        R32_Float             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32,          GfxTypeFormat::Float),
        D32F_Depth            = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32,          GfxTypeFormat::Depth),
        R16G16B16A16_Unorm    = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16B16A16, GfxTypeFormat::Unorm),
        R16G16B16A16_Snorm    = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16B16A16, GfxTypeFormat::Snorm),
        R16G16B16A16_UInt     = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16B16A16, GfxTypeFormat::UInt),
        R16G16B16A16_SInt     = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16B16A16, GfxTypeFormat::SInt),
        R16G16B16A16_Float    = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16B16A16, GfxTypeFormat::Float),
        D32FS8_Depth          = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::D32FS8,       GfxTypeFormat::Depth),
        R32G32_UInt           = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32G32,       GfxTypeFormat::UInt),
        R32G32_SInt           = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32G32,       GfxTypeFormat::SInt),
        R32G32_Float          = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32G32,       GfxTypeFormat::Float),
        R32G32B32_UInt        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32G32B32,    GfxTypeFormat::UInt),
        R32G32B32_SInt        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32G32B32,    GfxTypeFormat::SInt),
        R32G32B32_Float       = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32G32B32,    GfxTypeFormat::Float),
        R32G32B32A32_UInt     = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32G32B32A32, GfxTypeFormat::UInt),
        R32G32B32A32_SInt     = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32G32B32A32, GfxTypeFormat::SInt),
        R32G32B32A32_Float    = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32G32B32A32, GfxTypeFormat::Float),
        BC1_Unorm             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::BC1,          GfxTypeFormat::Unorm),
        BC1_SRGB              = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::BC1,          GfxTypeFormat::SRGB),
        BC2_Unorm             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::BC2,          GfxTypeFormat::Unorm),
        BC2_SRGB              = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::BC2,          GfxTypeFormat::SRGB),
        BC3_Unorm             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::BC3,          GfxTypeFormat::Unorm),
        BC3_SRGB              = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::BC3,          GfxTypeFormat::SRGB),
        BC4_Unorm             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::BC4,          GfxTypeFormat::Unorm),
        BC4_Snorm             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::BC4,          GfxTypeFormat::Snorm),
        BC5_Unorm             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::BC5,          GfxTypeFormat::Unorm),
        BC5_Snorm             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::BC5,          GfxTypeFormat::Snorm),
        BC6H_SF16             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::BC6H,         GfxTypeFormat::Float),
        BC6H_UF16             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::BC6H,         GfxTypeFormat::UFloat),
        BC7U_Unorm            = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::BC7U,         GfxTypeFormat::Unorm),
        BC7U_SRGB             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::BC7U,         GfxTypeFormat::SRGB),
        ASTC_4X4_Unorm        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_4x4,     GfxTypeFormat::Unorm),
        ASTC_4X4_SRGB         = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_4x4,     GfxTypeFormat::SRGB),
        ASTC_5X4_Unorm        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_5x4,     GfxTypeFormat::Unorm),
        ASTC_5X4_SRGB         = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_5x4,     GfxTypeFormat::SRGB),
        ASTC_5X5_Unorm        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_5x5,     GfxTypeFormat::Unorm),
        ASTC_5X5_SRGB         = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_5x5,     GfxTypeFormat::SRGB),
        ASTC_6X5_Unorm        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_6x5,     GfxTypeFormat::Unorm),
        ASTC_6X5_SRGB         = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_6x5,     GfxTypeFormat::SRGB),
        ASTC_6X6_Unorm        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_6x6,     GfxTypeFormat::Unorm),
        ASTC_6X6_SRGB         = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_6x6,     GfxTypeFormat::SRGB),
        ASTC_8X5_Unorm        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_8x5,     GfxTypeFormat::Unorm),
        ASTC_8X5_SRGB         = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_8x5,     GfxTypeFormat::SRGB),
        ASTC_8X6_Unorm        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_8x6,     GfxTypeFormat::Unorm),
        ASTC_8X6_SRGB         = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_8x6,     GfxTypeFormat::SRGB),
        ASTC_8X8_Unorm        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_8x8,     GfxTypeFormat::Unorm),
        ASTC_8X8_SRGB         = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_8x8,     GfxTypeFormat::SRGB),
        ASTC_10X5_Unorm       = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_10x5,    GfxTypeFormat::Unorm),
        ASTC_10X5_SRGB        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_10x5,    GfxTypeFormat::SRGB),
        ASTC_10X6_Unorm       = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_10x6,    GfxTypeFormat::Unorm),
        ASTC_10X6_SRGB        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_10x6,    GfxTypeFormat::SRGB),
        ASTC_10X8_Unorm       = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_10x8,    GfxTypeFormat::Unorm),
        ASTC_10X8_SRGB        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_10x8,    GfxTypeFormat::SRGB),
        ASTC_10X10_Unorm      = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_10x10,   GfxTypeFormat::Unorm),
        ASTC_10X10_SRGB       = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_10x10,   GfxTypeFormat::SRGB),
        ASTC_12X10_Unorm      = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_12x10,   GfxTypeFormat::Unorm),
        ASTC_12X10_SRGB       = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_12x10,   GfxTypeFormat::SRGB),
        ASTC_12X12_Unorm      = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_12x12,   GfxTypeFormat::Unorm),
        ASTC_12X12_SRGB       = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::ASTC_12x12,   GfxTypeFormat::SRGB),
        B5G5R5A1_Unorm        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::B5G5R5A1,     GfxTypeFormat::Unorm)
    };

    enum class GfxAttributeFormat : uint32_t {
        None_Unorm           = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::None,         GfxTypeFormat::Unorm),
        R8_Unorm             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8,           GfxTypeFormat::Unorm),
        R8_Snorm             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8,           GfxTypeFormat::Snorm),
        R8_UInt              = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8,           GfxTypeFormat::UInt),
        R8_SInt              = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8,           GfxTypeFormat::SInt),
        R8_UScaled           = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8,           GfxTypeFormat::UScaled),
        R8_SScaled           = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8,           GfxTypeFormat::SScaled),
        R8G8_Unorm           = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8,         GfxTypeFormat::Unorm),
        R8G8_Snorm           = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8,         GfxTypeFormat::Snorm),
        R8G8_UInt            = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8,         GfxTypeFormat::UInt),
        R8G8_SInt            = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8,         GfxTypeFormat::SInt),
        R8G8_UScaled         = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8,         GfxTypeFormat::UScaled),
        R8G8_SScaled         = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8,         GfxTypeFormat::SScaled),
        R16_Unorm            = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16,          GfxTypeFormat::Unorm),
        R16_Snorm            = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16,          GfxTypeFormat::Snorm),
        R16_UInt             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16,          GfxTypeFormat::UInt),
        R16_SInt             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16,          GfxTypeFormat::SInt),
        R16_Float            = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16,          GfxTypeFormat::Float),
        R16_UScaled          = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16,          GfxTypeFormat::UScaled),
        R16_SScaled          = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16,          GfxTypeFormat::SScaled),
        R8G8B8A8_Unorm       = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8B8A8,     GfxTypeFormat::Unorm),
        R8G8B8A8_Snorm       = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8B8A8,     GfxTypeFormat::Snorm),
        R8G8B8A8_UInt        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8B8A8,     GfxTypeFormat::UInt),
        R8G8B8A8_SInt        = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8B8A8,     GfxTypeFormat::SInt),
        R8G8B8A8_UScaled     = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8B8A8,     GfxTypeFormat::UScaled),
        R8G8B8A8_SScaled     = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R8G8B8A8,     GfxTypeFormat::SScaled),
        R10G10B10A2_Unorm    = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R10G10B10A2,  GfxTypeFormat::Unorm),
        R10G10B10A2_Snorm    = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R10G10B10A2,  GfxTypeFormat::Snorm),
        R10G10B10A2_UInt     = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R10G10B10A2,  GfxTypeFormat::UInt),
        R10G10B10A2_SInt     = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R10G10B10A2,  GfxTypeFormat::SInt),
        R16G16_Unorm         = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16,        GfxTypeFormat::Unorm),
        R16G16_Snorm         = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16,        GfxTypeFormat::Snorm),
        R16G16_UInt          = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16,        GfxTypeFormat::UInt),
        R16G16_SInt          = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16,        GfxTypeFormat::SInt),
        R16G16_Float         = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16,        GfxTypeFormat::Float),
        R16G16_UScaled       = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16,        GfxTypeFormat::UScaled),
        R16G16_SScaled       = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16,        GfxTypeFormat::SScaled),
        R32_UInt             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32,           GfxTypeFormat::UInt),
        R32_SInt             = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32,           GfxTypeFormat::SInt),
        R32_Float            = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32,           GfxTypeFormat::Float),
        R16G16B16A16_Unorm   = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16B16A16,  GfxTypeFormat::Unorm),
        R16G16B16A16_Snorm   = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16B16A16,  GfxTypeFormat::Snorm),
        R16G16B16A16_UInt    = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16B16A16,  GfxTypeFormat::UInt),
        R16G16B16A16_SInt    = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16B16A16,  GfxTypeFormat::SInt),
        R16G16B16A16_Float   = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16B16A16,  GfxTypeFormat::Float),
        R16G16B16A16_UScaled = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16B16A16,  GfxTypeFormat::UScaled),
        R16G16B16A16_SScaled = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R16G16B16A16,  GfxTypeFormat::SScaled),
        R32G32_UInt          = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32G32,        GfxTypeFormat::UInt),
        R32G32_SInt          = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32G32,        GfxTypeFormat::SInt),
        R32G32_Float         = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32G32,        GfxTypeFormat::Float),
        R32G32B32_UInt       = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32G32B32,     GfxTypeFormat::UInt),
        R32G32B32_SInt       = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32G32B32,     GfxTypeFormat::SInt),
        R32G32B32_Float      = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32G32B32,     GfxTypeFormat::Float),
        R32G32B32A32_UInt    = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32G32B32A32,  GfxTypeFormat::UInt),
        R32G32B32A32_SInt    = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32G32B32A32,  GfxTypeFormat::SInt),
        R32G32B32A32_Float   = GFX_MAKE_IMAGE_FORMAT(GfxChannelFormat::R32G32B32A32,  GfxTypeFormat::Float),
    };

    enum class GfxImageStorageDimension : uint8_t { 
        Type1D = 1,
        Type2D = 2,
        Type3D = 3
    };

    struct ResGfxTextureInfo {
        union {
            uint8_t texture_flags;
            struct {
                uint8_t  is_packaged         : 1;
                uint8_t  is_sparse_binding   : 1;
                uint8_t  is_sparse           : 1;
                uint8_t  is_res_texture      : 1;
                uint8_t  reserve0            : 4;
            };
        };
        uint8_t  storage_dimension;
        uint16_t tile_mode;
        uint16_t swizzle;
        uint16_t mip_levels;
        uint16_t sample_count;
        uint16_t reserve1;
        uint32_t image_format;
        uint32_t gpu_access_flags;
        uint32_t width;
        uint32_t height;
        uint32_t depth;
        uint32_t array_layers;
        uint32_t packaged_texture_layout;

        constexpr void SetDefaults() {
            storage_dimension = static_cast<uint8_t>(GfxImageStorageDimension::Type2D);
            tile_mode         = 0;
            swizzle           = 0;
            mip_levels        = 1;
            width             = 1;
            height            = 1;
            depth             = 1;
            sample_count      = 1;
            image_format      = 0;
            gpu_access_flags  = 0;
            array_layers      = 1;
        }
    };
    static_assert(sizeof(ResGfxTextureInfo) == 0x28);

    enum class GfxImageDimension : uint8_t {
        Type1D                  = 0,
        Type2D                  = 1,
        Type3D                  = 2,
        TypeCube                = 3,
        Type1DArray             = 4,
        Type2DArray             = 5,
        Type2DMultisample       = 6,
        Type2DMultisampleArray  = 7,
        TypeCubeArray           = 8,
        TypeRectangle           = 9
    };

    enum class GfxTextureSwizzle : uint8_t {
        Zero = 0,
        One  = 1,
        R    = 2,
        G    = 3,
        B    = 4,
        A    = 5,
    };

    enum class GfxTextureDepthStencilMode : uint8_t {
        Depth   = 0,
        Stencil = 1
    };

    template <typename T>
        requires (sizeof(T*) == sizeof(uint64_t))
    struct ResGfxTextureViewInfo {
        uint8_t   image_dimension;
        uint8_t   depth_stencil_mode;
        uint16_t  reserve0;
        uint32_t  image_format;
        uint8_t   swizzle_x;
        uint8_t   swizzle_y;
        uint8_t   swizzle_z;
        uint8_t   swizzle_w;
        uint32_t  reserve1;
        uint16_t  base_mip_level;
        uint16_t  mip_levels;
        uint32_t  reserve2[3];
        uint32_t  base_array_layer;
        uint32_t  array_layers;
        uint32_t  reserve3[2];
        T   *texture;
    };
    static_assert(sizeof(ResGfxTextureViewInfo<void*>) == 0x38);

    enum class GfxWrapMode : uint8_t {
        Repeat            = 0,
        MirrorRepeat      = 1,
        ClampToEdge       = 2,
        ClampToBorder     = 3,
        MirrorClampToEdge = 4
    };
    
    enum class GfxCompareOperation : uint8_t {
        Never            = 0,
        LessThan         = 1,
        Equal            = 2,
        LessThanEqual    = 3,
        GreaterThan      = 4,
        NotEqual         = 5,
        GreaterThanEqual = 6,
        Always           = 7
    };

    enum class GfxBorderColor : uint8_t {
        White            = 0,
        TransparentBlack = 1,
        Black            = 2,
    };

    enum class GfxMipMapFilter : uint8_t {
        None    = 0,
        Nearest = 1,
        Linear  = 2
    };

    enum class GfxMinFilter : uint8_t {
        Invalid = 0,
        Nearest = 1,
        Linear  = 2
    };

    enum class GfxMagFilter : uint8_t {
        Invalid = 0,
        Nearest = 1,
        Linear  = 2
    };

    enum GfxReductionFilter : uint8_t {
        Average = 0,
        Min     = 1,
        Max     = 2
    };

    struct ResGfxSamplerInfo {
        uint8_t    wrap_mode_u;
        uint8_t    wrap_mode_v;
        uint8_t    wrap_mode_w;
        uint8_t    compare_op;
        uint8_t    border_color;
        uint8_t    max_anisotropy;
        uint16_t   mip_map_filter    : 2;
        uint16_t   mag_filter        : 2;
        uint16_t   min_filter        : 2;
        uint16_t   enable_anisotropy : 1;
        uint16_t   enable_compare_op : 1;
        uint16_t   reduction_filter  : 2;
        uint16_t   reserve0          : 6;
        float lod_clamp_min;
        float lod_clamp_max;
        float lod_bias;
        uint32_t   reserve1;
        uint32_t   reserve2;
        uint32_t   reserve3;
    };
    static_assert(sizeof(ResGfxSamplerInfo) == 0x20);

    enum class GfxPrimitiveTopology {
        Points                 = 0,
        Lines                  = 1,
        LineStrip              = 2,
        Triangles              = 3,
        TrianglesStrip         = 4,
        LinesAdjacency         = 5,
        LineStripAdjacency     = 6,
        TrianglesAdjacency     = 7,
        TriangleStripAdjacency = 8,
        Patches                = 9,
    };

    enum class GfxIndexFormat {
        U8  = 0,
        U16 = 1,
        U32 = 2
    };

    enum class GfxComparisonFunction {
        Never            = 0,
        Less             = 1,
        Equal            = 2,
        LessThanEqual    = 3,
        Greater          = 4,
        NotEqual         = 5,
        GreaterThanEqual = 6,
        Always           = 7
    };

    enum class GfxStencilOperation {
        Keep          = 0,
        Zero          = 1,
        Replace       = 2,
        Increment     = 3,
        Decrement     = 4,
        Invert        = 5,
        IncrementWrap = 6,
        DecrementWrap = 7
    };

    enum class GfxBlendFactor : uint8_t {
        Zero                     = 0,
        One                      = 1,
        SourceColor              = 2,
        SourceColorMinusOne      = 3,
        DestinationColor         = 4,
        DestinationColorMinusOne = 5,
        SourceAlpha              = 6,
        SourceAlphaMinusOne      = 7,
        DestinationAlpha         = 8,
        DestinationAlphaMinusOne = 9,
        ConstantColor            = 10,
        ConstantColorMinusOne    = 11,
        ConstantAlpha            = 12,
        ConstantAlphaMinusOne    = 13,
        SourceAlphaSaturate      = 14,
        SourceOneColor           = 15,
        SourceOneColorMinusOne   = 16,
        SourceOneAlpha           = 17,
        SourceOneAlphaMinusOne   = 18
    };

    enum class GfxBlendEquation : uint8_t {
        Add        = 0,
        Sub        = 1,
        ReverseSub = 2,
        Min        = 3,
        Max        = 4
    };

    enum class GfxLogicOperation : uint8_t {
        Clear        = 0,
        And          = 1,
        AndReverse   = 2,
        Copy         = 3,
        AndInverted  = 4,
        NoOp         = 5,
        Xor          = 6,
        Or           = 7,
        Nor          = 8,
        Equivalent   = 9,
        Invert       = 10,
        OrReverse    = 11,
        CopyInverted = 12,
        OrInverted   = 13,
        Nand         = 14,
        Set          = 15
    };

    enum class GfxCullMode : uint8_t {
        None         = 0x0,
        Front        = 0x1,
        Back         = 0x2,
    };

    enum class GfxFillMode : uint8_t {
        Point = 0,
        Line  = 1,
        Fill  = 2,
    };
    
    enum class GfxFrontFace : uint8_t {
        CounterClockWise = 0x0,
        ClockWise        = 0x1,
    };

    struct ResGfxEmbedFile {
        void *file_offset;
        uint32_t   file_size;
        uint32_t   reserve0;
    };
    static_assert(sizeof(ResGfxEmbedFile) == 0x10);

    enum class GfxUserDataType : uint8_t {
        S32    = 0,
        Float  = 1,
        String = 2,
        Byte   = 3
    };

    struct ResGfxUserData {
        const char *user_data_name;
        void       *user_data;
        int32_t       data_entries;
        uint8_t          data_type;
        uint8_t          reserve0[0x2b];
    };
    static_assert(sizeof(ResGfxUserData) == 0x40);
}

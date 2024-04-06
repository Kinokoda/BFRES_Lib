#include "BFRES.h"

#include <iostream>

namespace BFRES
{
    class bfresFile
    {
        public:
            std::string Magic;
            uint32_t Signature;
            uint32_t Version;
            uint16_t Endianess;
            std::byte ByteAlignment;
            std::byte TargetAddressSize;
            uint32_t FileNameOffset;
            uint16_t FLags;
            uint16_t BlockOffset;
            uint32_t RelocationTableOffset;
            uint32_t BFRES_Size;
            uint64_t OffsetToFileName;
            uint64_t FMDL_Offset;
            uint64_t FMDL_DictionaryOffset;
    };
}
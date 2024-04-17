#pragma once

#include <cstdint>

namespace vp::res {

    struct ResNintendoWareRelocationTable;

    struct ResNintendoWareSubHeader {
        uint32_t magic;
        uint32_t next_block_offset;
        uint32_t block_size;
        uint32_t reserve;
        
        inline ResNintendoWareSubHeader *GetNextBlock() {
            return (this->next_block_offset == 0) ? nullptr : reinterpret_cast<ResNintendoWareSubHeader*>(reinterpret_cast<uintptr_t>(this) + this->next_block_offset);
        }
    };
    static_assert(sizeof(ResNintendoWareSubHeader) == 0x10);

    struct ResNintendoWareFileHeader {
        uint64_t magic;
        uint8_t  micro_version;
        uint8_t  minor_version;
        uint16_t major_version;
        uint16_t endianess;
        uint8_t  packed_alignment;
        uint8_t  address_size;
        uint32_t file_name_offset;
        uint16_t is_relocated;
        uint16_t first_block_offset;
        uint32_t relocation_table_offset;
        uint32_t file_size;

        static constexpr uint64_t BigEndianByteMark    = 0xFFFE;
        static constexpr uint64_t LittleEndianByteMark = 0xFEFF;

        [[nodiscard]] inline bool IsAlignmentValid()                                   const { return (((1ull << (this->packed_alignment & 63)) - 1) & reinterpret_cast<uint64_t>(this)) == 0; }
        [[nodiscard]] constexpr inline bool IsEndianReverse()                                    const { return this->endianess == BigEndianByteMark; }
        [[nodiscard]] constexpr inline bool IsEndianValid()                                      const { return this->endianess == LittleEndianByteMark; }
        [[nodiscard]] constexpr inline bool IsRelocated()                                        const { return this->is_relocated & 1; }
        [[nodiscard]] constexpr inline bool IsSignatureValid(uint64_t magic)                          const { return this->magic == magic; }
        [[nodiscard]] constexpr inline bool IsVersionValid(int32_t major_version, int32_t minor_version) const { return this->major_version == major_version && this->minor_version <= minor_version; }

        inline bool IsValid(uint64_t magic, int32_t major_version, int32_t minor_version, [[maybe_unused]] int32_t micro_version = 0) const {
            return this->IsVersionValid(major_version, minor_version) && this->IsSignatureValid(magic) && this->IsEndianValid() && this->IsAlignmentValid();
        }

        inline ResNintendoWareSubHeader *GetFirstBlock() {
            return (this->first_block_offset == 0) ? nullptr : reinterpret_cast<ResNintendoWareSubHeader*>(reinterpret_cast<uintptr_t>(this) + this->first_block_offset);
        }

        inline ResNintendoWareRelocationTable *GetRelocationTable() {
            return (this->relocation_table_offset == 0) ? nullptr : reinterpret_cast<ResNintendoWareRelocationTable*>(reinterpret_cast<uintptr_t>(this) + this->relocation_table_offset); 
        }

        inline void SetRelocated(bool is_relocated) { this->is_relocated = (this->is_relocated & 0xFFFE) | is_relocated; }

        inline void Relocate() {
            ResNintendoWareRelocationTable *relocation_table = this->GetRelocationTable();
            if (relocation_table != nullptr) {
                relocation_table -> Relocate();
            }
        }
    };
    static_assert(sizeof(ResNintendoWareFileHeader) == 0x20);
}

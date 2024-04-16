#pragma once

namespace vp::res {

    struct ResNintendoWareRelocationTable;

    struct ResNintendoWareSubHeader {
        u32 magic;
        u32 next_block_offset;
        u32 block_size;
        u32 reserve;
        
        ALWAYS_INLINE ResNintendoWareSubHeader *GetNextBlock() {
            return (this->next_block_offset == 0) ? nullptr : reinterpret_cast<ResNintendoWareSubHeader*>(reinterpret_cast<uintptr_t>(this) + this->next_block_offset);
        }
    };
    static_assert(sizeof(ResNintendoWareSubHeader) == 0x10);

    struct ResNintendoWareFileHeader {
        u64 magic;
        u8  micro_version;
        u8  minor_version;
        u16 major_version;
        u16 endianess;
        u8  packed_alignment;
        u8  address_size;
        u32 file_name_offset;
        u16 is_relocated;
        u16 first_block_offset;
        u32 relocation_table_offset;
        u32 file_size;

        static constexpr u64 BigEndianByteMark    = 0xFFFE;
        static constexpr u64 LittleEndianByteMark = 0xFEFF;

        ALWAYS_INLINE           bool IsAlignmentValid()                                   const { return (((1ull << (this->packed_alignment & 63)) - 1) & reinterpret_cast<u64>(this)) == 0; }
        constexpr ALWAYS_INLINE bool IsEndianReverse()                                    const { return this->endianess == BigEndianByteMark; }
        constexpr ALWAYS_INLINE bool IsEndianValid()                                      const { return this->endianess == LittleEndianByteMark; }
        constexpr ALWAYS_INLINE bool IsRelocated()                                        const { return this->is_relocated & 1; }
        constexpr ALWAYS_INLINE bool IsSignatureValid(u64 magic)                          const { return this->magic == magic; }
        constexpr ALWAYS_INLINE bool IsVersionValid(s32 major_version, s32 minor_version) const { return this->major_version == major_version && this->minor_version <= minor_version; }

        ALWAYS_INLINE bool IsValid(u64 magic, s32 major_version, s32 minor_version, [[maybe_unused]] s32 micro_version = 0) const {
            return this->IsVersionValid(major_version, minor_version) && this->IsSignatureValid(magic) && this->IsEndianValid() && this->IsAlignmentValid();
        }

        ALWAYS_INLINE ResNintendoWareSubHeader *GetFirstBlock() {
            return (this->first_block_offset == 0) ? nullptr : reinterpret_cast<ResNintendoWareSubHeader*>(reinterpret_cast<uintptr_t>(this) + this->first_block_offset);
        }

        ALWAYS_INLINE ResNintendoWareRelocationTable *GetRelocationTable() {
            return (this->relocation_table_offset == 0) ? nullptr : reinterpret_cast<ResNintendoWareRelocationTable*>(reinterpret_cast<uintptr_t>(this) + this->relocation_table_offset); 
        }

        ALWAYS_INLINE void SetRelocated(bool is_relocated) { this->is_relocated = (this->is_relocated & 0xFFFE) | is_relocated; }

        ALWAYS_INLINE void Relocate() {
            ResNintendoWareRelocationTable *relocation_table = this->GetRelocationTable();
            if (relocation_table != nullptr) {
                relocation_table->Relocate();
            }
        }
    };
    static_assert(sizeof(ResNintendoWareFileHeader) == 0x20);
}

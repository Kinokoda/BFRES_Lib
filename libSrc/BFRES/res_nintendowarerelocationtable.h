#pragma once



namespace vp::res {

    struct ResNintendoWareFileHeader;

	struct ResNintendoWareRelocationTable {
        uint32_t magic;
        uint32_t this_table_offset;
        uint32_t section_count;
        uint32_t reserve0;
        
        static constexpr uint32_t Magic = 0x5F524C54;

        struct ResSection {
            void *base_pointer;
            uint32_t   region_offset;
            uint32_t   region_size;
            uint32_t   base_entry_index;
            uint32_t   entry_count;
        };
        static_assert(sizeof(ResSection) == 0x18);

        struct ResEntry {
            uint32_t region_offset;
            uint16_t array_count;
            uint8_t  relocation_count;
            uint8_t  array_stride;
        };
        static_assert(sizeof(ResEntry) == 0x8);
        
        static uint64_t CalculateTableSize(int32_t sections, int32_t entries) { 
            return sections * sizeof(ResSection) + entries * sizeof(ResEntry) + sizeof(ResNintendoWareRelocationTable); 
        }

        inline uint64_t GetEntryTableOffset() {
            return sizeof(ResNintendoWareRelocationTable) + section_count * sizeof(ResSection);
        }

        ResNintendoWareFileHeader *GetFileHeader();

        ResSection *GetSection(int32_t section_index) { 
            return reinterpret_cast<ResSection*>(reinterpret_cast<uintptr_t>(this) + sizeof(ResNintendoWareRelocationTable) + section_index * sizeof(ResSection)); 
        }

        [[nodiscard]] const ResSection *GetSection(int32_t section_index) const {
            return reinterpret_cast<const ResSection*>(reinterpret_cast<uintptr_t>(this) + sizeof(ResNintendoWareRelocationTable) + section_index * sizeof(ResSection)); 
        }

        void SetSignature() { magic = Magic; }

        void Relocate();
        void Unrelocate();
	};
}

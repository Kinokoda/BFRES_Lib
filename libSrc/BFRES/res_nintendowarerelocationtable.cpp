//#include <vp.hpp>
#include <cstdint>
#include <cstdio>
#include "res_nintendowarerelocationtable.h"

namespace vp::res {

    ResNintendoWareFileHeader *ResNintendoWareRelocationTable::GetFileHeader() {
        return reinterpret_cast<ResNintendoWareFileHeader*>(reinterpret_cast<uintptr_t>(this) - this_table_offset);
    }

    void ResNintendoWareRelocationTable::Relocate() {

        ResNintendoWareFileHeader *file_header = GetFileHeader();

        /* No sections is valid */
        if (section_count == 0) {
            file_header->SetRelocated(true);
            return;
        }

        const uintptr_t base_file = reinterpret_cast<uintptr_t>(file_header);

        const size_t entry_table_offset = this->GetEntryTableOffset();

        /* Iterate each section */
        for(uint32_t i = 0; i < section_count; ++i) {

            /* Get section and calculate file base */
            ResSection *section = this->GetSection(i);
            uintptr_t file_base = (section->base_pointer == nullptr) ? base_file : reinterpret_cast<uintptr_t>(section->base_pointer) - section->region_offset;

            /* Relocate entries */
            uint32_t entry_count = section->entry_count;
            for(uint32_t entry_index = section->base_entry_index; entry_index < entry_count + section->base_entry_index; ++entry_index) {

                /* Calculate entry offset */
                const size_t entry_offset = entry_table_offset + entry_index * sizeof(ResEntry);
                ResEntry *entry = reinterpret_cast<ResEntry*>(reinterpret_cast<uintptr_t>(this) + entry_offset);

                /* Calculate relocation offset */
                uintptr_t region_offset = base_file + entry->region_offset;

                /* Relocate */
                const uint8_t offset_count = entry->relocation_count;
                const uint8_t offset_mask = offset_count & 3;
                for(uint32_t array_index = 0; array_index < entry->array_count; ++array_index) {

                    /* Quadruple method */
                    uintptr_t region_offset_iter = region_offset;
                    if (3 < offset_count) {
                        for(int32_t offset_index = offset_mask - offset_count; offset_index < 0; offset_index = offset_index + 4) {

                            /* Calculate and set pointer in file (x4) */
                            size_t relocation_pointer = (region_offset_iter != 0) ? reinterpret_cast<size_t>(file_base + region_offset_iter) : 0;
                            *reinterpret_cast<size_t*>(region_offset_iter) = relocation_pointer;
                            region_offset_iter = region_offset_iter + sizeof(size_t);

                            relocation_pointer = (region_offset_iter != 0) ? reinterpret_cast<size_t>(file_base + region_offset_iter) : 0;
                            *reinterpret_cast<size_t*>(region_offset_iter) = relocation_pointer;
                            region_offset_iter = region_offset_iter + sizeof(size_t);

                            relocation_pointer = (region_offset_iter != 0) ? reinterpret_cast<size_t>(file_base + region_offset_iter) : 0;
                            *reinterpret_cast<size_t*>(region_offset_iter) = relocation_pointer;
                            region_offset_iter = region_offset_iter + sizeof(size_t);

                            relocation_pointer = (region_offset_iter != 0) ? reinterpret_cast<size_t>(file_base + region_offset_iter) : 0;
                            *reinterpret_cast<size_t*>(region_offset_iter) = relocation_pointer;
                            region_offset_iter = region_offset_iter + sizeof(size_t);
                        }
                    }
                    if (offset_mask != 0) {
                        for(int32_t offset_index = -offset_mask; offset_index < 0; ++offset_index) {

                            /* Calculate and set pointer in file */
                            size_t relocation_pointer = (region_offset_iter != 0) ? reinterpret_cast<size_t>(file_base + region_offset_iter) : 0;
                            *reinterpret_cast<size_t*>(region_offset_iter) = relocation_pointer;
                            region_offset_iter = region_offset_iter + sizeof(size_t);
                        }
                    }

                    /* Calculate next array's region offset */
                    region_offset = region_offset + offset_count * sizeof(size_t) + entry->array_stride * sizeof(size_t);
                }
            }
        }

        /* Set relocation guard */
        file_header->SetRelocated(true);

        return;
    }

    void ResNintendoWareRelocationTable::Unrelocate() {

        ResNintendoWareFileHeader *file_header = GetFileHeader();

        /* No sections is valid */
        if (section_count == 0) {
            file_header->SetRelocated(true);
            return;
        }

        const uintptr_t base_file = reinterpret_cast<uintptr_t>(file_header);

        const size_t entry_table_offset = this->GetEntryTableOffset();

        /* Iterate each section */
        for(uint32_t i = 0; i < section_count; ++i) {

            /* Get section and calculate file base */
            ResSection *section = this->GetSection(i);
            uintptr_t file_base = (section->base_pointer == nullptr) ? base_file : reinterpret_cast<uintptr_t>(section->base_pointer) - section->region_offset;

            /* Relocate entries */
            uint32_t entry_count = section->entry_count;
            for(uint32_t entry_index = section->base_entry_index; entry_index < entry_count + section->base_entry_index; ++entry_index) {

                /* Calculate entry offset */
                const size_t entry_offset = entry_table_offset + entry_index * sizeof(ResEntry);
                ResEntry *entry = reinterpret_cast<ResEntry*>(reinterpret_cast<uintptr_t>(this) + entry_offset);

                /* Calculate relocation offset */
                uintptr_t region_offset = base_file + entry->region_offset;

                /* Relocate */
                const uint8_t offset_count = entry->relocation_count;
                const uint8_t offset_mask = offset_count & 3;
                for(uint32_t array_index = 0; array_index < entry->array_count; ++array_index) {

                    /* Quadruple method */
                    uintptr_t region_offset_iter = region_offset;
                    if (3 < offset_count) {
                        for(int32_t offset_index = offset_mask - offset_count; offset_index < 0; offset_index = offset_index + 4) {

                            /* Calculate and set pointer in file (x4) */
                            size_t relocation_pointer = (region_offset_iter != 0) ? reinterpret_cast<size_t>(region_offset_iter - file_base) : 0;
                            *reinterpret_cast<size_t*>(region_offset_iter) = relocation_pointer;
                            region_offset_iter = region_offset_iter + sizeof(size_t);

                            relocation_pointer = (region_offset_iter != 0) ? reinterpret_cast<size_t>(region_offset_iter - file_base) : 0;
                            *reinterpret_cast<size_t*>(region_offset_iter) = relocation_pointer;
                            region_offset_iter = region_offset_iter + sizeof(size_t);

                            relocation_pointer = (region_offset_iter != 0) ? reinterpret_cast<size_t>(region_offset_iter - file_base) : 0;
                            *reinterpret_cast<size_t*>(region_offset_iter) = relocation_pointer;
                            region_offset_iter = region_offset_iter + sizeof(size_t);

                            relocation_pointer = (region_offset_iter != 0) ? reinterpret_cast<size_t>(region_offset_iter - file_base) : 0;
                            *reinterpret_cast<size_t*>(region_offset_iter) = relocation_pointer;
                            region_offset_iter = region_offset_iter + sizeof(size_t);
                        }
                    }
                    if (offset_mask != 0) {
                        for(int32_t offset_index = -offset_mask; offset_index < 0; ++offset_index) {

                            /* Calculate and set pointer in file */
                            size_t relocation_pointer = (region_offset_iter != 0) ? reinterpret_cast<size_t>(region_offset_iter - file_base) : 0;
                            *reinterpret_cast<size_t*>(region_offset_iter) = relocation_pointer;
                            region_offset_iter = region_offset_iter + sizeof(size_t);
                        }
                    }

                    /* Calculate next array's region offset */
                    region_offset = region_offset + (offset_count << 3) + (entry->array_stride << 3);
                }
            }
        }

        /* Clear relocation guard */
        file_header -> SetRelocated(false);

        return;
    }
}

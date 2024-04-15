//
// Created by kino on 4/13/24.
//

#include "Header.h"

bool Header::isEndianess() const {
    return endianess;
}

uint32_t Header::getSignature() const {
    return signature;
}

std::byte Header::getAlignment() const {
    return alignment;
}

std::byte Header::getTargetAddressSize() const {
    return target_address_size;
}

uint32_t Header::getFilenameOffset() const {
    return filename_offset;
}

uint16_t Header::getFlags() const {
    return flags;
}

uint16_t Header::getBlockOffset() const {
    return block_offset;
}

uint32_t Header::getRelocationTableOffset() const {
    return relocation_table_offset;
}

uint32_t Header::getBfresSize() const {
    return bfres_size;
}

uint64_t Header::getFilenameLengthOffset() const {
    return filename_length_offset;
}

uint64_t Header::getFmdlOffset() const {
    return fmdl_offset;
}

uint64_t Header::getFmdlDictionaryOffset() const {
    return fmdl_dictionary_offset;
}

Header::Header(const char *data){
    endianess = UintReader::readUint16(data, 0xC, true) == 0xFEFF;
    signature = UintReader::readUint32(data, 0x04, endianess);
    alignment = (std::byte) data[0x0E];
    target_address_size = (std::byte) data[0x0F];
    filename_offset = UintReader::readUint32(data, 0x10, endianess);
    flags = UintReader::readUint16(data, 0x14, endianess);
    block_offset = UintReader::readUint16(data, 0x16, endianess);
    relocation_table_offset = UintReader::readUint32(data, 0x18, endianess);
    bfres_size = UintReader::readUint32(data, 0x1C, endianess);
    filename_length_offset = UintReader::readUint64(data, 0x20, endianess);
    fmdl_offset = UintReader::readUint64(data, 0x28, endianess);
    fmdl_dictionary_offset = UintReader::readUint64(data, 0x30, endianess);
}

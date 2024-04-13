//
// Created by kino on 4/13/24.
//

#include <cstdint>
#include "Header.h"

Header::Header(std::byte *data) {
    
}

const std::string &Header::getMagic() const {
    return Magic;
}

const std::uint32_t &Header::getSignature() const {
    return signature;
}

const std::uint32_t &Header::getVersion() const {
    return version;
}

const std::uint16_t &Header::getBom() const {
    return bom;
}

std::byte Header::getAlignment() const {
    return alignment;
}

std::byte Header::getTargetAddressSize() const {
    return target_address_size;
}

const std::uint32_t &Header::getFilenameOffset() const {
    return filename_offset;
}

const std::uint16_t &Header::getFlags() const {
    return flags;
}

const std::uint16_t &Header::getBlockOffset() const {
    return block_offset;
}

const std::uint32_t &Header::getRelocationTableOffset() const {
    return relocation_table_offset;
}

const std::uint32_t &Header::getBfresSize() const {
    return bfres_size;
}

const std::uint64_t &Header::getFilenameLengthOffset() const {
    return filename_length_offset;
}

const std::uint64_t &Header::getFmdlOffset() const {
    return fmdl_offset;
}

const std::uint64_t &Header::getFmdlDictionaryOffset() const {
    return fmdl_dictionary_offset;
}

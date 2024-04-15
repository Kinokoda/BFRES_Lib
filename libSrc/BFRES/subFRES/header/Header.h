//
// Created by kino on 4/13/24.
//

#ifndef BFRES_LIB_HEADER_H
#define BFRES_LIB_HEADER_H


#include <cstdint>
#include <cstddef>
#include <string>
#include <iostream>
#include "../../../usefulFunctions/UintReader.h"


class Header{
public:
    explicit Header(const char *data);

    [[nodiscard]] bool isEndianess() const;

    [[nodiscard]] uint32_t getSignature() const;

    [[nodiscard]] std::byte getAlignment() const;

    [[nodiscard]] std::byte getTargetAddressSize() const;

    [[nodiscard]] uint32_t getFilenameOffset() const;

    [[nodiscard]] uint16_t getFlags() const;

    [[nodiscard]] uint16_t getBlockOffset() const;

    [[nodiscard]] uint32_t getRelocationTableOffset() const;

    [[nodiscard]] uint32_t getBfresSize() const;

    [[nodiscard]] uint64_t getFilenameLengthOffset() const;

    [[nodiscard]] uint64_t getFmdlOffset() const;

    [[nodiscard]] uint64_t getFmdlDictionaryOffset() const;

private:
    const std::string Magic = "FRES";
    std::uint32_t signature;
    bool endianess;
    std::byte alignment;
    std::byte target_address_size;
    std::uint32_t filename_offset;
    std::uint16_t flags;
    std::uint16_t block_offset;
    std::uint32_t relocation_table_offset;
    std::uint32_t bfres_size;
    std::uint64_t filename_length_offset;
    std::uint64_t fmdl_offset;
    std::uint64_t fmdl_dictionary_offset;
};


#endif //BFRES_LIB_HEADER_H

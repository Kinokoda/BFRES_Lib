//
// Created by kino on 4/13/24.
//

#ifndef BFRES_LIB_HEADER_H
#define BFRES_LIB_HEADER_H


#include <cstdint>
#include <cstddef>
#include <string>


class Header {
    const std::string Magic = "FRES";
    std::uint32_t signature;
    std::uint32_t version;
    std::uint16_t bom;
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

    public:
        Header(std::byte* data);

    [[nodiscard]] const std::string &getMagic() const;

    [[nodiscard]] const std::uint32_t &getSignature() const;

    [[nodiscard]] const std::uint32_t &getVersion() const;

    [[nodiscard]] const std::uint16_t &getBom() const;

    [[nodiscard]] std::byte getAlignment() const;

    [[nodiscard]] std::byte getTargetAddressSize() const;

    [[nodiscard]] const std::uint32_t &getFilenameOffset() const;

    [[nodiscard]] const std::uint16_t &getFlags() const;

    [[nodiscard]] const std::uint16_t &getBlockOffset() const;

    [[nodiscard]] const std::uint32_t &getRelocationTableOffset() const;

    [[nodiscard]] const std::uint32_t &getBfresSize() const;

    [[nodiscard]] const std::uint64_t &getFilenameLengthOffset() const;

    [[nodiscard]] const std::uint64_t &getFmdlOffset() const;

    [[nodiscard]] const std::uint64_t &getFmdlDictionaryOffset() const;
};


#endif //BFRES_LIB_HEADER_H

//
// Created by kino on 4/14/24.
//

#ifndef BFRES_LIB_UINTREADER_H
#define BFRES_LIB_UINTREADER_H


#include <cstdint>
#include <cstddef>

class UintReader {
public:
    static uint16_t readUint16(const char *data, uint64_t offset, bool endianess = false);
    static uint32_t readUint32(const char *data, uint64_t offset, bool endianess = false);
    static uint64_t readUint64(const char *data, uint64_t offset, bool endianess = false);
};


#endif //BFRES_LIB_UINTREADER_H

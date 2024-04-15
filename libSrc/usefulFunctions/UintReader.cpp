//
// Created by kino on 4/14/24.
//

#include "UintReader.h"
uint16_t UintReader::readUint16(const char *data, uint64_t offset, bool endianess /*false for little endian, true for big endian*/){

    //false for little endian, true for big endian

    if(!endianess){
        return static_cast<uint8_t>(data[offset + 1]) << 8 | static_cast<uint8_t>(data[offset]);
    }
    else{
        return static_cast<uint8_t>(data[offset]) << 8 | static_cast<uint8_t>(data[offset + 1]);
    }
    //return static_cast<uint16_t>(data[offset + 1]);
};

uint32_t UintReader::readUint32(const char *data, uint64_t offset, bool endianess /*false for little endian, true for big endian*/){
    if (!endianess){

        uint32_t part2 = readUint16(data, offset + 2, endianess) << 16;
        uint32_t part1 = readUint16(data, offset, endianess);
        return part1 | part2;
    }
    else{
        uint32_t part1 = readUint16(data, offset, endianess) << 16;
        uint32_t part2 = readUint16(data, offset + 2, endianess);
        return part1 | part2;

    }
};

uint64_t UintReader::readUint64(const char * data, uint64_t offset, bool endianess /*false for little endian, true for big endian*/){
    if (!endianess){
        auto part2 = readUint32(data, (offset + 4), endianess);
        auto part1 = readUint32(data, offset, endianess);
        return ((uint64_t) part2 << 32) | part1;
    }
    else{
        uint64_t part1 = readUint32(data, offset, endianess);
        uint64_t part2 = readUint32(data, offset + 4, endianess);
        return (part1 << 32) | part2;
    }
};
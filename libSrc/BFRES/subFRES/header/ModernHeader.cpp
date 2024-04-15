//
// Created by kino on 4/15/24.
//

#include "ModernHeader.h"
#include "../../../usefulFunctions/UintReader.h"

ModernHeader::ModernHeader(const char * data, bool endianess) {
    UnknownOffset = UintReader::readUint64(data, 0x38, endianess);
    UnknownDictionaryOffset = UintReader::readUint64(data, 0x40, endianess);
    Unknown_2_Offset = UintReader::readUint64(data, 0x48, endianess);
    Unknown_2_DictionaryOffset = UintReader::readUint64(data, 0x50, endianess);
    SkeletalAnimationsOffset = UintReader::readUint64(data, 0x58, endianess);
    SkeletalAnimationsDictionary = UintReader::readUint64(data, 0x60, endianess);
    MaterialsAnimationsOffset = UintReader::readUint64(data, 0x68, endianess);
    MaterialAnimationsDictionary = UintReader::readUint64(data, 0x70, endianess);
    BoneVisibilityAnimationArrayOffset = UintReader::readUint64(data, 0x78, endianess);
    BoneVisibilityAnimationArrayDictionary = UintReader::readUint64(data, 0x80, endianess);
    ShapeAnimationArrayOffset = UintReader::readUint64(data, 0x88, endianess);
    ShapeAnimationArrayDictionaryOffset = UintReader::readUint64(data, 0x90, endianess);
    SceneAnimationArrayOffset = UintReader::readUint64(data, 0x98, endianess);
    SceneAnimationArrayDictionaryOffset = UintReader::readUint64(data, 0xA0, endianess);
    MemoryPool = UintReader::readUint64(data, 0xA8, endianess);
    BufferSection = UintReader::readUint64(data, 0xB0, endianess);
    EmbeddedFilesOffset = UintReader::readUint64(data, 0xB8, endianess);
    EmbeddedFileDictionaryOffset = UintReader::readUint64(data, 0xC0, endianess);
    StringTableOffset = UintReader::readUint64(data, 0xD0, endianess);
    StringTableSize = UintReader::readUint32(data, 0xD8, endianess);
    ModelCount = UintReader::readUint16(data, 0xDC, endianess);
    UnknownCount = UintReader::readUint16(data, 0xDE, endianess);
    Unknown2Count = UintReader::readUint16(data, 0xE0, endianess);
    SkeletalAnimationCount = UintReader::readUint16(data, 0xE2, endianess);
    MaterialAnimationCount = UintReader::readUint16(data, 0xE4, endianess);
    BoneVisualAnimationCount = UintReader::readUint16(data, 0xE6, endianess);
    ShapeAnimationCount = UintReader::readUint16(data, 0xE8, endianess);
    SceneAnimationCount = UintReader::readUint16(data, 0xEA, endianess);
    ExternalFileCount = UintReader::readUint16(data, 0xEC, endianess);
}

uint64_t ModernHeader::getUnknownOffset() const {
    return UnknownOffset;
}

uint64_t ModernHeader::getUnknownDictionaryOffset() const {
    return UnknownDictionaryOffset;
}

uint64_t ModernHeader::getUnknown2Offset() const {
    return Unknown_2_Offset;
}

uint64_t ModernHeader::getUnknown2DictionaryOffset() const {
    return Unknown_2_DictionaryOffset;
}

uint64_t ModernHeader::getSkeletalAnimationsOffset() const {
    return SkeletalAnimationsOffset;
}

uint64_t ModernHeader::getSkeletalAnimationsDictionary() const {
    return SkeletalAnimationsDictionary;
}

uint64_t ModernHeader::getMaterialsAnimationsOffset() const {
    return MaterialsAnimationsOffset;
}

uint64_t ModernHeader::getMaterialAnimationsDictionary() const {
    return MaterialAnimationsDictionary;
}

uint64_t ModernHeader::getBoneVisibilityAnimationArrayOffset() const {
    return BoneVisibilityAnimationArrayOffset;
}

uint64_t ModernHeader::getBoneVisibilityAnimationArrayDictionary() const {
    return BoneVisibilityAnimationArrayDictionary;
}

uint64_t ModernHeader::getShapeAnimationArrayOffset() const {
    return ShapeAnimationArrayOffset;
}

uint64_t ModernHeader::getShapeAnimationArrayDictionaryOffset() const {
    return ShapeAnimationArrayDictionaryOffset;
}

uint64_t ModernHeader::getSceneAnimationArrayOffset() const {
    return SceneAnimationArrayOffset;
}

uint64_t ModernHeader::getSceneAnimationArrayDictionaryOffset() const {
    return SceneAnimationArrayDictionaryOffset;
}

uint64_t ModernHeader::getMemoryPool() const {
    return MemoryPool;
}

uint64_t ModernHeader::getBufferSection() const {
    return BufferSection;
}

uint64_t ModernHeader::getEmbeddedFilesOffset() const {
    return EmbeddedFilesOffset;
}

uint64_t ModernHeader::getEmbeddedFileDictionaryOffset() const {
    return EmbeddedFileDictionaryOffset;
}

uint64_t ModernHeader::getStringTableOffset() const {
    return StringTableOffset;
}

uint32_t ModernHeader::getStringTableSize() const {
    return StringTableSize;
}

uint16_t ModernHeader::getModelCount() const {
    return ModelCount;
}

uint16_t ModernHeader::getUnknownCount() const {
    return UnknownCount;
}

uint16_t ModernHeader::getUnknown2Count() const {
    return Unknown2Count;
}

uint16_t ModernHeader::getSkeletalAnimationCount() const {
    return SkeletalAnimationCount;
}

uint16_t ModernHeader::getMaterialAnimationCount() const {
    return MaterialAnimationCount;
}

uint16_t ModernHeader::getBoneVisualAnimationCount() const {
    return BoneVisualAnimationCount;
}

uint16_t ModernHeader::getShapeAnimationCount() const {
    return ShapeAnimationCount;
}

uint16_t ModernHeader::getSceneAnimationCount() const {
    return SceneAnimationCount;
}

uint16_t ModernHeader::getExternalFileCount() const {
    return ExternalFileCount;
}

int ModernHeader::getEndOfHeaderOffset() const {
    return EndOfHeaderOffset;
}

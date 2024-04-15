//
// Created by kino on 4/15/24.
//

#include "LegacyHeader.h"

LegacyHeader::LegacyHeader(const char * data) {
    SkeletalAnimationsOffset = UintReader::readUint64(data, 0x38);
    SkeletalAnimationsDictionary = UintReader::readUint64(data, 0x40);
    MaterialAnimationsOffset = UintReader::readUint64(data, 0x48);
    MaterialAnimationsDictionary = UintReader::readUint64(data, 0x50);
    BoneVisibilityAnimationArrayOffset = UintReader::readUint64(data, 0x58);
    BoneVisibilityAnimationArrayDictionary = UintReader::readUint64(data, 0x60);
    ShapeAnimationArrayOffset = UintReader::readUint64(data, 0x68);
    ShapeAnimationDictionaryOffset = UintReader::readUint64(data, 0x70);
    SceneAnimationArrayOffset = UintReader::readUint64(data, 0x78);
    SceneAnimationDictionaryOffset = UintReader::readUint64(data, 0x80);
    MemoryPool = UintReader::readUint64(data, 0x88);
    BufferSection = UintReader::readUint64(data, 0x90);
    EmbeddedFilesOffset = UintReader::readUint64(data, 0x98);
    EmbeddedFileDictionaryOffset = UintReader::readUint64(data, 0xA0);
    StringTableOffset = UintReader::readUint64(data, 0xB0);
    StringTableSize = UintReader::readUint32(data, 0xB8);
    ModelCount = UintReader::readUint16(data, 0xBC);
    SkeletalAnimationCount = UintReader::readUint16(data, 0xBE);
    MaterialAnimationCount = UintReader::readUint16(data, 0xC0);
    BoneVisualAnimationCount = UintReader::readUint16(data, 0xC2);
    ShapeAnimationCount = UintReader::readUint16(data, 0xC4);
    SceneAnimationCount = UintReader::readUint16(data, 0xC6);
    ExternalFileCount = UintReader::readUint16(data, 0xC8);
}

uint64_t LegacyHeader::getSkeletalAnimationsOffset() const {
    return SkeletalAnimationsOffset;
}

uint64_t LegacyHeader::getSkeletalAnimationsDictionary() const {
    return SkeletalAnimationsDictionary;
}

uint64_t LegacyHeader::getMaterialAnimationsOffset() const {
    return MaterialAnimationsOffset;
}

uint64_t LegacyHeader::getMaterialAnimationsDictionary() const {
    return MaterialAnimationsDictionary;
}

uint64_t LegacyHeader::getBoneVisibilityAnimationArrayOffset() const {
    return BoneVisibilityAnimationArrayOffset;
}

uint64_t LegacyHeader::getBoneVisibilityAnimationArrayDictionary() const {
    return BoneVisibilityAnimationArrayDictionary;
}

uint64_t LegacyHeader::getShapeAnimationArrayOffset() const {
    return ShapeAnimationArrayOffset;
}

uint64_t LegacyHeader::getShapeAnimationDictionaryOffset() const {
    return ShapeAnimationDictionaryOffset;
}

uint64_t LegacyHeader::getSceneAnimationArrayOffset() const {
    return SceneAnimationArrayOffset;
}

uint64_t LegacyHeader::getSceneAnimationDictionaryOffset() const {
    return SceneAnimationDictionaryOffset;
}

uint64_t LegacyHeader::getMemoryPool() const {
    return MemoryPool;
}

uint64_t LegacyHeader::getBufferSection() const {
    return BufferSection;
}

uint64_t LegacyHeader::getEmbeddedFilesOffset() const {
    return EmbeddedFilesOffset;
}

uint64_t LegacyHeader::getEmbeddedFileDictionaryOffset() const {
    return EmbeddedFileDictionaryOffset;
}

uint64_t LegacyHeader::getStringTableOffset() const {
    return StringTableOffset;
}

uint32_t LegacyHeader::getStringTableSize() const {
    return StringTableSize;
}

uint16_t LegacyHeader::getModelCount() const {
    return ModelCount;
}

uint16_t LegacyHeader::getSkeletalAnimationCount() const {
    return SkeletalAnimationCount;
}

uint16_t LegacyHeader::getMaterialAnimationCount() const {
    return MaterialAnimationCount;
}

uint16_t LegacyHeader::getBoneVisualAnimationCount() const {
    return BoneVisualAnimationCount;
}

uint16_t LegacyHeader::getShapeAnimationCount() const {
    return ShapeAnimationCount;
}

uint16_t LegacyHeader::getSceneAnimationCount() const {
    return SceneAnimationCount;
}

uint16_t LegacyHeader::getExternalFileCount() const {
    return ExternalFileCount;
}

int LegacyHeader::getEndOfHeaderOffset() const {
    return EndOfHeaderOffset;
}

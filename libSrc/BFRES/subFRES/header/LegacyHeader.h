//
// Created by kino on 4/15/24.
//

#ifndef BFRES_LIB_LEGACYHEADER_H
#define BFRES_LIB_LEGACYHEADER_H

#include <cstdint>
#include <cstddef>
#include <string>
#include <iostream>
#include "../../../usefulFunctions/UintReader.h"

class LegacyHeader {
private:
    uint64_t SkeletalAnimationsOffset;
    uint64_t SkeletalAnimationsDictionary;
    uint64_t MaterialAnimationsOffset;
    uint64_t MaterialAnimationsDictionary;
    uint64_t BoneVisibilityAnimationArrayOffset;
    uint64_t BoneVisibilityAnimationArrayDictionary;
    uint64_t ShapeAnimationArrayOffset;
    uint64_t ShapeAnimationDictionaryOffset;
    uint64_t SceneAnimationArrayOffset;
    uint64_t SceneAnimationDictionaryOffset;
    uint64_t MemoryPool;
    uint64_t BufferSection;
    uint64_t EmbeddedFilesOffset;
    uint64_t EmbeddedFileDictionaryOffset;
    uint64_t StringTableOffset;
    uint32_t StringTableSize;
    uint16_t ModelCount;
    uint16_t SkeletalAnimationCount;
    uint16_t MaterialAnimationCount;
    uint16_t BoneVisualAnimationCount;
    uint16_t ShapeAnimationCount;
    uint16_t SceneAnimationCount;
    uint16_t ExternalFileCount;
    const int Padding[2]{ 8, 6};
    const int EndOfHeaderOffset = 0xD0;
public:
    explicit LegacyHeader(const char * data);

    [[nodiscard]] uint64_t getSkeletalAnimationsOffset() const;

    [[nodiscard]] uint64_t getSkeletalAnimationsDictionary() const;

    [[nodiscard]] uint64_t getMaterialAnimationsOffset() const;

    [[nodiscard]] uint64_t getMaterialAnimationsDictionary() const;

    [[nodiscard]] uint64_t getBoneVisibilityAnimationArrayOffset() const;

    [[nodiscard]] uint64_t getBoneVisibilityAnimationArrayDictionary() const;

    [[nodiscard]] uint64_t getShapeAnimationArrayOffset() const;

    [[nodiscard]] uint64_t getShapeAnimationDictionaryOffset() const;

    [[nodiscard]] uint64_t getSceneAnimationArrayOffset() const;

    [[nodiscard]] uint64_t getSceneAnimationDictionaryOffset() const;

    [[nodiscard]] uint64_t getMemoryPool() const;

    [[nodiscard]] uint64_t getBufferSection() const;

    [[nodiscard]] uint64_t getEmbeddedFilesOffset() const;

    [[nodiscard]] uint64_t getEmbeddedFileDictionaryOffset() const;

    [[nodiscard]] uint64_t getStringTableOffset() const;

    [[nodiscard]] uint32_t getStringTableSize() const;

    [[nodiscard]] uint16_t getModelCount() const;

    [[nodiscard]] uint16_t getSkeletalAnimationCount() const;

    [[nodiscard]] uint16_t getMaterialAnimationCount() const;

    [[nodiscard]] uint16_t getBoneVisualAnimationCount() const;

    [[nodiscard]] uint16_t getShapeAnimationCount() const;

    [[nodiscard]] uint16_t getSceneAnimationCount() const;

    [[nodiscard]] uint16_t getExternalFileCount() const;

    [[nodiscard]] int getEndOfHeaderOffset() const;

};


#endif //BFRES_LIB_LEGACYHEADER_H

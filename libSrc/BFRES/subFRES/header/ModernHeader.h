//
// Created by kino on 4/15/24.
//

#ifndef BFRES_LIB_MODERNHEADER_H
#define BFRES_LIB_MODERNHEADER_H

#include <cstdint>
#include <cstddef>
#include <string>
#include <iostream>

class ModernHeader {
public:
    ModernHeader(const char * data, bool endianess);

    [[nodiscard]] uint64_t getUnknownOffset() const;

    [[nodiscard]] uint64_t getUnknownDictionaryOffset() const;

    [[nodiscard]] uint64_t getUnknown2Offset() const;

    [[nodiscard]] uint64_t getUnknown2DictionaryOffset() const;

    [[nodiscard]] uint64_t getSkeletalAnimationsOffset() const;

    [[nodiscard]] uint64_t getSkeletalAnimationsDictionary() const;

    [[nodiscard]] uint64_t getMaterialsAnimationsOffset() const;

    [[nodiscard]] uint64_t getMaterialAnimationsDictionary() const;

    [[nodiscard]] uint64_t getBoneVisibilityAnimationArrayOffset() const;

    [[nodiscard]] uint64_t getBoneVisibilityAnimationArrayDictionary() const;

    [[nodiscard]] uint64_t getShapeAnimationArrayOffset() const;

    [[nodiscard]] uint64_t getShapeAnimationArrayDictionaryOffset() const;

    [[nodiscard]] uint64_t getSceneAnimationArrayOffset() const;

    [[nodiscard]] uint64_t getSceneAnimationArrayDictionaryOffset() const;

    [[nodiscard]] uint64_t getMemoryPool() const;

    [[nodiscard]] uint64_t getBufferSection() const;

    [[nodiscard]] uint64_t getEmbeddedFilesOffset() const;

    [[nodiscard]] uint64_t getEmbeddedFileDictionaryOffset() const;

    [[nodiscard]] uint64_t getStringTableOffset() const;

    [[nodiscard]] uint32_t getStringTableSize() const;

    [[nodiscard]] uint16_t getModelCount() const;

    [[nodiscard]] uint16_t getUnknownCount() const;

    [[nodiscard]] uint16_t getUnknown2Count() const;

    [[nodiscard]] uint16_t getSkeletalAnimationCount() const;

    [[nodiscard]] uint16_t getMaterialAnimationCount() const;

    [[nodiscard]] uint16_t getBoneVisualAnimationCount() const;

    [[nodiscard]] uint16_t getShapeAnimationCount() const;

    [[nodiscard]] uint16_t getSceneAnimationCount() const;

    [[nodiscard]] uint16_t getExternalFileCount() const;

    [[nodiscard]] int getEndOfHeaderOffset() const;

private:
    uint64_t UnknownOffset;
    uint64_t UnknownDictionaryOffset;
    uint64_t Unknown_2_Offset;
    uint64_t Unknown_2_DictionaryOffset;
    uint64_t SkeletalAnimationsOffset;
    uint64_t SkeletalAnimationsDictionary;
    uint64_t MaterialsAnimationsOffset;
    uint64_t MaterialAnimationsDictionary;
    uint64_t BoneVisibilityAnimationArrayOffset;
    uint64_t BoneVisibilityAnimationArrayDictionary;
    uint64_t ShapeAnimationArrayOffset;
    uint64_t ShapeAnimationArrayDictionaryOffset;
    uint64_t SceneAnimationArrayOffset;
    uint64_t SceneAnimationArrayDictionaryOffset;
    uint64_t MemoryPool;
    uint64_t BufferSection;
    uint64_t EmbeddedFilesOffset;
    uint64_t EmbeddedFileDictionaryOffset;
    uint64_t StringTableOffset;
    uint32_t StringTableSize;
    uint16_t ModelCount;
    uint16_t UnknownCount;
    uint16_t Unknown2Count;
    uint16_t SkeletalAnimationCount;
    uint16_t MaterialAnimationCount;
    uint16_t BoneVisualAnimationCount;
    uint16_t ShapeAnimationCount;
    uint16_t SceneAnimationCount;
    uint16_t ExternalFileCount;
    const int Padding[2]{ 8, 2};
    const int EndOfHeaderOffset = 0xF0;


};


#endif //BFRES_LIB_MODERNHEADER_H

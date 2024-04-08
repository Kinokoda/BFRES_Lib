#include "BFRES.h"

#include <iostream>

namespace BFRES
{
    class Header{
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
        Header(uint32_t signature, uint32_t version, uint16_t bom, std::byte alignment, std::byte targetAddressSize,
               uint32_t filenameOffset, uint16_t flags, uint16_t blockOffset, uint32_t relocationTableOffset,
               uint32_t bfresSize, uint64_t filenameLengthOffset, uint64_t fmdlOffset, uint64_t fmdlDictionaryOffset)
                : signature(signature), version(version), bom(bom), alignment(alignment),
                  target_address_size(targetAddressSize), filename_offset(filenameOffset), flags(flags),
                  block_offset(blockOffset), relocation_table_offset(relocationTableOffset), bfres_size(bfresSize),
                  filename_length_offset(filenameLengthOffset), fmdl_offset(fmdlOffset),
                  fmdl_dictionary_offset(fmdlDictionaryOffset) {}

        [[nodiscard]] uint32_t getSignature() const {
            return signature;
        }

        [[nodiscard]] uint32_t getVersion() const {
            return version;
        }

        [[nodiscard]] uint16_t getBom() const {
            return bom;
        }

        [[nodiscard]] std::byte getAlignment() const {
            return alignment;
        }

        [[nodiscard]] std::byte getTargetAddressSize() const {
            return target_address_size;
        }

        [[nodiscard]] uint32_t getFilenameOffset() const {
            return filename_offset;
        }

        [[nodiscard]] uint16_t getFlags() const {
            return flags;
        }

        [[nodiscard]] uint16_t getBlockOffset() const {
            return block_offset;
        }

        [[nodiscard]] uint32_t getRelocationTableOffset() const {
            return relocation_table_offset;
        }

        [[nodiscard]] uint32_t getBfresSize() const {
            return bfres_size;
        }

        [[nodiscard]] uint64_t getFilenameLengthOffset() const {
            return filename_length_offset;
        }

        [[nodiscard]] uint64_t getFmdlOffset() const {
            return fmdl_offset;
        }

        [[nodiscard]] uint64_t getFmdlDictionaryOffset() const {
            return fmdl_dictionary_offset;
        }

        void setSignature(uint32_t signature) {
            Header::signature = signature;
        }

        void setVersion(uint32_t version) {
            Header::version = version;
        }

        void setBom(uint16_t bom) {
            Header::bom = bom;
        }

        void setAlignment(std::byte alignment) {
            Header::alignment = alignment;
        }

        void setTargetAddressSize(std::byte targetAddressSize) {
            target_address_size = targetAddressSize;
        }

        void setFilenameOffset(uint32_t filenameOffset) {
            filename_offset = filenameOffset;
        }

        void setFlags(uint16_t flags) {
            Header::flags = flags;
        }

        void setBlockOffset(uint16_t blockOffset) {
            block_offset = blockOffset;
        }

        void setRelocationTableOffset(uint32_t relocationTableOffset) {
            relocation_table_offset = relocationTableOffset;
        }

        void setBfresSize(uint32_t bfresSize) {
            bfres_size = bfresSize;
        }

        void setFilenameLengthOffset(uint64_t filenameLengthOffset) {
            filename_length_offset = filenameLengthOffset;
        }

        void setFmdlOffset(uint64_t fmdlOffset) {
            fmdl_offset = fmdlOffset;
        }

        void setFmdlDictionaryOffset(uint64_t fmdlDictionaryOffset) {
            fmdl_dictionary_offset = fmdlDictionaryOffset;
        }
    };

    class HeaderModern : Header {
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

        public:

        HeaderModern(uint32_t signature, uint32_t version, uint16_t bom, std::byte alignment,
                     std::byte targetAddressSize, uint32_t filenameOffset, uint16_t flags, uint16_t blockOffset,
                     uint32_t relocationTableOffset, uint32_t bfresSize, uint64_t filenameLengthOffset,
                     uint64_t fmdlOffset, uint64_t fmdlDictionaryOffset, uint64_t unknownOffset,
                     uint64_t unknownDictionaryOffset, uint64_t unknown2Offset, uint64_t unknown2DictionaryOffset,
                     uint64_t skeletalAnimationsOffset, uint64_t skeletalAnimationsDictionary,
                     uint64_t materialsAnimationsOffset, uint64_t materialAnimationsDictionary,
                     uint64_t boneVisibilityAnimationArrayOffset, uint64_t boneVisibilityAnimationArrayDictionary,
                     uint64_t shapeAnimationArrayOffset, uint64_t shapeAnimationArrayDictionaryOffset,
                     uint64_t sceneAnimationArrayOffset, uint64_t sceneAnimationArrayDictionaryOffset,
                     uint64_t memoryPool, uint64_t bufferSection, uint64_t embeddedFilesOffset,
                     uint64_t embeddedFileDictionaryOffset, uint64_t stringTableOffset, uint32_t stringTableSize,
                     uint16_t modelCount, uint16_t unknownCount, uint16_t unknown2Count,
                     uint16_t skeletalAnimationCount, uint16_t materialAnimationCount,
                     uint16_t boneVisualAnimationCount, uint16_t shapeAnimationCount, uint16_t sceneAnimationCount,
                     uint16_t externalFileCount, const int endOfHeaderOffset) : Header(signature, version, bom,
                                                                                       alignment, targetAddressSize,
                                                                                       filenameOffset, flags,
                                                                                       blockOffset,
                                                                                       relocationTableOffset, bfresSize,
                                                                                       filenameLengthOffset, fmdlOffset,
                                                                                       fmdlDictionaryOffset),
                                                                                UnknownOffset(unknownOffset),
                                                                                UnknownDictionaryOffset(
                                                                                        unknownDictionaryOffset),
                                                                                Unknown_2_Offset(unknown2Offset),
                                                                                Unknown_2_DictionaryOffset(
                                                                                        unknown2DictionaryOffset),
                                                                                SkeletalAnimationsOffset(
                                                                                        skeletalAnimationsOffset),
                                                                                SkeletalAnimationsDictionary(
                                                                                        skeletalAnimationsDictionary),
                                                                                MaterialsAnimationsOffset(
                                                                                        materialsAnimationsOffset),
                                                                                MaterialAnimationsDictionary(
                                                                                        materialAnimationsDictionary),
                                                                                BoneVisibilityAnimationArrayOffset(
                                                                                        boneVisibilityAnimationArrayOffset),
                                                                                BoneVisibilityAnimationArrayDictionary(
                                                                                        boneVisibilityAnimationArrayDictionary),
                                                                                ShapeAnimationArrayOffset(
                                                                                        shapeAnimationArrayOffset),
                                                                                ShapeAnimationArrayDictionaryOffset(
                                                                                        shapeAnimationArrayDictionaryOffset),
                                                                                SceneAnimationArrayOffset(
                                                                                        sceneAnimationArrayOffset),
                                                                                SceneAnimationArrayDictionaryOffset(
                                                                                        sceneAnimationArrayDictionaryOffset),
                                                                                MemoryPool(memoryPool),
                                                                                BufferSection(bufferSection),
                                                                                EmbeddedFilesOffset(
                                                                                        embeddedFilesOffset),
                                                                                EmbeddedFileDictionaryOffset(
                                                                                        embeddedFileDictionaryOffset),
                                                                                StringTableOffset(stringTableOffset),
                                                                                StringTableSize(stringTableSize),
                                                                                ModelCount(modelCount),
                                                                                UnknownCount(unknownCount),
                                                                                Unknown2Count(unknown2Count),
                                                                                SkeletalAnimationCount(
                                                                                        skeletalAnimationCount),
                                                                                MaterialAnimationCount(
                                                                                        materialAnimationCount),
                                                                                BoneVisualAnimationCount(
                                                                                        boneVisualAnimationCount),
                                                                                ShapeAnimationCount(
                                                                                        shapeAnimationCount),
                                                                                SceneAnimationCount(
                                                                                        sceneAnimationCount),
                                                                                ExternalFileCount(externalFileCount),
                                                                                Padding(8,2),
                                                                                EndOfHeaderOffset(endOfHeaderOffset) {}

        [[nodiscard]] uint64_t getUnknownOffset() const {
                return UnknownOffset;
            }

            void setUnknownOffset(uint64_t unknownOffset) {
                UnknownOffset = unknownOffset;
            }

            [[nodiscard]] uint64_t getUnknownDictionaryOffset() const {
                return UnknownDictionaryOffset;
            }

            void setUnknownDictionaryOffset(uint64_t unknownDictionaryOffset) {
                UnknownDictionaryOffset = unknownDictionaryOffset;
            }

            [[nodiscard]] uint64_t getUnknown2Offset() const {
                return Unknown_2_Offset;
            }

            void setUnknown2Offset(uint64_t unknown2Offset) {
                Unknown_2_Offset = unknown2Offset;
            }

            [[nodiscard]] uint64_t getUnknown2DictionaryOffset() const {
                return Unknown_2_DictionaryOffset;
            }

            void setUnknown2DictionaryOffset(uint64_t unknown2DictionaryOffset) {
                Unknown_2_DictionaryOffset = unknown2DictionaryOffset;
            }

            [[nodiscard]] uint64_t getSkeletalAnimationsOffset() const {
                return SkeletalAnimationsOffset;
            }

            void setSkeletalAnimationsOffset(uint64_t skeletalAnimationsOffset) {
                SkeletalAnimationsOffset = skeletalAnimationsOffset;
            }

            [[nodiscard]] uint64_t getSkeletalAnimationsDictionary() const {
                return SkeletalAnimationsDictionary;
            }

            void setSkeletalAnimationsDictionary(uint64_t skeletalAnimationsDictionary) {
                SkeletalAnimationsDictionary = skeletalAnimationsDictionary;
            }

            [[nodiscard]] uint64_t getMaterialsAnimationsOffset() const {
                return MaterialsAnimationsOffset;
            }

            void setMaterialsAnimationsOffset(uint64_t materialsAnimationsOffset) {
                MaterialsAnimationsOffset = materialsAnimationsOffset;
            }

            [[nodiscard]] uint64_t getMaterialAnimationsDictionary() const {
                return MaterialAnimationsDictionary;
            }

            void setMaterialAnimationsDictionary(uint64_t materialAnimationsDictionary) {
                MaterialAnimationsDictionary = materialAnimationsDictionary;
            }

            [[nodiscard]] uint64_t getBoneVisibilityAnimationArrayOffset() const {
                return BoneVisibilityAnimationArrayOffset;
            }

            void setBoneVisibilityAnimationArrayOffset(uint64_t boneVisibilityAnimationArrayOffset) {
                BoneVisibilityAnimationArrayOffset = boneVisibilityAnimationArrayOffset;
            }

            [[nodiscard]] uint64_t getBoneVisibilityAnimationArrayDictionary() const {
                return BoneVisibilityAnimationArrayDictionary;
            }

            void setBoneVisibilityAnimationArrayDictionary(uint64_t boneVisibilityAnimationArrayDictionary) {
                BoneVisibilityAnimationArrayDictionary = boneVisibilityAnimationArrayDictionary;
            }

            [[nodiscard]] uint64_t getShapeAnimationArrayOffset() const {
                return ShapeAnimationArrayOffset;
            }

            void setShapeAnimationArrayOffset(uint64_t shapeAnimationArrayOffset) {
                ShapeAnimationArrayOffset = shapeAnimationArrayOffset;
            }

            [[nodiscard]] uint64_t getShapeAnimationArrayDictionaryOffset() const {
                return ShapeAnimationArrayDictionaryOffset;
            }

            void setShapeAnimationArrayDictionaryOffset(uint64_t shapeAnimationArrayDictionaryOffset) {
                ShapeAnimationArrayDictionaryOffset = shapeAnimationArrayDictionaryOffset;
            }

            [[nodiscard]] uint64_t getSceneAnimationArrayOffset() const {
                return SceneAnimationArrayOffset;
            }

            void setSceneAnimationArrayOffset(uint64_t sceneAnimationArrayOffset) {
                SceneAnimationArrayOffset = sceneAnimationArrayOffset;
            }

            [[nodiscard]] uint64_t getSceneAnimationArrayDictionaryOffset() const {
                return SceneAnimationArrayDictionaryOffset;
            }

            void setSceneAnimationArrayDictionaryOffset(uint64_t sceneAnimationArrayDictionaryOffset) {
                SceneAnimationArrayDictionaryOffset = sceneAnimationArrayDictionaryOffset;
            }

            [[nodiscard]] uint64_t getMemoryPool() const {
                return MemoryPool;
            }

            void setMemoryPool(uint64_t memoryPool) {
                MemoryPool = memoryPool;
            }

            [[nodiscard]] uint64_t getBufferSection() const {
                return BufferSection;
            }

            void setBufferSection(uint64_t bufferSection) {
                BufferSection = bufferSection;
            }

            [[nodiscard]] uint64_t getEmbeddedFilesOffset() const {
                return EmbeddedFilesOffset;
            }

            void setEmbeddedFilesOffset(uint64_t embeddedFilesOffset) {
                EmbeddedFilesOffset = embeddedFilesOffset;
            }

            [[nodiscard]] uint64_t getEmbeddedFileDictionaryOffset() const {
                return EmbeddedFileDictionaryOffset;
            }

            void setEmbeddedFileDictionaryOffset(uint64_t embeddedFileDictionaryOffset) {
                EmbeddedFileDictionaryOffset = embeddedFileDictionaryOffset;
            }

            [[nodiscard]] uint64_t getStringTableOffset() const {
                return StringTableOffset;
            }

            void setStringTableOffset(uint64_t stringTableOffset) {
                StringTableOffset = stringTableOffset;
            }

            [[nodiscard]] uint32_t getStringTableSize() const {
                return StringTableSize;
            }

            void setStringTableSize(uint32_t stringTableSize) {
                StringTableSize = stringTableSize;
            }

            [[nodiscard]] uint16_t getModelCount() const {
                return ModelCount;
            }

            void setModelCount(uint16_t modelCount) {
                ModelCount = modelCount;
            }

            [[nodiscard]] uint16_t getUnknownCount() const {
                return UnknownCount;
            }

            void setUnknownCount(uint16_t unknownCount) {
                UnknownCount = unknownCount;
            }

            [[nodiscard]] uint16_t getUnknown2Count() const {
                return Unknown2Count;
            }

            void setUnknown2Count(uint16_t unknown2Count) {
                Unknown2Count = unknown2Count;
            }

            [[nodiscard]] uint16_t getSkeletalAnimationCount() const {
                return SkeletalAnimationCount;
            }

            void setSkeletalAnimationCount(uint16_t skeletalAnimationCount) {
                SkeletalAnimationCount = skeletalAnimationCount;
            }

            [[nodiscard]] uint16_t getMaterialAnimationCount() const {
                return MaterialAnimationCount;
            }

            void setMaterialAnimationCount(uint16_t materialAnimationCount) {
                MaterialAnimationCount = materialAnimationCount;
            }

            [[nodiscard]] uint16_t getBoneVisualAnimationCount() const {
                return BoneVisualAnimationCount;
            }

            void setBoneVisualAnimationCount(uint16_t boneVisualAnimationCount) {
                BoneVisualAnimationCount = boneVisualAnimationCount;
            }

            [[nodiscard]] uint16_t getShapeAnimationCount() const {
                return ShapeAnimationCount;
            }

            void setShapeAnimationCount(uint16_t shapeAnimationCount) {
                ShapeAnimationCount = shapeAnimationCount;
            }

            [[nodiscard]] uint16_t getSceneAnimationCount() const {
                return SceneAnimationCount;
            }

            void setSceneAnimationCount(uint16_t sceneAnimationCount) {
                SceneAnimationCount = sceneAnimationCount;
            }

            [[nodiscard]] uint16_t getExternalFileCount() const {
                return ExternalFileCount;
            }

            void setExternalFileCount(uint16_t externalFileCount) {
                ExternalFileCount = externalFileCount;
            }

            [[nodiscard]] const int getEndOfHeaderOffset() const {
                return EndOfHeaderOffset;
            }
    };

    class HeaderLegacy : Header
    {
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
        HeaderLegacy(uint32_t signature, uint32_t version, uint16_t bom, std::byte alignment,
                     std::byte targetAddressSize, uint32_t filenameOffset, uint16_t flags, uint16_t blockOffset,
                     uint32_t relocationTableOffset, uint32_t bfresSize, uint64_t filenameLengthOffset,
                     uint64_t fmdlOffset, uint64_t fmdlDictionaryOffset, uint64_t skeletalAnimationsOffset,
                     uint64_t skeletalAnimationsDictionary, uint64_t materialAnimationsOffset,
                     uint64_t materialAnimationsDictionary, uint64_t boneVisibilityAnimationArrayOffset,
                     uint64_t boneVisibilityAnimationArrayDictionary, uint64_t shapeAnimationArrayOffset,
                     uint64_t shapeAnimationDictionaryOffset, uint64_t sceneAnimationArrayOffset,
                     uint64_t sceneAnimationDictionaryOffset, uint64_t memoryPool, uint64_t bufferSection,
                     uint64_t embeddedFilesOffset, uint64_t embeddedFileDictionaryOffset, uint64_t stringTableOffset,
                     uint32_t stringTableSize, uint16_t modelCount, uint16_t skeletalAnimationCount,
                     uint16_t materialAnimationCount, uint16_t boneVisualAnimationCount, uint16_t shapeAnimationCount,
                     uint16_t sceneAnimationCount, uint16_t externalFileCount, const int *padding,
                     const int endOfHeaderOffset) : Header(signature, version, bom, alignment, targetAddressSize,
                                                           filenameOffset, flags, blockOffset, relocationTableOffset,
                                                           bfresSize, filenameLengthOffset, fmdlOffset,
                                                           fmdlDictionaryOffset),
                                                    SkeletalAnimationsOffset(skeletalAnimationsOffset),
                                                    SkeletalAnimationsDictionary(skeletalAnimationsDictionary),
                                                    MaterialAnimationsOffset(materialAnimationsOffset),
                                                    MaterialAnimationsDictionary(materialAnimationsDictionary),
                                                    BoneVisibilityAnimationArrayOffset(
                                                            boneVisibilityAnimationArrayOffset),
                                                    BoneVisibilityAnimationArrayDictionary(
                                                            boneVisibilityAnimationArrayDictionary),
                                                    ShapeAnimationArrayOffset(shapeAnimationArrayOffset),
                                                    ShapeAnimationDictionaryOffset(shapeAnimationDictionaryOffset),
                                                    SceneAnimationArrayOffset(sceneAnimationArrayOffset),
                                                    SceneAnimationDictionaryOffset(sceneAnimationDictionaryOffset),
                                                    MemoryPool(memoryPool), BufferSection(bufferSection),
                                                    EmbeddedFilesOffset(embeddedFilesOffset),
                                                    EmbeddedFileDictionaryOffset(embeddedFileDictionaryOffset),
                                                    StringTableOffset(stringTableOffset),
                                                    StringTableSize(stringTableSize), ModelCount(modelCount),
                                                    SkeletalAnimationCount(skeletalAnimationCount),
                                                    MaterialAnimationCount(materialAnimationCount),
                                                    BoneVisualAnimationCount(boneVisualAnimationCount),
                                                    ShapeAnimationCount(shapeAnimationCount),
                                                    SceneAnimationCount(sceneAnimationCount),
                                                    ExternalFileCount(externalFileCount), Padding(8,6),
                                                    EndOfHeaderOffset(endOfHeaderOffset) {}

        [[nodiscard]] uint64_t getSkeletalAnimationsOffset() const {
            return SkeletalAnimationsOffset;
        }

        [[nodiscard]] uint64_t getSkeletalAnimationsDictionary() const {
            return SkeletalAnimationsDictionary;
        }

        [[nodiscard]] uint64_t getMaterialAnimationsOffset() const {
            return MaterialAnimationsOffset;
        }

        [[nodiscard]] uint64_t getMaterialAnimationsDictionary() const {
            return MaterialAnimationsDictionary;
        }

        [[nodiscard]] uint64_t getBoneVisibilityAnimationArrayOffset() const {
            return BoneVisibilityAnimationArrayOffset;
        }

        [[nodiscard]] uint64_t getBoneVisibilityAnimationArrayDictionary() const {
            return BoneVisibilityAnimationArrayDictionary;
        }

        [[nodiscard]] uint64_t getShapeAnimationArrayOffset() const {
            return ShapeAnimationArrayOffset;
        }

        [[nodiscard]] uint64_t getShapeAnimationDictionaryOffset() const {
            return ShapeAnimationDictionaryOffset;
        }

        [[nodiscard]] uint64_t getSceneAnimationArrayOffset() const {
            return SceneAnimationArrayOffset;
        }

        [[nodiscard]] uint64_t getSceneAnimationDictionaryOffset() const {
            return SceneAnimationDictionaryOffset;
        }

        [[nodiscard]] uint64_t getMemoryPool() const {
            return MemoryPool;
        }

        [[nodiscard]] uint64_t getBufferSection() const {
            return BufferSection;
        }

        [[nodiscard]] uint64_t getEmbeddedFilesOffset() const {
            return EmbeddedFilesOffset;
        }

        [[nodiscard]] uint64_t getEmbeddedFileDictionaryOffset() const {
            return EmbeddedFileDictionaryOffset;
        }

        [[nodiscard]] uint64_t getStringTableOffset() const {
            return StringTableOffset;
        }

        [[nodiscard]] uint32_t getStringTableSize() const {
            return StringTableSize;
        }

        [[nodiscard]] uint16_t getModelCount() const {
            return ModelCount;
        }

        [[nodiscard]] uint16_t getSkeletalAnimationCount() const {
            return SkeletalAnimationCount;
        }

        [[nodiscard]] uint16_t getMaterialAnimationCount() const {
            return MaterialAnimationCount;
        }

        [[nodiscard]] uint16_t getBoneVisualAnimationCount() const {
            return BoneVisualAnimationCount;
        }

        [[nodiscard]] uint16_t getShapeAnimationCount() const {
            return ShapeAnimationCount;
        }

        [[nodiscard]] uint16_t getSceneAnimationCount() const {
            return SceneAnimationCount;
        }

        [[nodiscard]] uint16_t getExternalFileCount() const {
            return ExternalFileCount;
        }

        [[nodiscard]] const int *getPadding() const {
            return Padding;
        }

        [[nodiscard]] const int getEndOfHeaderOffset() const {
            return EndOfHeaderOffset;
        }

        void setSkeletalAnimationsOffset(uint64_t skeletalAnimationsOffset) {
            SkeletalAnimationsOffset = skeletalAnimationsOffset;
        }

        void setSkeletalAnimationsDictionary(uint64_t skeletalAnimationsDictionary) {
            SkeletalAnimationsDictionary = skeletalAnimationsDictionary;
        }

        void setMaterialAnimationsOffset(uint64_t materialAnimationsOffset) {
            MaterialAnimationsOffset = materialAnimationsOffset;
        }

        void setMaterialAnimationsDictionary(uint64_t materialAnimationsDictionary) {
            MaterialAnimationsDictionary = materialAnimationsDictionary;
        }

        void setBoneVisibilityAnimationArrayOffset(uint64_t boneVisibilityAnimationArrayOffset) {
            BoneVisibilityAnimationArrayOffset = boneVisibilityAnimationArrayOffset;
        }

        void setBoneVisibilityAnimationArrayDictionary(uint64_t boneVisibilityAnimationArrayDictionary) {
            BoneVisibilityAnimationArrayDictionary = boneVisibilityAnimationArrayDictionary;
        }

        void setShapeAnimationArrayOffset(uint64_t shapeAnimationArrayOffset) {
            ShapeAnimationArrayOffset = shapeAnimationArrayOffset;
        }

        void setShapeAnimationDictionaryOffset(uint64_t shapeAnimationDictionaryOffset) {
            ShapeAnimationDictionaryOffset = shapeAnimationDictionaryOffset;
        }

        void setSceneAnimationArrayOffset(uint64_t sceneAnimationArrayOffset) {
            SceneAnimationArrayOffset = sceneAnimationArrayOffset;
        }

        void setSceneAnimationDictionaryOffset(uint64_t sceneAnimationDictionaryOffset) {
            SceneAnimationDictionaryOffset = sceneAnimationDictionaryOffset;
        }

        void setMemoryPool(uint64_t memoryPool) {
            MemoryPool = memoryPool;
        }

        void setBufferSection(uint64_t bufferSection) {
            BufferSection = bufferSection;
        }

        void setEmbeddedFilesOffset(uint64_t embeddedFilesOffset) {
            EmbeddedFilesOffset = embeddedFilesOffset;
        }

        void setEmbeddedFileDictionaryOffset(uint64_t embeddedFileDictionaryOffset) {
            EmbeddedFileDictionaryOffset = embeddedFileDictionaryOffset;
        }

        void setStringTableOffset(uint64_t stringTableOffset) {
            StringTableOffset = stringTableOffset;
        }

        void setStringTableSize(uint32_t stringTableSize) {
            StringTableSize = stringTableSize;
        }

        void setModelCount(uint16_t modelCount) {
            ModelCount = modelCount;
        }

        void setSkeletalAnimationCount(uint16_t skeletalAnimationCount) {
            SkeletalAnimationCount = skeletalAnimationCount;
        }

        void setMaterialAnimationCount(uint16_t materialAnimationCount) {
            MaterialAnimationCount = materialAnimationCount;
        }

        void setBoneVisualAnimationCount(uint16_t boneVisualAnimationCount) {
            BoneVisualAnimationCount = boneVisualAnimationCount;
        }

        void setShapeAnimationCount(uint16_t shapeAnimationCount) {
            ShapeAnimationCount = shapeAnimationCount;
        }

        void setSceneAnimationCount(uint16_t sceneAnimationCount) {
            SceneAnimationCount = sceneAnimationCount;
        }

        void setExternalFileCount(uint16_t externalFileCount) {
            ExternalFileCount = externalFileCount;
        }
    };

    class FMDL_Header{
        const std::string Magic = "FMDL";
        uint64_t FMAT_DictionaryOffset;
        uint64_t UserDataOffset;
        uint16_t VertexArrayCount;
        uint16_t ShapeCount;
        uint16_t MaterialCount;
        uint16_t UserDataCount;
        uint32_t TotalVertexCount;
        const int PaddingStatic[2]{16,4};
        const int EndOfHeader = 0X78;
    public:
        FMDL_Header(const std::string &magic, uint64_t fmatDictionaryOffset, uint64_t userDataOffset,
                    uint16_t vertexArrayCount, uint16_t shapeCount, uint16_t materialCount, uint16_t userDataCount,
                    uint32_t totalVertexCount, const int *padding, const int endOfHeader) : Magic(magic),
                                                                                            FMAT_DictionaryOffset(
                                                                                                    fmatDictionaryOffset),
                                                                                            UserDataOffset(
                                                                                                    userDataOffset),
                                                                                            VertexArrayCount(
                                                                                                    vertexArrayCount),
                                                                                            ShapeCount(shapeCount),
                                                                                            MaterialCount(
                                                                                                    materialCount),
                                                                                            UserDataCount(
                                                                                                    userDataCount),
                                                                                            TotalVertexCount(
                                                                                                    totalVertexCount),
                                                                                            PaddingStatic(16,4),
                                                                                            EndOfHeader(endOfHeader) {}

        [[nodiscard]] const std::string &getMagic() const {
            return Magic;
        }

        [[nodiscard]] uint64_t getFmatDictionaryOffset() const {
            return FMAT_DictionaryOffset;
        }

        void setFmatDictionaryOffset(uint64_t fmatDictionaryOffset) {
            FMAT_DictionaryOffset = fmatDictionaryOffset;
        }

        [[nodiscard]] uint64_t getUserDataOffset() const {
            return UserDataOffset;
        }

        void setUserDataOffset(uint64_t userDataOffset) {
            UserDataOffset = userDataOffset;
        }

        [[nodiscard]] uint16_t getVertexArrayCount() const {
            return VertexArrayCount;
        }

        void setVertexArrayCount(uint16_t vertexArrayCount) {
            VertexArrayCount = vertexArrayCount;
        }

        [[nodiscard]] uint16_t getShapeCount() const {
            return ShapeCount;
        }

        void setShapeCount(uint16_t shapeCount) {
            ShapeCount = shapeCount;
        }

        [[nodiscard]] uint16_t getMaterialCount() const {
            return MaterialCount;
        }

        void setMaterialCount(uint16_t materialCount) {
            MaterialCount = materialCount;
        }

        [[nodiscard]] uint16_t getUserDataCount() const {
            return UserDataCount;
        }

        void setUserDataCount(uint16_t userDataCount) {
            UserDataCount = userDataCount;
        }

        [[nodiscard]] uint32_t getTotalVertexCount() const {
            return TotalVertexCount;
        }

        void setTotalVertexCount(uint32_t totalVertexCount) {
            TotalVertexCount = totalVertexCount;
        }

        [[nodiscard]] const int *getStaticPadding() const {
            return PaddingStatic;
        }

        [[nodiscard]] int getEndOfHeader() const {
            return EndOfHeader;
        }
    };

    class FMDL_HeaderModern : FMDL_Header{
        uint32_t FlagPadding;
        uint64_t ModelNameOffset;
        uint64_t PathNameOffset;
        uint64_t FSKL_Offset;
        uint64_t FVTX_Offset;
        uint64_t FSHP_Offset;
        uint64_t FSHP_Dictionary_Offset;
        uint64_t FMAT_Offset;
        uint64_t Padding;
    public:
        FMDL_HeaderModern(const std::string &magic, uint64_t fmatDictionaryOffset, uint64_t userDataOffset,
                          uint16_t vertexArrayCount, uint16_t shapeCount, uint16_t materialCount,
                          uint16_t userDataCount, uint32_t totalVertexCount, const int *padding, const int endOfHeader,
                          uint32_t flagPadding, uint64_t modelNameOffset, uint64_t pathNameOffset, uint64_t fsklOffset,
                          uint64_t fvtxOffset, uint64_t fshpOffset, uint64_t fshpDictionaryOffset, uint64_t fmatOffset,
                          uint64_t padding1) : FMDL_Header(magic, fmatDictionaryOffset, userDataOffset,
                                                           vertexArrayCount, shapeCount, materialCount, userDataCount,
                                                           totalVertexCount, padding, endOfHeader),
                                               FlagPadding(flagPadding), ModelNameOffset(modelNameOffset),
                                               PathNameOffset(pathNameOffset), FSKL_Offset(fsklOffset),
                                               FVTX_Offset(fvtxOffset), FSHP_Offset(fshpOffset),
                                               FSHP_Dictionary_Offset(fshpDictionaryOffset), FMAT_Offset(fmatOffset),
                                               Padding(padding1) {}

        [[nodiscard]] uint32_t getFlagPadding() const {
            return FlagPadding;
        }

        void setFlagPadding(uint32_t flagPadding) {
            FlagPadding = flagPadding;
        }

        [[nodiscard]] uint64_t getModelNameOffset() const {
            return ModelNameOffset;
        }

        void setModelNameOffset(uint64_t modelNameOffset) {
            ModelNameOffset = modelNameOffset;
        }

        [[nodiscard]] uint64_t getPathNameOffset() const {
            return PathNameOffset;
        }

        void setPathNameOffset(uint64_t pathNameOffset) {
            PathNameOffset = pathNameOffset;
        }

        [[nodiscard]] uint64_t getFsklOffset() const {
            return FSKL_Offset;
        }

        void setFsklOffset(uint64_t fsklOffset) {
            FSKL_Offset = fsklOffset;
        }

        [[nodiscard]] uint64_t getFvtxOffset() const {
            return FVTX_Offset;
        }

        void setFvtxOffset(uint64_t fvtxOffset) {
            FVTX_Offset = fvtxOffset;
        }

        [[nodiscard]] uint64_t getFshpOffset() const {
            return FSHP_Offset;
        }

        void setFshpOffset(uint64_t fshpOffset) {
            FSHP_Offset = fshpOffset;
        }

        [[nodiscard]] uint64_t getFshpDictionaryOffset() const {
            return FSHP_Dictionary_Offset;
        }

        void setFshpDictionaryOffset(uint64_t fshpDictionaryOffset) {
            FSHP_Dictionary_Offset = fshpDictionaryOffset;
        }

        [[nodiscard]] uint64_t getFmatOffset() const {
            return FMAT_Offset;
        }

        void setFmatOffset(uint64_t fmatOffset) {
            FMAT_Offset = fmatOffset;
        }

        [[nodiscard]]  uint64_t getPadding() const {
            return Padding;
        }

        void setPadding(uint64_t padding) {
            Padding = padding;
        }
    };

    class FMDL_HeaderLegacy : FMDL_Header{
        uint32_t BlockSize;
        uint64_t BlockOffset;
        uint64_t ModelNameOffset;
        uint64_t PathnameOffset;
        uint64_t FSKL_Offset;
        uint64_t FVTX_Offset;
        uint64_t FSHP_Offset;
        uint64_t FSHP_DictionaryOffset;
        uint64_t FMAT_Offset;
    public:
        FMDL_HeaderLegacy(const std::string &magic, uint64_t fmatDictionaryOffset, uint64_t userDataOffset,
                          uint16_t vertexArrayCount, uint16_t shapeCount, uint16_t materialCount,
                          uint16_t userDataCount, uint32_t totalVertexCount, const int *padding, const int endOfHeader,
                          uint32_t blockSize, uint64_t blockOffset, uint64_t modelNameOffset, uint64_t pathnameOffset,
                          uint64_t fsklOffset, uint64_t fvtxOffset, uint64_t fshpOffset, uint64_t fshpDictionaryOffset,
                          uint64_t fmatOffset) : FMDL_Header(magic, fmatDictionaryOffset, userDataOffset,
                                                             vertexArrayCount, shapeCount, materialCount, userDataCount,
                                                             totalVertexCount, padding, endOfHeader),
                                                 BlockSize(blockSize), BlockOffset(blockOffset),
                                                 ModelNameOffset(modelNameOffset), PathnameOffset(pathnameOffset),
                                                 FSKL_Offset(fsklOffset), FVTX_Offset(fvtxOffset),
                                                 FSHP_Offset(fshpOffset), FSHP_DictionaryOffset(fshpDictionaryOffset),
                                                 FMAT_Offset(fmatOffset) {}

        [[nodiscard]] uint32_t getBlockSize() const {
            return BlockSize;
        }

        void setBlockSize(uint32_t blockSize) {
            BlockSize = blockSize;
        }

        [[nodiscard]] uint64_t getBlockOffset() const {
            return BlockOffset;
        }

        void setBlockOffset(uint64_t blockOffset) {
            BlockOffset = blockOffset;
        }

        [[nodiscard]] uint64_t getModelNameOffset() const {
            return ModelNameOffset;
        }

        void setModelNameOffset(uint64_t modelNameOffset) {
            ModelNameOffset = modelNameOffset;
        }

        [[nodiscard]] uint64_t getPathnameOffset() const {
            return PathnameOffset;
        }

        void setPathnameOffset(uint64_t pathnameOffset) {
            PathnameOffset = pathnameOffset;
        }

        [[nodiscard]] uint64_t getFsklOffset() const {
            return FSKL_Offset;
        }

        void setFsklOffset(uint64_t fsklOffset) {
            FSKL_Offset = fsklOffset;
        }

        [[nodiscard]] uint64_t getFvtxOffset() const {
            return FVTX_Offset;
        }

        void setFvtxOffset(uint64_t fvtxOffset) {
            FVTX_Offset = fvtxOffset;
        }

        [[nodiscard]] uint64_t getFshpOffset() const {
            return FSHP_Offset;
        }

        void setFshpOffset(uint64_t fshpOffset) {
            FSHP_Offset = fshpOffset;
        }

        [[nodiscard]] uint64_t getFshpDictionaryOffset() const {
            return FSHP_DictionaryOffset;
        }

        void setFshpDictionaryOffset(uint64_t fshpDictionaryOffset) {
            FSHP_DictionaryOffset = fshpDictionaryOffset;
        }

        [[nodiscard]] uint64_t getFmatOffset() const {
            return FMAT_Offset;
        }

        void setFmatOffset(uint64_t fmatOffset) {
            FMAT_Offset = fmatOffset;
        }
    };

    class FVTX_Header{
        std::string Magic = "FVTX";
        uint64_t VertexBufferSize;
        uint64_t VertexStrideSize;
        uint64_t VertexBufferArrayOffset;
        uint32_t BufferOffset;
        std::byte VertexAtributteCount;
        std::byte VertexBufferCount;
        uint16_t VertexIndex;
        uint32_t VertexCount;
        uint32_t SkinWeightInfluence;
        const int EndOfHeader = 0x60;
    public:
        FVTX_Header(const std::string &magic, uint64_t vertexBufferSize, uint64_t vertexStrideSize,
                    uint64_t vertexBufferArrayOffset, uint32_t bufferOffset, std::byte vertexAtributteCount,
                    std::byte vertexBufferCount, uint16_t vertexIndex, uint32_t vertexCount,
                    uint32_t skinWeightInfluence, const int endOfHeader) : Magic(magic),
                                                                           VertexBufferSize(vertexBufferSize),
                                                                           VertexStrideSize(vertexStrideSize),
                                                                           VertexBufferArrayOffset(
                                                                                   vertexBufferArrayOffset),
                                                                           BufferOffset(bufferOffset),
                                                                           VertexAtributteCount(vertexAtributteCount),
                                                                           VertexBufferCount(vertexBufferCount),
                                                                           VertexIndex(vertexIndex),
                                                                           VertexCount(vertexCount),
                                                                           SkinWeightInfluence(skinWeightInfluence),
                                                                           EndOfHeader(endOfHeader) {}

        [[nodiscard]] const std::string &getMagic() const {
            return Magic;
        }

        void setMagic(const std::string &magic) {
            Magic = magic;
        }

        [[nodiscard]] uint64_t getVertexBufferSize() const {
            return VertexBufferSize;
        }

        void setVertexBufferSize(uint64_t vertexBufferSize) {
            VertexBufferSize = vertexBufferSize;
        }

        [[nodiscard]] uint64_t getVertexStrideSize() const {
            return VertexStrideSize;
        }

        void setVertexStrideSize(uint64_t vertexStrideSize) {
            VertexStrideSize = vertexStrideSize;
        }

        [[nodiscard]] uint64_t getVertexBufferArrayOffset() const {
            return VertexBufferArrayOffset;
        }

        void setVertexBufferArrayOffset(uint64_t vertexBufferArrayOffset) {
            VertexBufferArrayOffset = vertexBufferArrayOffset;
        }

        [[nodiscard]] uint32_t getBufferOffset() const {
            return BufferOffset;
        }

        void setBufferOffset(uint32_t bufferOffset) {
            BufferOffset = bufferOffset;
        }

        [[nodiscard]] std::byte getVertexAtributteCount() const {
            return VertexAtributteCount;
        }

        void setVertexAtributteCount(std::byte vertexAtributteCount) {
            VertexAtributteCount = vertexAtributteCount;
        }

        [[nodiscard]] std::byte getVertexBufferCount() const {
            return VertexBufferCount;
        }

        void setVertexBufferCount(std::byte vertexBufferCount) {
            VertexBufferCount = vertexBufferCount;
        }

        [[nodiscard]] uint16_t getVertexIndex() const {
            return VertexIndex;
        }

        void setVertexIndex(uint16_t vertexIndex) {
            VertexIndex = vertexIndex;
        }

        [[nodiscard]] uint32_t getVertexCount() const {
            return VertexCount;
        }

        void setVertexCount(uint32_t vertexCount) {
            VertexCount = vertexCount;
        }

        [[nodiscard]] uint32_t getSkinWeightInfluence() const {
            return SkinWeightInfluence;
        }

        void setSkinWeightInfluence(uint32_t skinWeightInfluence) {
            SkinWeightInfluence = skinWeightInfluence;
        }

        [[nodiscard]] int getEndOfHeader() const {
            return EndOfHeader;
        }
    };

    class FVTX_HeaderModern : FVTX_Header{
        std::byte Flags[4];
        uint64_t VertexAttributeArrayOffset;
        uint64_t VertexAttributeArrayDictionary;
        uint64_t MemoryPool;
        uint64_t UnknownOffset;

    public:
        
    };

    class bfresFile
    {

    };
}
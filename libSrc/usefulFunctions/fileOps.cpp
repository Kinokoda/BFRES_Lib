//
// Created by kino on 4/12/24.
//

#include "fileOps.h"

std::vector<std::byte> fileOps::readFileData(const std::string &name) {
    std::ifstream inputFile(name, std::ios_base::binary);

    // Determine the length of the file by seeking
    // to the end of the file, reading the value of the
    // position indicator, and then seeking back to the beginning.
    inputFile.seekg(0, std::ios_base::end);
    auto length = inputFile.tellg();
    inputFile.seekg(0, std::ios_base::beg);

    // Make a buffer of the exact size of the file and read the data into it.
    std::vector<std::byte> buffer(length);
    inputFile.read(reinterpret_cast<char*>(buffer.data()), length);

    inputFile.close();
    return buffer;
}
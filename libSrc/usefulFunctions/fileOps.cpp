//
// Created by kino on 4/12/24.
//

#include "fileOps.h"

std::byte * fileOps::read(const std::string& filepath){
    std::ifstream resfile(filepath, std::ios::binary);

    if (!resfile) {
        throw std::runtime_error("Failed to open " + filepath + "\n");
    }

    resfile.seekg(0, std::ifstream::end);
    long length = resfile.tellg();
    resfile.seekg(0, std::ifstream::end);

    auto buffer = new std::byte[length];
    std::cout << "Reading " << length << " characters... ";
    resfile.read((char *)buffer, length);
    std::cout << "all data read successfully.\n";

    return buffer;
}
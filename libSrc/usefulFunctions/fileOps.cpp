//
// Created by kino on 4/12/24.
//

#include "fileOps.h"

fileOps::fileOps(const std::string& filePath) {
    length = 0;
    data = nullptr;
    readFile(filePath);
}

const char * fileOps::getData() const {
    return data;
}

long fileOps::getLength() const {
    return length;
}

void fileOps::readFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::in|std::ios::binary|std::ios::ate);
    if (!file){
        throw std::runtime_error("Error reading file");
    }
    if (file.is_open()){
        long size = file.tellg();
        length = size;
        data = new char[size];
        file.seekg(0, std::ios::beg);
        file.read(data, size);
        file.close();
        //std::cout << "File Magic: " << data << std::endl;
    }
}
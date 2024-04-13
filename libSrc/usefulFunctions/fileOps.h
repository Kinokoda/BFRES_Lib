//
// Created by kino on 4/12/24.
//

#ifndef BFRES_LIB_FILEOPS_H
#define BFRES_LIB_FILEOPS_H

#include <cstddef>
#include <fstream>
#include <vector>
#include <iostream>
#include <array>

using Bytes = std::vector<std::byte>;

class fileOps {
private:
    long length;
    char * data;

public:

    explicit fileOps(const std::string& filePath);

    void readFile(const std::string& filePath);

    [[nodiscard]] const char * getData() const;

    [[nodiscard]] long getLength() const;

};


#endif //BFRES_LIB_FILEOPS_H

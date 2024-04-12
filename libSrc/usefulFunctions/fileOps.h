//
// Created by kino on 4/12/24.
//

#ifndef BFRES_LIB_FILEOPS_H
#define BFRES_LIB_FILEOPS_H

#include <cstddef>
#include <fstream>
#include <vector>

class fileOps {
    public:
    static std::vector<std::byte> readFileData(const std::string &path);
};


#endif //BFRES_LIB_FILEOPS_H

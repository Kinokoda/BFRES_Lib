//
// Created by kino on 4/12/24.
//

#ifndef BFRES_LIB_FILEOPS_H
#define BFRES_LIB_FILEOPS_H

#include <cstddef>
#include <fstream>
#include <vector>
#include <iostream>

class fileOps {
    public:
    std::byte static * read(const std::string& filepath);
};


#endif //BFRES_LIB_FILEOPS_H

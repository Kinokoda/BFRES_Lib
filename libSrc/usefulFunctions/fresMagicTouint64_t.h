//
// Created by kino on 4/17/24.
//

#ifndef BFRES_LIB_FRESMAGICTOUINT64_T_H
#define BFRES_LIB_FRESMAGICTOUINT64_T_H

#include <cstdint>
#include <string>

namespace MagicToString{

    uint64_t stringToUint64(const std::string& str) {
        uint64_t result = 0;
        for (char c : str) {
            result = (result << 8) | static_cast<unsigned char>(c);
        }
        return result;
    }
};
#endif //BFRES_LIB_FRESMAGICTOUINT64_T_H

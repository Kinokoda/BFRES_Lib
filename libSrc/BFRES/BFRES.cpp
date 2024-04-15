//
// Created by kino on 4/14/24.
//

#include "BFRES.h"
#include "subFRES/header/LegacyHeader.h"

BFRES::BFRES(const char * data) {
    Header Header(data);

    if(Header.isEndianess()){
        std::cout << "Big Endian" << std::endl;
        ModernHeader ModernHeader(data, Header.isEndianess());

    } else{
        std::cout << "Little Endian" << std::endl;
        LegacyHeader LegacyHeader(data);
    }

    std::cout << "BFRES created" << std::endl;
}

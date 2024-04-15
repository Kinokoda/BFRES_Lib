//
// Created by kino on 4/14/24.
//

#ifndef BFRES_LIB_BFRES_H
#define BFRES_LIB_BFRES_H

#include <cstdint>
#include <cstddef>
#include <string>
#include <iostream>
#include "subFRES/header/Header.h"
#include "subFRES/header/ModernHeader.h"
#include "subFRES/header/LegacyHeader.h"

class BFRES {
private:

public:
    explicit BFRES(const char * data);

};


#endif //BFRES_LIB_BFRES_H

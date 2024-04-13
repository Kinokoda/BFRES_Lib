//
// Created by kino on 4/12/24.
//


#include "main.h"

int main(){
    fileOps file("/home/kino/Downloads/Player00.bfres");
    auto data = file.getData();

    std::cout << (uint8_t) data[0x0C] - 0 << std::endl;

    //Header header((std::byte *) data);


    return 0;
}

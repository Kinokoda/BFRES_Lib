//
// Created by kino on 4/12/24.
//

#include "main.h"

int main(){
    std::byte* fileData = fileOps::read("/home/kino/Downloads/Player00.bfres");
    std::cout << "File data: " << fileData << std::endl;
    return 0;
}
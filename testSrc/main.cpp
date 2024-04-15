//
// Created by kino on 4/12/24.
//


#include "main.h"


int main(){
    fileOps file("/home/kino/Downloads/Clt_SDODR000_M.bfres");
    auto data = file.getData();
    BFRES resFile(data);

    return 0;
}
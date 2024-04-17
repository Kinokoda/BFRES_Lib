cmake_minimum_required(VERSION 3.28)
project(BFRES_Lib VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

add_library(BFRES_Lib STATIC
        libSrc/BFRES/res_bfres.hpp
        libSrc/BFRES/res_bfresanimcurve.hpp
        libSrc/BFRES/res_bfresbonevisibilityanim.hpp
        libSrc/BFRES/res_bfresmaterial.hpp
        libSrc/BFRES/res_bfresmaterialanim.hpp
        libSrc/BFRES/res_bfresmodel.hpp
        libSrc/BFRES/res_bfressceneanim.hpp
        libSrc/BFRES/res_bfresshape.hpp
        libSrc/BFRES/res_bfresshapeanim.hpp
        libSrc/BFRES/res_bfresskeletalanim.hpp
        libSrc/BFRES/res_bfresskeleton.hpp
        libSrc/BFRES/res_gfxcommon.hpp
        libSrc/BFRES/res_gfxtostring.hpp
        libSrc/BFRES/res_nintendowaredictionary.hpp
        libSrc/BFRES/res_nintendowarefileheader.hpp
        libSrc/BFRES/res_nintendowarerelocationtable.cpp
        libSrc/BFRES/res_nintendowarerelocationtable.h
        libSrc/BFRES/res_nintendowarestringpool.hpp
        libSrc/usefulFunctions/usefulStructs.h
        libSrc/usefulFunctions/fresMagicTouint64_t.h
        #libSrc/BFRES/BFRES.cpp
        #libSrc/BFRES/BFRES.h
        #libSrc/BFRES/subFRES/header/Header.cpp
        #libSrc/BFRES/subFRES/header/Header.h
        #libSrc/BFRES/subFRES/header/ModernHeader.cpp
        #libSrc/BFRES/subFRES/header/ModernHeader.h
        #libSrc/BFRES/subFRES/header/LegacyHeader.cpp
        #libSrc/BFRES/subFRES/header/LegacyHeader.h
        #libSrc/BFRES/subFRES/FMDL/FMDL.cpp
        #libSrc/BFRES/subFRES/FMDL/FMDL.h

)

#add_library(fileOps STATIC
        #libSrc/usefulFunctions/fileOps.cpp
        #libSrc/usefulFunctions/fileOps.h
        #libSrc/usefulFunctions/UintReader.cpp
        #libSrc/usefulFunctions/UintReader.h
#)

add_executable(BFRES_Lib_Test
        testSrc/main.h
        testSrc/main.cpp
)

target_link_libraries(BFRES_Lib_Test BFRES_Lib)
#target_link_libraries(BFRES_Lib_Test fileOps)

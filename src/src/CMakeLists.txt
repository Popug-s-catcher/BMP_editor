cmake_minimum_required(VERSION 3.2)

project(bmp_edit)

set(SOURCE_EXE main.c)

add_library(configs STATIC configs.h configs.c)
add_library(AuxFunc STATIC AuxFunc.h AuxFunc.c)
add_library(rectangle STATIC rectangle.h rectangle.c)
add_library(frame STATIC frame.h frame.c)
add_library(rotation STATIC rotation.h rotation.c)

add_executable(main ${SOURCE_EXE})

target_link_libraries(rectangle AuxFunc)
target_link_libraries(frame AuxFunc)
target_link_libraries(rotation AuxFunc)

target_link_libraries(main configs AuxFunc rectangle frame rotation)
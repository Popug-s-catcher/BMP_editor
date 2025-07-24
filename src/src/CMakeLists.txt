cmake_minimum_required(VERSION 3.2)

project(bmp_edit)

set(SOURCE_EXE main.c)
set(CONF_DIR config)
set(FUNC_DIR functions)

add_library(configs STATIC ${CONF_DIR}/configs.h ${CONF_DIR}/configs.c)
add_library(AuxFunc STATIC ${CONF_DIR}/AuxFunc.h ${CONF_DIR}/AuxFunc.c)
add_library(rectangle STATIC ${FUNC_DIR}/rectangle.h ${FUNC_DIR}/rectangle.c)
add_library(frame STATIC ${FUNC_DIR}/frame.h ${FUNC_DIR}/frame.c)
add_library(rotation STATIC ${FUNC_DIR}/rotation.h ${FUNC_DIR}/rotation.c)

add_executable(main ${SOURCE_EXE})

target_link_libraries(rectangle AuxFunc)
target_link_libraries(frame AuxFunc)
target_link_libraries(rotation AuxFunc)

target_link_libraries(main configs AuxFunc rectangle frame rotation)
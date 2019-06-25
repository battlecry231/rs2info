cmake_minimum_required(VERSION 2.8)

PROJECT(main)

# - Find OpenNI
set(OPEN_NI2_ROOT "/usr" CACHE 
    FILEPATH "Root directory of OpenNI2")
#set(OPEN_NI2_ROOT "~/Downloads/devel/OpenNI2" CACHE 
#    FILEPATH "Root directory of OpenNI2")
find_library(OpenNI2_LIBRARY NAMES OpenNI2 PATHS 
    "${OPEN_NI2_ROOT}/Bin/x64-Release"
    "${OPEN_NI2_ROOT}/lib"
    "C:/Program Files (x86)/OpenNI2/Lib" 
    "C:/Program Files/OpenNI2/Lib" 
    ${CMAKE_LIB_PATH})

find_path(OpenNI2_INCLUDE_DIR OpenNI.h PATHS 
    "${OPEN_NI2_ROOT}/include/openni2"
    "${OPEN_NI2_ROOT}/include"
    "${OPEN_NI2_ROOT}/Include")


include_directories("${OpenNI2_INCLUDE_DIR}")


add_executable(main main.cpp)

target_link_libraries(  main 
                        OpenNI2
                        )
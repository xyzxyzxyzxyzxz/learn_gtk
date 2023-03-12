cmake_minimum_required(VERSION 3.17)
project(Hello C)


set(CMAKE_C_COMPILER  e:/floder9/msys64/mingw64/bin/gcc.exe)
set(CMAKE_CXX_COMPILER  e:/floder9/msys64/mingw64/bin/g++.exe)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

add_executable(Hello 
        example-1.c)

target_link_libraries(Hello 
        ${GTK4_LIBRARIES})
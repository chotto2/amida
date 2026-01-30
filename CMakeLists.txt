cmake_minimum_required(VERSION 3.16)
project(amida C)

set(CMAKE_C_STANDARD 11)

add_executable(amida src/amida.c)
target_include_directories(amida PRIVATE src)
target_link_libraries(amida gmp m)

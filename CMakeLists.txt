cmake_minimum_required(VERSION 3.3)
project(Lsn11_Example_pthreads)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

set(SOURCE_FILES main.c)
add_executable(pthreads ${SOURCE_FILES})
target_link_libraries(pthreads pthread)
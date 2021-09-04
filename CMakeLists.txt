cmake_minimum_required ( VERSION 3.1.0 )

project(small_rndr)
set (CMAKE_CXX_STANDARD 17)

#Sources
set(RENDERER_SRC
    src/main.cpp)

#Executable
add_executable(small_rndr ${RENDERER_SRC})
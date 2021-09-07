cmake_minimum_required ( VERSION 3.1.0 )

project(small_rndr)
set (CMAKE_CXX_STANDARD 17)

#Sources
set(RENDERER_SRC
    src/main.cpp
    src/vec3.h
    src/color.h
    src/ray.h
    src/hittable.h
    src/sphere.h)

#Executable
add_executable(small_rndr ${RENDERER_SRC})
include_directories(src/)
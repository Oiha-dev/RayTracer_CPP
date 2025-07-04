cmake_minimum_required(VERSION 3.31)
project(RayTracer_CPP)

set(CMAKE_CXX_STANDARD 26)

add_executable(RayTracer_CPP main.cpp
        header/vec3.h
        header/color.h
        header/ray.h
        header/hit.h
        header/sphere.h
        header/world.h
        header/randomUtils.h)

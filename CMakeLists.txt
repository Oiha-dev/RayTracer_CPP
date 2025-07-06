cmake_minimum_required(VERSION 3.31)
project(RayTracer_CPP)

set(CMAKE_CXX_STANDARD 26)

add_executable(RayTracer_CPP main.cpp
        header/vec3.h
        header/color.h
        header/ray.h
        header/hit.h
        header/object.h
        header/world.h
        header/randomUtils.h
        header/camera.h)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(RayTracer_CPP PRIVATE -O3 -march=native -ftree-vectorizer-verbose=2 )
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(RayTracer_CPP PRIVATE /O2 /arch:AVX2 /Qvec-report:2)
endif()
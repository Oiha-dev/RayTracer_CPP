cmake_minimum_required(VERSION 3.31)
project(RayTracer_CPP)

set(CMAKE_CXX_STANDARD 26)

file(GLOB Sources *.cpp)
file(GLOB Headers header/*.h)

include_directories(header)

add_executable(RayTracer_CPP ${Sources})

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(RayTracer_CPP PRIVATE -O3 -march=native -ftree-vectorizer-verbose=2 -flto)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(RayTracer_CPP PRIVATE /O2 /arch:AVX2 /Qvec-report:2)
endif()
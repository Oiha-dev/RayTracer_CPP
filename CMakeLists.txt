cmake_minimum_required(VERSION 3.22)
project(RayTracer_CPP)

set(CMAKE_CXX_STANDARD 23)

file(GLOB Sources *.cpp)

include_directories(header)

add_executable(RayTracer_CPP ${Sources})

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(RayTracer_CPP PRIVATE -O3 -mavx2 -flto -ffunction-sections -fdata-sections -s )
    target_link_options(RayTracer_CPP PRIVATE -static -Wl,--gc-sections -lpthread )
endif()
cmake_minimum_required(VERSION 3.22)
project(MandelbrotExplorer LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
find_package(Threads REQUIRED)

include(FetchContent)
set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON)
FetchContent_MakeAvailable(SFML)

add_executable(mb-explorer src/main.cpp
        src/Mandelbrot.cpp
        src/Mandelbrot.h
        src/VisualComputer.cpp
        src/VisualComputer.h)
target_compile_features(mb-explorer PRIVATE cxx_std_17)
target_link_libraries(mb-explorer PRIVATE SFML::Graphics Threads::Threads)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT mb-explorer)

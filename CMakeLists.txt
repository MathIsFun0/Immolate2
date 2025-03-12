cmake_minimum_required(VERSION 3.10)
project(Immolate LANGUAGES CXX)

# Set C++ standard and required flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define sources for the executable
set(EXECUTABLE_SOURCES
    src/main.cpp
)

# Set optimization flags based on the compiler
if(MSVC)
    set(OPTIMIZATION_FLAGS "/Ox /arch:AVX2")  # AVX2 hardcoded for now, I couldn't get detection to work
else()
    set(OPTIMIZATION_FLAGS "-O3 -g -std=c++20 -Wall -Wextra -Wpedantic -Wno-c++17-extensions -gdwarf-3 -ldl -march=native")  # Full optimization for GCC/Clang, plus debugging info
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAGS}")

# Arm specific flags, todo; properly test this
if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffp-model=fast -fp-model=fast")
endif()

# Output compile_commands.json for clangd stuff
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(immol ${EXECUTABLE_SOURCES})
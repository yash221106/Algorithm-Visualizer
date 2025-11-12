cmake_minimum_required(VERSION 3.16)
project(AlgorithmVisualizer)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Prefer MinGW on Windows if available
if(WIN32 AND NOT DEFINED CMAKE_GENERATOR)
    find_program(MINGW_MAKE mingw32-make.exe)
    if(MINGW_MAKE)
        set(CMAKE_GENERATOR "MinGW Makefiles" CACHE STRING "" FORCE)
    endif()
endif()

# Find SFML 3.x (components must be capitalized)
find_package(SFML 3 COMPONENTS Graphics Window System QUIET)
if(NOT SFML_FOUND)
    # Fallback to SFML 2.x if 3.x is not found
    find_package(SFML 2.6 COMPONENTS Graphics Window System REQUIRED)
endif()

# Add executable
add_executable(AlgorithmVisualizer
    src/main.cpp
    src/Visualizer.cpp
)

# Include directories
target_include_directories(AlgorithmVisualizer PRIVATE include)

# Link SFML libraries using imported targets (SFML 3.x style)
# SFML::Graphics automatically links Window and System
target_link_libraries(AlgorithmVisualizer 
    SFML::Graphics 
    SFML::Window 
    SFML::System
)


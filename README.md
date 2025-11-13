# Algorithm Visualizer

A clean, modular C++ project for visualizing algorithms using SFML 3.x.

/\*
COMMAND TO BUILD AND RUN THE PROJECT

g++ src/_.cpp -o visualizer -std=c++17 -Iinclude -IC:\SFML-3.0.2\include -LC:\SFML-3.0.2\lib -lsfml-graphics -lsfml-window -lsfml-system
_/

## Project Structure

```
AlgorithmVisualizer/
├── CMakeLists.txt
├── src/
│   ├── main.cpp
│   ├── Visualizer.cpp
│   └── algorithms/
│       ├── algorithms.h
│       └── README.md
├── include/
│   └── Visualizer.hpp
└── assets/
    └── README.md
```

## Requirements

- **SFML 3.x** (installed via MSYS2/MinGW)
- **CMake 3.16+**
- **MinGW-w64 with GCC 8+** (or compatible compiler with C++17 support)
- **C++17** standard support

## Building with CMake

### Using MinGW (Recommended for Windows with MSYS2)

```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_CXX_COMPILER=C:/msys64/ucrt64/bin/g++.exe ..
cmake --build .
```

### Using CMake (Auto-detect)

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Building with g++ (Fallback)

If CMake is not available, you can compile directly with g++:

```bash
g++ -std=c++17 -I./include -IC:/msys64/ucrt64/include -o AlgorithmVisualizer.exe src/main.cpp src/Visualizer.cpp -LC:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system
```

**Note:** Replace `C:/msys64/ucrt64` with your actual SFML installation path if different.

## Running

After building, run the executable:

```bash
./AlgorithmVisualizer.exe
```

Or on Windows:

```bash
.\build\AlgorithmVisualizer.exe
```

## Controls

- **R**: Regenerate the array with new random values
- **Close Window**: Click the X button or press Alt+F4

## Features

- Visualizes arrays as vertical bars
- Supports highlighting specific array indices
- Modular design for easy extension
- Ready for algorithm implementations

## Version Compatibility

- **SFML**: 3.x (compatible with MSYS2/MinGW installation)
- **MinGW**: GCC 15.2.0+ (tested with MSYS2 ucrt64)
- **CMake**: 3.16+
- **C++ Standard**: C++17

## Next Steps

- Add sorting algorithms (Bubble Sort, Quick Sort, Merge Sort, etc.)
- Add searching algorithms (Binary Search, Linear Search, etc.)
- Add graph algorithms visualization
- Add animation controls (pause, step, speed)

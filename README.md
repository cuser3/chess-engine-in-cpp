# Chess Engine in C++

A simple chess engine and graphical chessboard built with C++ and SFML. The project allows you to play chess with a graphical interface and is intended as a learning project for C++.

## Features

- Interactive chessboard with SFML graphics
- Basic chess rules and piece movement
- Easy to extend for AI or additional features

## Future Work

- Pawn promotion
- Castling
- AI Chessbot, using simple algorithms like Min/Max or alpha/beta pruning

## Requirements

- [SFML](https://www.sfml-dev.org/) version 3.0.0 (fetched automatically)
- [CMake](https://cmake.org/) version 3.10 or higher (tested with 4.0.2)
- C++ compiler (tested with MSVC 17 2022)

## How to Build

1. **Clone the repository:**
   ```sh
   git clone https://github.com/yourusername/chess-engine-in-cpp.git
   cd chess-engine-in-cpp
   ```

2. **Configure the project with CMake:**
   ```sh
   cmake -S . -B build
   ```

3. **Build the project:**
   ```sh
   cmake --build build --config Debug
   ```

4. **Run the executable:**
   - The binary will be in `build/Debug` or `build/Release` depending on your configuration.

**Note:**  
If you encounter CMake errors related to dependency CMake versions, see the troubleshooting section below.

## Troubleshooting

- If you get errors about `cmake_minimum_required` in dependencies, you may need to manually edit the `CMakeLists.txt` files in `build/_deps/*-src/` to require at least version 3.5.

## References

- Images from [Greenchess](https://greenchess.net/info.php?item=downloads)
- [SFML Documentation](https://www.sfml-dev.org/documentation/3.0.0/)
- [CMake Documentation](https://cmake.org/documentation/)

---



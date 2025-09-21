# 🎮 Tetris (C++ & SDL2)

A modern implementation of the classic **Tetris** game written in **C++** using the **SDL2 library**.  
The goal is to replicate the timeless gameplay mechanics of Tetris while keeping the codebase clean, modular, and beginner-friendly.

---

## ✨ Features
- Classic **Tetris gameplay** with falling tetrominoes
- **Keyboard controls** for movement and rotation
- **Grid system** for piece placement and collision detection
- **Rotations** (left & right) using matrix transformations
- Clear and extensible **object-oriented design**
- Cross-platform (Linux, Windows, macOS)

---

## 🕹 Controls
| Key            | Action                |
|----------------|-----------------------|
| ⬅️ Left Arrow  | Move piece left       |
| ➡️ Right Arrow | Move piece right      |
| ⬆️ Up Arrow    | Rotate piece          |
| ⬇️ Down Arrow  | Soft drop             |
| ⎋ Escape       | Quit game             |

---

## 🛠 Requirements
- C++17 or newer
- [SDL2](https://www.libsdl.org/download-2.0.php)

### Linux (Ubuntu/Debian)
```bash
sudo apt-get install build-essential libsdl2-dev
```

A
## 🛠 Installation

### Arch Linux
```bash
sudo pacman -S sdl2
```


## 🚀 Build Instructions

This project uses **CMake** to configure and build the Tetris game.  

### 1️⃣ Create a Build Directory
It's good practice to build in a separate folder:
```bash
mkdir -p build
cd build
```
### 2️⃣ Generate Build Files
```bash
cmake ..
```
### 3️⃣ Compile the Game
```bash
cmake --build .
```
### 4️⃣ Run the Game
After building, the executable will be inside the build/ directory:
```bash
./Tetris      # Linux / macOS
```

## Notes
- Make sure SDL2 is installed on your system.
- The source files are in src/ and CMake automatically picks them up.
- You can rebuild anytime by running cmake --build . inside the build directory.

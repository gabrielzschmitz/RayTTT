# Installation Guide for TicTacToe

This guide covers how to build and run the TicTacToe game on supported platforms.

---

## Prerequisites

* A C++ compiler toolchain suitable for your platform
* [VSCode](https://code.visualstudio.com/) (optional, for editing and building)

---

## VSCode (All Platforms)

> **Note:** You must have a compiler toolchain installed before building.

1. Open the project folder in VSCode.
2. Run the build task (`Ctrl + Shift + B` or `F5`).
3. The game will compile and run.

---

## Windows

### MinGW-W64 (GCC)

1. Double-click the `build-MinGW-W64.bat` file to prepare the build environment.
2. Open a terminal in the project folder.

   * Use the `W64devkit.exe` terminal if you have not added MinGW-W64 to your PATH.
   * Otherwise, you may use CMD or any other terminal where the MinGW `bin` directory is in your PATH.
3. Run:

   ```bash
   make
   ```
4. The build will complete, and the game will be ready to run.

> **Note:** Use a modern MinGW-W64 (e.g., from [W64devkit releases](https://github.com/skeeto/w64devkit/releases)) or the raylib installer version. Add `C:\raylib\w64devkit\bin` to your PATH if applicable.

> Avoid installing multiple MinGW distributions to prevent conflicts.

---

### Microsoft Visual Studio

1. Run the `build-VisualStudio2022.bat` script.
2. Open the generated `.sln` file in Visual Studio.
3. Build and run the project inside Visual Studio.

---

## Linux

1. Change directory to `build`:

   ```bash
   cd build
   ```
2. Generate Makefiles:

   ```bash
   ./premake5 gmake
   ```
3. Return to the root directory:

   ```bash
   cd ..
   ```
4. (Optional) Build with compilation database support:

   ```bash
   bear -- make VERBOSE=1
   ```
5. Build the project:

   ```bash
   make
   ```
6. The game is ready to run.

---

## macOS

1. Change directory to `build`:

   ```bash
   cd build
   ```
2. Generate Makefiles for macOS:

   ```bash
   ./premake5.osx gmake
   ```
3. Return to the root directory:

   ```bash
   cd ..
   ```
4. Build the project:

   ```bash
   make
   ```
5. The game is ready to run.

---

## Running the Game

After building, execute the game binary located in `bin/Debug`:

```bash
./bin/Debug/Game
```

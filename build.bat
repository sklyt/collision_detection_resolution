@echo off
REM Assumes raylib is installed and in include/lib paths
REM Download raylib from: https://github.com/raysan5/raylib/releases

g++ -std=c++17 main.cpp renderer.cpp debugger.cpp -o collision_test.exe -lraylib -lopengl32 -lgdi32 -lwinmm -I./include

echo Build complete! Run with: collision_test.exe
pause
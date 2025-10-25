#!/bin/bash

# Install raylib if not present
if ! pkg-config --exists raylib; then
    echo "Installing raylib..."
    sudo apt-get update
    sudo apt-get install -y libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev
    
    git clone https://github.com/raysan5/raylib.git
    cd raylib/src
    make PLATFORM=PLATFORM_DESKTOP
    sudo make install
    cd ../..
fi

# Compile
g++ -std=c++17 main.cpp renderer.cpp debugger.cpp -o collision_test -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -I./include

echo "Build complete! Run with: ./collision_test"
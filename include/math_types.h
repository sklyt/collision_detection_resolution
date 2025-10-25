#pragma once
#include <cmath>

struct Vec2 {
    float x, y;
    
    Vec2() : x(0), y(0) {}
    Vec2(float x, float y) : x(x), y(y) {}
    
    /**
     * Operator overloading in C++ allows the redefinition of how standard operators interact with user-defined types (classes or structs). This enables operators like +, -, *, /, ==, <<, >>, and others to work intuitively with custom objects, making the code more readable and expressive.
     */
    Vec2 operator+(const Vec2& other) const { return Vec2(x + other.x, y + other.y); }
    Vec2 operator-(const Vec2& other) const { return Vec2(x - other.x, y - other.y); }
    Vec2 operator*(float scalar) const { return Vec2(x * scalar, y * scalar); }
    
    float Length() const { return std::sqrt(x * x + y * y); }
    Vec2 Normalized() const {
        float len = Length();
        return len > 0 ? Vec2(x / len, y / len) : Vec2(0, 0);
    }
        Vector2 ToRaylib() const { return Vector2{x, y}; }
};
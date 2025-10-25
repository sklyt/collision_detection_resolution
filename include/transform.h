

/**
 * The transform tells us where something is. The collider tells us what space it occupies.
 */


#pragma once
#include "math_types.h"

struct Transform_ {
    Vec2 position;
    
    Transform_() : position(0, 0) {}
    Transform_(const Vec2& pos) : position(pos) {}
    Transform_(float x, float y) : position(x, y) {}
};
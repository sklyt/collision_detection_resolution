#pragma once

/**
 *
 * foundation for broad phase
 * use in rejection test
 * super easy as is just a non rotating box
 *
 *
 * struct Transform {
    Vec2 position;
    // Later: rotation, scale, hierarchy, etc.
};
```

That's it. Position is the center point of our object.

## The AABB Collider

An AABB is defined by its **half-extents** (half-width, half-height from center):
```
    ┌─────────────┐
    │             │ half.y
    │      •──────┤ (position)
    │   half.x    │
    └─────────────┘
```

Why half-extents instead of full width/height? Math convenience. To get the boundaries:
- `min = position - half`
- `max = position + half`

## Overlap Testing: The Core Algorithm

Two AABBs overlap if they overlap on **both axes**. If they're separated on *any* axis, they don't collide.

**The test**:
```
No overlap on X-axis if: box1.max.x < box2.min.x OR box1.min.x > box2.max.x
No overlap on Y-axis if: box1.max.y < box2.min.y OR box1.min.y > box2.max.y

Overlap if: NOT separated on X AND NOT separated on Y
```

Visual:
```
Separated on X:          Overlapping:
┌──┐                     ┌──┐
│A │    ┌──┐             │A─┼─┐
└──┘    │B │             └──┼B│
        └──┘                └─┘
 *
 */

// if one axis fail there's no collision(super fast to test)

#include "math_types.h"
#include "transform.h"

struct AABB
{
    Vec2 halfExtents; // Half-width, half-height

    AABB() : halfExtents(0, 0) {}
    AABB(float halfWidth, float halfHeight) : halfExtents(halfWidth, halfHeight) {}
    AABB(const Vec2 &half) : halfExtents(half) {}

    // Get min/max corners in world space
    Vec2 GetMin(const Transform_ &transform) const
    {
        return transform.position - halfExtents;
    }

    Vec2 GetMax(const Transform_ &transform) const
    {
        return transform.position + halfExtents;
    }

    // Get full width/height
    float GetWidth() const { return halfExtents.x * 2.0f; }
    float GetHeight() const { return halfExtents.y * 2.0f; }

};

namespace Collision {
    
    // Test if two AABBs overlap
    inline bool TestAABBvsAABB(const AABB& a, const Transform_& transformA,
                               const AABB& b, const Transform_& transformB) {
        Vec2 minA = a.GetMin(transformA);
        Vec2 maxA = a.GetMax(transformA);
        Vec2 minB = b.GetMin(transformB);
        Vec2 maxB = b.GetMax(transformB);
        
        // Separated on X-axis?
        if (maxA.x < minB.x || minA.x > maxB.x) return false;
        
        // Separated on Y-axis?
        if (maxA.y < minB.y || minA.y > maxB.y) return false;
        
        // Overlapping on both axes
        return true;
    }
}
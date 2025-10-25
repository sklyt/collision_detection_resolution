#include "renderer.h"
#include "aabb.h"
#include "transform.h"
#include <iostream>

int main() {
    Renderer renderer;
    if (!renderer.Initialize(800, 600, "AABB Collision Test")) {
        return -1;
    }
    
    // Create two boxes
    Transform_ transformA(200, 300);
    AABB aabbA(50, 50);  // 100x100 box
    
    Transform_ transformB(400, 300);
    AABB aabbB(40, 60);  // 80x120 box
    
    // Game loop
    while (!WindowShouldClose()) {
        // Move box B with mouse
        Vector2 mousePos = GetMousePosition();
        transformB.position = Vec2(mousePos.x, mousePos.y);
        
        // Test collision
        bool colliding = Collision::TestAABBvsAABB(aabbA, transformA, aabbB, transformB);
        
        // Render
        renderer.BeginFrame();
        renderer.Clear(Color4(20, 20, 30, 255));
        
        
        // Draw box A (red if colliding, green if not)
       const Color colorA = colliding ? RED : GREEN;
        Vec2 minA = aabbA.GetMin(transformA);
        Vec2 sizeA(aabbA.GetWidth(), aabbA.GetHeight());
        renderer.DrawRectangle(minA, sizeA, colorA);
        
        // Draw box B (always blue)
        Vec2 minB = aabbB.GetMin(transformB);
        Vec2 sizeB(aabbB.GetWidth(), aabbB.GetHeight());
        renderer.DrawRectangle(minB, sizeB, BLUE);
        
        // Draw collision status
        std::string status = colliding ? "COLLIDING" : "NOT COLLIDING";
        renderer.DrawText(status, Vec2(10, 10), 20, BLACK);
        
        renderer.EndFrame();
    }
    
    renderer.Shutdown();
    return 0;
}
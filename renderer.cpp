#include "renderer.h"
#include <iostream>
// #include <resource_manager.h>
#include "debugger.h"

Renderer::Renderer() : width_(0), height_(0), initialized_(false), inTextureMode_(false) {}

Renderer::~Renderer()
{
    if (initialized_)
    {
        Shutdown();
    }

}

void Renderer::UpdateSizeIfNeeded()
{
    if (IsWindowResized())
    {
        width_ = GetScreenWidth();
        height_ = GetScreenHeight();
        Debugger::Instance().LogInfo("Window resized: " + std::to_string(width_) + "x" + std::to_string(height_));
    }

};

bool Renderer::Initialize(int width, int height, const char *title)
{
    width_ = width;
    height_ = height;

    InitWindow(width, height, title);
    // SetTargetFPS(60);

    if (!IsWindowReady())
    {
        Debugger::Instance().LogError("Failed to create window");

        return false;
    }

    initialized_ = true;
    Debugger::Instance().LogInfo("Renderer initialized");
    return true;
}

void Renderer::Shutdown()
{
    if (!initialized_)
        return;

    CloseWindow();
    initialized_ = false;

    Debugger::Instance().LogInfo("Renderer shutdown");
}

void Renderer::BeginFrame()
{
    BeginDrawing();
}

void Renderer::EndFrame()
{
    EndDrawing();
}

void Renderer::Clear(const Color4 &color)
{
    ClearBackground(color.ToRaylib());
}

void Renderer::DrawRectangle(const Vec2 &pos, const Vec2 &size, const Color &color)
{
    ::DrawRectangle((int)pos.x, (int)pos.y, (int)size.x, (int)size.y, color);
}

void Renderer::DrawCircle(const Vec2 &center, float radius, const Color &color)
{
    ::DrawCircle((int)center.x, (int)center.y, radius, color);
}


void Renderer::DrawLine(const Vec2& start, const Vec2& end, const Color& color, float thickness) {
    ::DrawLineEx(
        (Vector2){ start.x, start.y },
        (Vector2){ end.x, end.y },
        thickness,
        color
    );
}

void Renderer::DrawText(const std::string &text, const Vec2 &pos, int fontSize, const Color &color)
{
    ::DrawText(text.c_str(), (int)pos.x, (int)pos.y, fontSize, color);
}


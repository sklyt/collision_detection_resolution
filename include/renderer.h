#pragma once

#include "raylib.h"
#include <string>
#include <cmath>
// #include "resource_manager.h"
#include "math_types.h"
struct Color4
{
    float r, g, b, a;
    Color4(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f)
        : r(r), g(g), b(b), a(a) {}

    Color ToRaylib() const
    {
        return Color{
            (unsigned char)(r * 255),
            (unsigned char)(g * 255),
            (unsigned char)(b * 255),
            (unsigned char)(a * 255)};
    }
};

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool Initialize(int width, int height, const char *title);
    void Shutdown();

    void BeginFrame();
    void EndFrame();
    void Clear(const Color4 &color = Color4(0.1f, 0.1f, 0.1f, 1.0f));
    void UpdateSizeIfNeeded();

    // Basic drawing primitives
    void DrawRectangle(const Vec2 &pos, const Vec2 &size, const Color &color);
    void DrawCircle(const Vec2 &center, float radius, const Color &color);
    void DrawText(const std::string &text, const Vec2 &pos, int fontSize, const Color &color);
    void DrawLine(const Vec2& start, const Vec2& end, const Color& color, float thickness = 1.0f);

    // Texture
    // void DrawTexture(ResourceId textureId, const Vec2 &pos, const Color4 &tint = Color4(1, 1, 1, 1));
    // void DrawTexture(ResourceId textureId, const Vec2 &pos, const Vec2 &size, const Color4 &tint = Color4(1, 1, 1, 1));
    // void DrawTextureRegion(ResourceId textureId, const Vec2 &srcPos, const Vec2 &srcSize,
    //                        const Vec2 &destPos, const Vec2 &destSize, const Color4 &tint = Color4(1, 1, 1, 1));

    // void DrawTextWithFont(const std::string &text, ResourceId fontId, const Vec2 &pos, const Color4 &color);
    // Vec2 MeasureText(const std::string &text, ResourceId fontId);

    // Screen info
    int GetWidth() const { return width_; }
    int GetHeight() const { return height_; }

    // ResourceId CreateRenderTexture(int width, int height);
    // void DestroyRenderTexture(ResourceId id);
    // void SetRenderTarget(ResourceId id);
    // Vec2 GetRenderTextureSize(ResourceId id) const;


    void setTargetFPS(int customFPS){
        SetTargetFPS(customFPS);
    }

private:
    int width_, height_;
    bool initialized_;
    // offscreen rendering for tilemaps
    // std::unordered_map<ResourceId, RenderTexture2D> internalRenderTextures_;
    // ResourceId nextRenderTextureId_;
    // ResourceId currentRenderTargetId_;
    bool inTextureMode_;
};
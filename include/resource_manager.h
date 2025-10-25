#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include <mutex>
#include "raylib.h"

class Resource;
class TextureResource;
class FontResource;

enum class TextureFilterMode
{
    POINT = 0,      // No filter, pixel approximation
    BILINEAR,       // Linear filtering
    TRILINEAR,      // Trilinear filtering (linear with mipmaps)
    ANISOTROPIC_4X, // Anisotropic filtering 4x
    ANISOTROPIC_8X, // Anisotropic filtering 8x
    ANISOTROPIC_16X // Anisotropic filtering 16x
};

using ResourceId = uint32_t;

class ResourceManager
{
public:
    static ResourceManager &Instance();

    ResourceManager();
    ~ResourceManager();

    ResourceId LoadTexture(const std::string &path);
    ResourceId LoadFont(const std::string &path, int fontSize = 32);

    // thread safe -> shared pointers
    std::shared_ptr<TextureResource> GetTexture(ResourceId id);
    std::shared_ptr<FontResource> GetFont(ResourceId id);

    // Resource management
    void UnloadResource(ResourceId id);
    void UnloadAll();
    size_t GetResourceCount() const;

    void PrintResourceStats() const;


private:
    ResourceId GenerateId();

    mutable std::mutex mutex_;
    std::unordered_map<ResourceId, std::shared_ptr<Resource>> resources_;
    std::unordered_map<std::string, ResourceId> pathToId_;
    ResourceId nextId_;

    std::shared_ptr<TextureResource> CreateTextureResource(const std::string &path);
    std::shared_ptr<FontResource> CreateFontResource(const std::string &path, int fontSize);
};

// Resources

class Resource
{
public:
    Resource(ResourceId id, const std::string &path)
        : id_(id), path_(path), loaded_(false) {}
    virtual ~Resource() = default;

    ResourceId GetId() const { return id_; }
    const std::string &GetPath() const { return path_; }
    bool IsLoaded() const { return loaded_; }

    virtual bool Load() = 0;
    virtual void Unload() = 0;
    virtual size_t GetMemoryUsage() const = 0;

protected:
    ResourceId id_;
    std::string path_;
    bool loaded_;
};

enum class TextureWrapMode {
    REPEAT = 0,
    CLAMP,
    MIRROR_REPEAT,
    MIRROR_CLAMP
};

class TextureResource : public Resource
{
public:
    TextureResource(ResourceId id, const std::string &path);
    ~TextureResource() override;

    bool Load() override;
    void Unload() override;
    size_t GetMemoryUsage() const override;

    const Texture2D &GetTexture() const { return texture_; }
    int GetWidth() const { return texture_.width; }
    int GetHeight() const { return texture_.height; }

    void SetTextureFilter(TextureFilterMode filter);
    TextureFilterMode GetCurrentFilter() const { return currentFilter_; }
    void GenerateMipmaps();
    bool HasMipmaps() const { return hasMipmaps_; }
    void SetTextureWrap(TextureWrapMode wrap);

private:
    Texture2D texture_;
    TextureFilterMode currentFilter_ = TextureFilterMode::BILINEAR;
    bool hasMipmaps_ = false;

    // Convert enum to raylib filter mode
    int ConvertToRaylibFilter(TextureFilterMode filter);
};

class FontResource : public Resource
{
public:
    FontResource(ResourceId id, const std::string &path, int fontSize);
    ~FontResource() override;

    bool Load() override;
    void Unload() override;
    size_t GetMemoryUsage() const override;

    const Font &GetFont() const { return font_; }
    int GetFontSize() const { return fontSize_; }

private:
    Font font_;
    int fontSize_;
};
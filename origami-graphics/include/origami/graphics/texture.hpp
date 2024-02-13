#pragma once

#include <origami/core.hpp>
#include <origami/assets.hpp>
#include <origami/gfx.hpp>
#include <string>

enum class TextureFormat : uint32_t
{
    RGB = 6407,
    RGBA = 6408,
    Depth24Stencil8 = 0x88F0,
    Depth32FStencil8 = 0x8CAD,
};

enum class TextureFilter : uint32_t
{
    Nearest = 0x2600,
    Linear = 0x2601,
    NearestMipmapNearest = 0x2700,
    LinearMipmapNearest = 0x2701,
    NearestMipmapLinear = 0x2702,
    LinearMipmapLinear = 0x2703,
};

enum class TextureWrap : uint32_t
{
    Repeat = 0x2901,
    MirroredRepeat = 0x8370,
    ClampToEdge = 0x812F,
    ClampToBorder = 0x812D,
    MirrorClampToEdge = 0x8743,
};

class Texture
{
public:
    static const std::string asset_type;

    glid_t _id;
    int width, height;
    TextureFormat format;
    TextureFilter filter;
    TextureWrap wrap;

    Texture(int width, int height, TextureFormat format, TextureFilter filter = TextureFilter::Linear, TextureWrap wrap = TextureWrap::ClampToEdge, const void *data = nullptr);

    ~Texture();

    void bind(int slot = 0);

    static Texture *load_asset(const std::string &path, AssetManager &assets);
};
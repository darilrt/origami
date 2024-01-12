#pragma once

#include <sokol_gfx.h>
#include <string>

class Image
{
public:
    enum Format
    {
        RGBA8 = SG_PIXELFORMAT_RGBA8,
        R32F = SG_PIXELFORMAT_R32F,
        R16F = SG_PIXELFORMAT_R16F,
        Depth = SG_PIXELFORMAT_DEPTH,
        DepthStencil = SG_PIXELFORMAT_DEPTH_STENCIL,
    };

    enum Usage
    {
        Immutable = SG_USAGE_IMMUTABLE,
        Dynamic = SG_USAGE_DYNAMIC,
        Stream = SG_USAGE_STREAM,
    };

    Image(
        int width,
        int height,
        int num_mipmaps,
        Format format,
        Usage usage = Immutable,
        bool render_target = false,
        const void *data = nullptr);

    ~Image();

    void resize(int width, int height);

    static Image *from_file(const std::string &path);

    static Image *from_memory(const void *data, int width, int height);

    static Image *create_render_target(int width, int height);

    static Image *create_depth_target(int width, int height);

    sg_image image = {0};

private:
    Format format;
    Usage usage;
    int width;
    int height;
    int num_mipmaps;
    bool render_target;

    Image() = default;
};
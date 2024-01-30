#pragma once

#include <string>

class ImageOld
{
public:
    enum Format
    {
        RGBA8,
        R32F,
        R16F,
        Depth,
        DepthStencil,
    };

    enum Usage
    {
        Immutable,
        Dynamic,
        Stream,
    };

    ImageOld(
        int width,
        int height,
        int num_mipmaps,
        Format format,
        Usage usage = Immutable,
        bool render_target = false,
        const void *data = nullptr);

    ~ImageOld();

    void resize(int width, int height);

    static ImageOld *from_file(const std::string &path);

    static ImageOld *from_memory(const void *data, int width, int height);

    static ImageOld *create_render_target(int width, int height);

    static ImageOld *create_depth_target(int width, int height);

private:
    Format format;
    Usage usage;
    int width;
    int height;
    int num_mipmaps;
    bool render_target;

    ImageOld() = default;
};
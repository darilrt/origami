#include <GL/glew.hpp>
#include <GL/gl.h>

#include <origami/core.hpp>
#include <origami/gfx.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "origami/graphics/texture.hpp"
#include "origami/graphics/graphics_system.hpp"

const std::string Texture::asset_type = "Graphics/Texture";

Texture::Texture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrap wrap, const void *data)
    : width(width), height(height), format(format), filter(filter), wrap(wrap)
{
    GL_CALL(glGenTextures(1, &_id));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, _id));

    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLenum>(wrap)));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLenum>(wrap)));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(filter)));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(filter)));

    GLuint type = GL_UNSIGNED_BYTE;
    GLuint internal_format = static_cast<GLenum>(format);

    if (format == TextureFormat::Depth)
    {
        type = GL_FLOAT;
        internal_format = GL_DEPTH_COMPONENT32F;
    }

    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLenum>(internal_format), width, height, 0, static_cast<GLenum>(format), type, data));
}

Texture::~Texture()
{
    GL_CALL(glDeleteTextures(1, &_id));
}

void Texture::bind(int slot)
{
    GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, _id));
}

void Texture::generate_mipmaps()
{
    GL_CALL(glBindTexture(GL_TEXTURE_2D, _id));
    GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
}

Texture *Texture::load_asset(const std::string &path, AssetManager &assets)
{
    int tex_width, tex_height, tex_channels;

    stbi_uc *pixels = stbi_load(path.c_str(), &tex_width, &tex_height, &tex_channels, STBI_rgb_alpha);

    if (!pixels)
    {
        throw std::runtime_error("Failed to load texture image " + path);
    }

    Texture *texture = new Texture(
        tex_width, tex_height,
        TextureFormat::RGBA,
        TextureFilter::Linear,
        TextureWrap::Repeat,
        pixels);

    texture->generate_mipmaps();

    stbi_image_free(pixels);

    return texture;
}
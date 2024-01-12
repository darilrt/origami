#include <origami/math.hpp>
#include <sokol_gfx.h>

#include "origami/graphics/render_pass.hpp"

RenderPass::RenderPass(int width, int height)
{
    resize(width, height);
}

RenderPass::~RenderPass()
{
    sg_destroy_pass(this->pass);
}

void RenderPass::resize(int width, int height)
{
    sg_pass_desc desc = {0};
    this->action = {0};

    this->albedo_attachment = new_shared<Image>(width, height, 1, Image::RGBA8, Image::Immutable, true, nullptr);
    desc.color_attachments[0] = {.image = this->albedo_attachment->image};
    this->action.colors[0] = {
        .load_action = SG_LOADACTION_CLEAR,
        .clear_value = {clear_color.x, clear_color.y, clear_color.z, clear_color.w},
    };

    this->normal_ao_attachment = new_shared<Image>(width, height, 1, Image::RGBA8, Image::Immutable, true, nullptr);
    desc.color_attachments[1] = {.image = this->normal_ao_attachment->image};
    this->action.colors[1] = {
        .load_action = SG_LOADACTION_CLEAR,
        .clear_value = {0.0f, 0.0f, 0.0f, 1.0f},
    };

    this->position_roughness_attachment = new_shared<Image>(width, height, 1, Image::RGBA8, Image::Immutable, true, nullptr);
    desc.color_attachments[2] = {.image = this->position_roughness_attachment->image};
    this->action.colors[2] = {
        .load_action = SG_LOADACTION_CLEAR,
        .clear_value = {0.0f, 0.0f, 0.0f, 1.0f},
    };

    this->emissive_metallic_attachment = new_shared<Image>(width, height, 1, Image::RGBA8, Image::Immutable, true, nullptr);
    desc.color_attachments[3] = {.image = this->emissive_metallic_attachment->image};
    this->action.colors[3] = {
        .load_action = SG_LOADACTION_CLEAR,
        .clear_value = {0.0f, 0.0f, 0.0f, 1.0f},
    };

    this->depth_attachment = Shared<Image>(Image::create_depth_target(width, height));
    desc.depth_stencil_attachment.image = this->depth_attachment->image;
    this->action.depth = {
        .load_action = SG_LOADACTION_CLEAR,
        .store_action = _SG_STOREACTION_DEFAULT,
        .clear_value = 1.0f,
    };

    if (this->pass.id != SG_INVALID_ID)
        sg_destroy_pass(this->pass);

    this->pass = sg_make_pass(&desc);
}

void RenderPass::set_clear_color(Vec4 color)
{
    this->clear_color = color;
    this->action.colors[0].clear_value = {color.x, color.y, color.z, color.w};
}
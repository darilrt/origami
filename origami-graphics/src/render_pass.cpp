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
    this->color_attachment = Shared<Image>(Image::create_render_target(width, height));
    this->depth_attachment = Shared<Image>(Image::create_depth_target(width, height));

    sg_pass_desc desc = {0};

    desc.color_attachments[0] = {
        .image = this->color_attachment->image,
    };

    desc.depth_stencil_attachment.image = this->depth_attachment->image;

    if (this->pass.id != SG_INVALID_ID)
        sg_destroy_pass(this->pass);

    this->pass = sg_make_pass(&desc);

    this->action = {0};

    this->action.colors[0] = {
        .load_action = SG_LOADACTION_CLEAR,
        .clear_value = {clear_color.x, clear_color.y, clear_color.z, clear_color.w},
    };

    this->action.depth = {
        .load_action = SG_LOADACTION_CLEAR,
        .store_action = SG_STOREACTION_DONTCARE,
        .clear_value = 1.0f,
    };
}
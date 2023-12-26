#include <SDL2/SDL.h>
#include <sokol_gfx.h>
#include <sokol_log.h>
#include <cassert>

#include <origami/math.h>

struct
{
    sg_pass_action action;
    sg_pipeline pip;
    sg_bindings bind;
} state;

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_LoadLibrary(NULL);
    SDL_GL_SetSwapInterval(0);

    SDL_Window *window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    SDL_Event event;
    bool running = true;

    sg_desc desc = sg_desc{
        .logger = slog_func,
    };
    sg_setup(&desc);
    assert(sg_isvalid());

    state.action.colors[0].load_action = SG_LOADACTION_CLEAR;
    state.action.colors[0].clear_value = {0.1f, 0.1f, 0.1f, 1.0f};

    struct
    {
        Vec3 position;
        Vec4 color;
    } quad_vertices[] = {
        {Vec3{0.0f, 0.5f, 0.0f}, Vec4{1.0f, 0.0f, 0.0f, 1.0f}},
        {Vec3{0.5f, -0.5f, 0.0f}, Vec4{0.0f, 1.0f, 0.0f, 1.0f}},
        {Vec3{-0.5f, -0.5f, 0.0f}, Vec4{0.0f, 0.0f, 1.0f, 1.0f}},
    };

    uint16_t quad_indices[] = {0, 1, 2};

    state.bind.vertex_buffers[0] = sg_make_buffer(sg_buffer_desc{
        .data = SG_RANGE(quad_vertices),
        .label = "quad-vertices",
    });
    state.bind.index_buffer = sg_make_buffer(sg_buffer_desc{
        .type = SG_BUFFERTYPE_INDEXBUFFER,
        .data = SG_RANGE(quad_indices),
        .label = "quad-indices",
    });

    sg_shader shd = sg_make_shader(sg_shader_desc{
        .vs = {
            .source = (const char *)R"(
                #version 330
                layout(location = 0) in vec3 aPos;
                layout(location = 1) in vec4 aColor;
                out vec4 vColor;
                void main() {
                    gl_Position = vec4(aPos, 1.0);
                    vColor = aColor;
                }
            )",
        },
        .fs = {
            .source = (const char *)R"(
                #version 330
                in vec4 vColor;
                out vec4 fragColor;
                void main() {
                    fragColor = vColor;
                }
            )",
        },
    });

    sg_pipeline_desc pip_desc = {0};
    pip_desc.shader = shd;
    pip_desc.index_type = SG_INDEXTYPE_UINT16;
    pip_desc.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT3;
    pip_desc.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT4;

    state.pip = sg_make_pipeline(pip_desc);

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        sg_begin_default_pass(&state.action, 640, 480);

        sg_apply_pipeline(state.pip);
        sg_apply_bindings(&state.bind);
        sg_draw(0, 3, 1);

        sg_end_pass();

        sg_commit();
        SDL_GL_SwapWindow(window);
    }

    sg_shutdown();
    return 0;
}

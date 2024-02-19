#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include "origami/window.hpp"

void Window::init(EngineState &state)
{
    SDL_GLContext context;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetSwapInterval(1);

    window = SDL_CreateWindow("Origami", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x, size.y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    context = SDL_GL_CreateContext((SDL_Window *)window);
    if (window == nullptr)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
}

void Window::run(EngineState &state)
{
    auto window_id = SDL_GetWindowID((SDL_Window *)window);
    auto &es = state.get_resource<EventSystem>();
    SDL_Event event;
    bool is_running = true;
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    float delta_time = 0;
    float life_time = 0;

    es.emit<PreStart>();
    es.emit<Start>();

    SDL_SetWindowPosition((SDL_Window *)window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    while (is_running)
    {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        delta_time = (float)((NOW - LAST) / (float)SDL_GetPerformanceFrequency());
        life_time += delta_time;

        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                es.emit<WindowClose>();
                is_running = false;
            }
            else if (event.type == SDL_WINDOWEVENT && event.window.windowID == window_id)
            {
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_RESIZED:
                    es.emit<WindowResize>({
                        .width = event.window.data1,
                        .height = event.window.data2,
                    });
                    break;
                }
            }
            else if (event.type == SDL_KEYDOWN)
            {
                es.emit<KeyDown>({
                    .key_code = (KeyCode)event.key.keysym.scancode,
                });
            }
            else if (event.type == SDL_KEYUP)
            {
                es.emit<KeyUp>({
                    .key_code = (KeyCode)event.key.keysym.scancode,
                });
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                es.emit<MouseButtonDown>({
                    .button = (MouseButton)event.button.button,
                });
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                es.emit<MouseButtonUp>({
                    .button = (MouseButton)event.button.button,
                });
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                es.emit<MouseMove>({
                    .x = event.motion.x,
                    .y = event.motion.y,
                    .dx = event.motion.xrel,
                    .dy = event.motion.yrel,
                });
            }
            else if (event.type == SDL_MOUSEWHEEL)
            {
                es.emit<MouseScroll>({
                    .x = event.wheel.x,
                    .y = event.wheel.y,
                });
            }
        }

        es.emit<PreUpdate>();
        es.emit(Update{
            .delta_time = delta_time,
            .life_time = life_time,
        });
        es.emit<PostUpdate>();
        es.emit<Render>();

        SDL_GL_SwapWindow((SDL_Window *)window);
    }
}

void Window::set_size(Vec2 size)
{
    this->size = size;
    SDL_SetWindowSize((SDL_Window *)window, size.x, size.y);
}

void Window::set_title(const std::string &title)
{
    SDL_SetWindowTitle((SDL_Window *)window, title.c_str());
}

void Window::set_vsync(bool vsync)
{
    SDL_GL_SetSwapInterval(vsync ? 1 : 0);
}

void Window::set_fullscreen(bool fullscreen)
{
    SDL_SetWindowFullscreen((SDL_Window *)window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
}

void Window::create_surface_khr(void *instance, void *surface)
{
    SDL_bool result = SDL_Vulkan_CreateSurface(
        (SDL_Window *)window,
        (VkInstance)instance,
        (VkSurfaceKHR *)surface);

    if (result != SDL_TRUE)
    {
        throw std::runtime_error("Window::create_surface_khr: Failed to create Vulkan surface");
    }
}

std::vector<const char *> Window::get_required_extensions()
{
    unsigned int count;
    SDL_Vulkan_GetInstanceExtensions((SDL_Window *)window, &count, nullptr);

    std::vector<const char *> extensions(count);
    SDL_Vulkan_GetInstanceExtensions((SDL_Window *)window, &count, extensions.data());

    return extensions;
}
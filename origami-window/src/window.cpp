#include <iostream>
#include <SDL2/SDL.h>

#include "origami/window.hpp"

void Window::init(EngineState &state)
{
    SDL_GLContext context;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetSwapInterval(1);

    window = SDL_CreateWindow("Origami", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.x, size.y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    context = SDL_GL_CreateContext((SDL_Window *)window);
    if (context == nullptr)
    {
        std::cerr << "OpenGL context could not be created! SDL_Error: " << SDL_GetError() << std::endl;
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

    es.emit<Start>();
    while (is_running)
    {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        delta_time = (float)((NOW - LAST) / (float)SDL_GetPerformanceFrequency());

        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                is_running = false;
            }
            else if (event.type == SDL_WINDOWEVENT && event.window.windowID == window_id)
            {
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    is_running = false;
            }
        }

        es.emit<PreUpdate>();
        es.emit(Update{
            .delta_time = delta_time,
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

void Window::set_title(const char *title)
{
    SDL_SetWindowTitle((SDL_Window *)window, title);
}

void Window::set_vsync(bool vsync)
{
    SDL_GL_SetSwapInterval(vsync ? 1 : 0);
}
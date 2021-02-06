#pragma once

#include <SDL2/SDL.h>

#include "memory.h"

namespace gui {
    using namespace foundation;

    struct Gui {
        Gui(Allocator &allocator, SDL_Renderer *renderer);

        Allocator &allocator;
    };

    /**
     * @brief Updates the gui
     *
     * @param gui The gui to update
     * @param t The current time
     * @param dt The delta time since last update
     */
    void update(Gui &gui, uint32_t t, double dt);

    /**
     * @brief Renders the gui
     *
     * @param gui The gui to render
     * @param renderer The SDL renderer.
     */
    void render(Gui &gui, SDL_Renderer *renderer);
}

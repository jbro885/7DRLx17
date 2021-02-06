#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#include "hash.h"
#include "array.h"
#include "memory.h"
#include "texture.h"

// The namespace for all of the game world specific gameplay code.
namespace world {
    using namespace foundation;

    // Max width of the world.
    static const uint64_t Max_Width = 128;

    // Max height of the world.
    static const uint64_t Max_Height = 128;

    /**
     * @brief A tile struct.
     * 
     */
    struct Tile {
        int index = 0;
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        double angle = 0.0;
    };

    /**
     * @brief An enum that describes a specific game state.
     * 
     */
    enum class GameState {
        // Game state is creating, or loading from a save.
        Initializing,

        // Generating a dungeon level.
        DunGen,

        // Playing the game.
        Playing,
    };

    // The game world.
    struct World {
        World(Allocator &allocator, SDL_Renderer *renderer, const char *atlas_config_filename);
        ~World();

        // The allocator
        Allocator &allocator;

        // The current game state.
        GameState game_state;

        // The thread for generating a dungeon.
        SDL_Thread *dungen_thread;

        // The texture atlas
        texture::Atlas *atlas;

        // The camera x and y offset
        int x_offset, y_offset;

        // The The hash of tile states.
        Hash<Tile> tiles;
    };


    /**
     * @brief Updates the world
     *
     * @param world The world to update
     * @param t The current time
     * @param dt The delta time since last update
     */
    void update(World &world, uint32_t t, double dt);

    /**
     * @brief Renders the world
     *
     * @param world The world to render
     * @param renderer The SDL renderer.
     */
    void render(World &world, SDL_Renderer *renderer);

    /**
     * @brief Returns the index of an x, y coordinate
     * 
     * @param x The x coord
     * @param y The y coord
     * @param max_width The maxium width.
     * @return constexpr uint64_t The index.
     */
    constexpr uint64_t index(uint64_t const x, uint64_t const y, uint64_t max_width) {
        return x + max_width * y;
    }

    /**
     * @brief Calculates the x, y coordinates based on an index.
     * 
     * @param index The index.
     * @param x The pass-by-reference x coord to calculate.
     * @param y The pass-by-reference y coord to calculate.
     * @param max_width The maxium width.
     */
    constexpr void coord(uint64_t const index, uint64_t &x, uint64_t &y, uint64_t max_width) {
        x = index % max_width;
        y = index / max_width;
    }
}

#ifndef COLOURS_HPP
#define COLOURS_HPP

#include <SDL2/SDL.h>

namespace Colours {
    // RGBA Colours
    const SDL_Color White = {255, 255, 255, 255};
    const SDL_Color Black = {0, 0, 0, 255};
    const SDL_Color Red = {255, 0, 0, 255};
    const SDL_Color Green = {0, 255, 0, 255};
    const SDL_Color Blue = {0, 0, 255, 255};
    const SDL_Color Yellow = {255, 255, 0, 255};
    const SDL_Color Cyan = {0, 255, 255, 255};
    const SDL_Color Magenta = {255, 0, 255, 255};
}

#endif 

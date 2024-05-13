#ifndef COLOURS_HPP
#define COLOURS_HPP

#include <SDL2/SDL.h>
#include <string.h>

namespace Colours
{
    // RGBA Colours
    const SDL_Color White = {255, 255, 255, 255};
    const SDL_Color Black = {0, 0, 0, 255};
    const SDL_Color Red = {255, 0, 0, 255};
    const SDL_Color Orange = {255, 165, 0, 255};
    const SDL_Color Green = {0, 255, 0, 255};
    const SDL_Color Blue = {0, 0, 255, 255};
    const SDL_Color Yellow = {255, 255, 0, 255};
    const SDL_Color Cyan = {0, 255, 255, 255};
    const SDL_Color LightBlue = {135, 206, 250, 255};
    const SDL_Color Pink = {255, 105, 180, 255};
    const SDL_Color Purple = {128, 0, 128, 255};
}

#endif

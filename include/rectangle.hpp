#ifndef RECTANGULAR_BRICK_HPP
#define RECTANGULAR_BRICK_HPP

#include "brick.hpp"

class RectangularBrick : public Brick {
public:
    RectangularBrick(int x, int y, int width, int height, int durability) : Brick(x, y, width, height, durability) {}

    void draw(SDL_Renderer* renderer) const override {
        SDL_Rect rect = {m_x, m_y, m_width, m_height};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Couleur rouge
        SDL_RenderFillRect(renderer, &rect);
    }
};

#endif // RECTANGULAR_BRICK_HPP

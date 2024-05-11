#ifndef BONUS_HPP
#define BONUS_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include "colour.hpp"

enum BonusType
{
    PaddleSizeIncrease,
    PaddleSizeDecrease,
    BallSpeedIncrease,
    BallDuplication,
    BallSizeIncrease,
    BallSizeDecrease,
    BallExtraLife,
    BallExtraScore
};

class Bonus 
{
public:
    Bonus(int x, int y, int width, int height, int type) : m_x(x), m_y(y), m_width(width), m_height(height), m_type(type) {}
    ~Bonus() {}
    void draw(SDL_Renderer *renderer) const
    {
        SDL_Rect rect = {m_x, m_y, m_width, m_height};
        SDL_Color c = Colours::Purple;
        SDL_SetRenderDrawColor(renderer,c.r, c.g, c.b, c.a); // Couleur bleue
        SDL_RenderFillRect(renderer, &rect);
    }

    int update(float deltaTime)
    {
        m_y += 100 * deltaTime;
        return m_y;
    }


    // Getters
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    int getType() const { return m_type; }

protected:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    int m_type;
};

#endif // BONUS_HPP

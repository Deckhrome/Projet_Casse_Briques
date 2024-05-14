#ifndef BONUS_HPP
#define BONUS_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include "colour.hpp"
enum BonusType
{
    // Good bonuses
    PaddleSizeIncrease,
    BallDuplication,
    BallSizeIncrease,
    BallExtraLife,
    BallExtraScore,
    // Bad bonuses
    BallSpeedIncrease,
    BallSizeDecrease,
    PaddleSizeDecrease
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
        if (m_type == BonusType::PaddleSizeIncrease)
        {
            c = Colours::Green;
        }
        else if (m_type == BonusType::BallDuplication)
        {
            c = Colours::Yellow;
        }
        else if (m_type == BonusType::BallSizeIncrease)
        {
            c = Colours::Blue;
        }
        else if (m_type == BonusType::BallExtraLife)
        {
            c = Colours::Red;
        }
        else if (m_type == BonusType::BallExtraScore)
        {
            c = Colours::Orange;
        }
        else if (m_type == BonusType::BallSpeedIncrease)
        {
            c = Colours::Black;
        }
        else if (m_type == BonusType::BallSizeDecrease)
        {
            c = Colours::White;
        }
        else if (m_type == BonusType::PaddleSizeDecrease)
        {
            c = Colours::Pink;
        }
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a); // Couleur bleue
        SDL_RenderFillRect(renderer, &rect);
    }

    int update(float deltaTime)
    {
        m_y += 100 * deltaTime;
        return m_y;
    }

    bool isActive() const { return m_active; }

    void setActive(bool active) { m_active = active; }

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
    bool m_active = true;
};

#endif // BONUS_HPP

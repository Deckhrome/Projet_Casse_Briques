#ifndef BRICK_HPP
#define BRICK_HPP

#include "colour.hpp"

class Brick
{
public:
    Brick(int x, int y, int width, int height, int durability) : m_x(x), m_y(y), m_width(width), m_height(height), m_durability(durability) {}

    // peut être une fonctionnalité du jeu
    // void update(float deltaTime) {}

    void draw(SDL_Renderer *renderer) const
    {
        SDL_Rect rect = {m_x, m_y, m_width, m_height};
        SDL_Color c = getColour();
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
        SDL_RenderFillRect(renderer, &rect);
    }

    // Getters
    int getDurability() const
    {
        return m_durability;
    }

    void setDurability(int newDurability) { m_durability = newDurability; }

    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

protected:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    int m_durability;

    // Colour depending on the durability
    SDL_Color getColour() const
    {
        if (m_durability > 50)
        {
            return Colours::Green;
        }
        else if (m_durability > 30)
        {
            return Colours::Yellow;
        }
        else if (m_durability > 10)
        {
            return Colours::Orange;
        }
        else
        {
            return Colours::Red;
        }
    }
};

#endif

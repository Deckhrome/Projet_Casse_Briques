#ifndef BRICK_HPP
#define BRICK_HPP

#include "gameObject.hpp"
#include "colours.hpp"

class Brick : public GameObject {
public:
    Brick(int x, int y, int width, int height, int durability) : m_x(x), m_y(y), m_width(width), m_height(height), m_durability(durability) {}

    // peut être une fonctionnalité du jeu
    // void update(float deltaTime) override {}
    
    void draw(SDL_Renderer* renderer) const override {
        SDL_Rect rect = {m_x, m_y, m_width, m_height};
        SDL_SetRenderDrawColor(renderer, Colours::Red.r, Colours::Red.g, Colours::Red.b, Colours::Red.a);
        SDL_RenderFillRect(renderer, &rect);
    }   

    int getDurability() const {
        return m_durability;
    }

protected:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    int m_durability;
};

#endif // BRICK_HPP

#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "SDL2/SDL.h"
#include "bonus.hpp"

class Paddle
{
public:
    // Constructor
    Paddle(int x, int y, int width, int height, int screenWidth, int screenHeight) : m_x(x), m_y(y), m_width(width), m_height(height), m_screenWidth(screenWidth), m_screenHeight(screenHeight), m_velocity(0) {}
    ~Paddle() {}

    // Update
    void update(float deltaTime);

    // Draw
    void drawPaddle(SDL_Renderer *renderer) const;

    // handleInput
    void handleInput(SDL_Event &event, int screenWidth);

    // Getters
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    int getX() const { return m_x; }
    int getY() const { return m_y; }

    // Setters
    void setX(int x) { m_x = x; }
    void setY(int y) { m_y = y; }
    void setWidth(int width) { m_width = width; }
    void setHeight(int height) { m_height = height; }

    // Reset position
    void resetPaddle();

private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    int m_screenWidth;
    int m_screenHeight;
    int m_velocity;

    static constexpr int PADDLE_SPEED = 300;
};

#endif
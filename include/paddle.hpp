#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "SDL2/SDL.h"

class Paddle {
public:
    // Constructor
    Paddle(int x, int y,int width, int height, int screenWidth) :
    m_x(x), m_y(y), m_width(width), m_height(height), m_screenWidth(screenWidth), m_velocity(0) {}
    ~Paddle(){}
    // Update
    void update(float deltaTime);
    // Draw
    void drawPaddle(SDL_Renderer * renderer) const;
    // handleInput
    void handleInput(SDL_Event& event);
    // Getters
    int getWidth() const {return m_width;}
    int getHeight() const {return m_height;}
    int getX() const {return m_x;}
    int getY() const {return m_y;}
private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    int m_screenWidth; // to know the screen limit
    int m_velocity;

    static constexpr int PADDLE_SPEED = 300;
};



#endif
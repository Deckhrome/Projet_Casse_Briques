#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "gameObject.hpp"

class Paddle : public GameObject
{
public:
    // Constructor
    Paddle(int x, int y,int width, int height, int screenWidth) :
    m_x(x), m_y(y), m_width(width), m_height(height), m_screenWidth(screenWidth), m_velocity(0) {}
    ~Paddle(){}
    // Update
    void update(float deltaTime) override;
    // Draw
    void draw(SDL_Renderer * renderer) const override;
    // handleInput
    void handleInput(SDL_Event& event) override;
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
#ifndef BALL_HPP
#define BALL_HPP

#include "paddle.hpp"
#include "bricks.hpp"
#include <memory> // Inclure la bibliothèque pour std::unique_ptr

class Ball {
public:
    // Constructeur
    Ball(int radius, int initialX, int initialY, int screenWidth, int screenHeight);

    // Méthodes héritées de GameObject
    void update(float deltaTime, Paddle paddle, Bricks& bricks);
    void drawBall(SDL_Renderer* renderer) const ;
    void handleInput(SDL_Event& event);

    // Handle every type of collision
    void handleCollisionsBorder(int windowWidth, int windowHeight);
    void handleCollisionsPaddle(Paddle paddle);
    void handleCollisionsBricks(Bricks& bricks); 

    // Getter
    int getX() const { return m_x; }
    int getY() const { return m_y; }

    // Reset position
    void reset();

private:
    int m_radius;
    int m_x;               
    int m_y;
    int m_velocity;             
    int m_velocityX;       
    int m_velocityY;       
    int m_screenWidth;     
    int m_screenHeight;
};

#endif

#ifndef BALL_HPP
#define BALL_HPP

#include "vector2D.hpp"
#include "paddle.hpp"
#include "bricks.hpp"
#include "gameStatus.hpp"
#include "bonuses.hpp"
#include <memory> // Inclure la bibliothèque pour std::unique_ptr

class Ball
{
public:
    // Constructeur
    Ball(int radius, int initialX, int initialY, int screenWidth, int screenHeight);

    // Méthodes héritées de GameObject
    void update(float deltaTime, Paddle paddle, Bricks &bricks, Bonuses &bonuses, GameStatus &gameStatus);
    void drawBall(SDL_Renderer *renderer) const;
    void handleInput(SDL_Event &event);

    // Handle every type of collision
    void handleCollisionsBorder(int windowWidth, int windowHeight, GameStatus &gameStatus);
    void handleCollisionsPaddle(Paddle paddle);
    void handleCollisionsBricks(Bricks &bricks, Bonuses &bonuses, GameStatus &gameStatus);
    void handleCollisionsBonuses(Bonuses &bonuses, Paddle &paddle, GameStatus &gameStatus);

    // Getters
    int getRadius() const { return m_radius; }
    Vector2D getPosition() const { return m_position; }

    // Reset position
    void resetBall();

private:
    int m_radius;
    Vector2D m_position;
    Vector2D m_velocity;
    int m_screenWidth;
    int m_screenHeight;
    int m_updateCounter;
    bool m_justCollide;
    float m_velocityRatio;
};

#endif

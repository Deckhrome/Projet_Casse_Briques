#ifndef BALLS_HPP
#define BALLS_HPP

#include <vector>
#include "ball.hpp"
#include "paddle.hpp"
#include "bricks.hpp"
#include "gameStatus.hpp"
#include "bonuses.hpp"

class Balls
{
public:
    // Constructor
    Balls(int ball_radius, int start_x, int start_y, int screen_width, int screen_height) : m_ballRadius(ball_radius),
                                                                                            m_startX(start_x),
                                                                                            m_startY(start_y),
                                                                                            m_screenWidth(screen_width),
                                                                                            m_screenHeight(screen_height) {}

    // Destructor
    ~Balls()
    {
        balls.clear();
    }

    // Method to add a ball to the vector
    void addBall(const Ball &ball)
    {
        balls.push_back(ball);
    }

    // Method to remove a ball from the vector
    void removeBall(int index)
    {
        balls.erase(balls.begin() + index);
    }

    // Method to get the number of balls
    int getNumBalls() const
    {
        return balls.size();
    }

    // Method to get a specific ball by index
    Ball &getBall(int index)
    {
        return balls[index];
    }

    // Method to update all balls
    void update(float deltaTime, Paddle paddle, Bricks &bricks, Bonuses &bonuses, GameStatus &gameStatus)
    {
        size_t size = balls.size();
        if (size == 0)
        {
            resetBalls();
            return;
        }
        for (size_t i = 0; i < size; i++)
        {
            balls[i].updatePosition(deltaTime);
            balls[i].handleCollisionsPaddle(paddle);
            balls[i].handleCollisionsBricks(bricks, bonuses, gameStatus);
            if (balls[i].handleCollisionsBorder(m_screenWidth, m_screenHeight, gameStatus))
            {
                removeBall(i);
                std::cout << "Remove ball :" << i << std::endl;
            }
        }
    }

    // Change Radius of all ball
    void changeRadius(int radius)
    {
        for (Ball &ball : balls)
        {
            ball.setRadius(radius);
        }
    }

    // Change Velocity Ratio of all ball
    void changeVelocityRatio(float velocityRatio)
    {
        for (Ball &ball : balls)
        {
            ball.setVelocityRatio(velocityRatio);
        }
    }

    // Method to draw all balls
    void drawBalls(SDL_Renderer *renderer) const
    {
        for (const Ball &ball : balls)
        {
            ball.drawBall(renderer);
        }
    }

    // Method to reset all balls
    void resetBalls()
    {
        balls.clear();
        Ball ball(m_ballRadius, m_startX, m_startY, m_screenWidth, m_screenHeight);
        addBall(ball);
    }

private:
    std::vector<Ball> balls; // Vector to store the balls
    int m_ballRadius;
    int m_startX;
    int m_startY;
    int m_screenWidth;
    int m_screenHeight;
};

#endif // BALLS_HPP
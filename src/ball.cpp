#include <cmath>
#include <math.h>
#include <algorithm>
#include "../include/ball.hpp"
#include "../include/colour.hpp"

#define VELOCITY 600
#define RANGE_ANGLE 4
#define STARTING_ANGLE (M_PI / 4)

Ball::Ball(int radius, int initialX, int initialY, int screenWidth, int screenHeight) : m_radius(radius),
                                                                                        m_x(initialX),
                                                                                        m_y(initialY),
                                                                                        m_velocity(VELOCITY),
                                                                                        m_velocityX(0),
                                                                                        m_velocityY(m_velocity),
                                                                                        m_screenWidth(screenWidth),
                                                                                        m_screenHeight(screenHeight) {}

void Ball::update(float deltaTime, Paddle paddle, Bricks &bricks)
{
    m_x += static_cast<int>(m_velocityX * deltaTime);
    m_y += static_cast<int>(m_velocityY * deltaTime);
    // Handle collision
    handleCollisionsBorder(m_screenWidth, m_screenHeight);
    handleCollisionsPaddle(paddle);
    handleCollisionsBricks(bricks);
}

void Ball::handleInput(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
    {
        this->reset();
    }
}

void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius)
{
    for (int x = -radius; x <= radius; ++x)
    {
        int height = static_cast<int>(std::sqrt(radius * radius - x * x));
        SDL_RenderDrawLine(renderer, centerX + x, centerY - height, centerX + x, centerY + height);
    }
}

void Ball::drawBall(SDL_Renderer *renderer) const
{
    SDL_SetRenderDrawColor(renderer, Colours::Red.r, Colours::Red.g, Colours::Red.b, Colours::Red.a);
    drawCircle(renderer, m_x, m_y, m_radius);
}

#include "ball.hpp"
#include "bricks.hpp"

void Ball::handleCollisionsBricks(Bricks &bricks)
{
    // Get all bricks
    const std::vector<Brick> &allBricks = bricks.getAllBricks();

    // Browse all bricks
    for (size_t i = 0; i < allBricks.size(); ++i)
    {
        const Brick &brick = allBricks[i];

        // Already destroyed
        if (brick.getDurability() <= 0)
        {
            continue;
        }
        // Verify collision on each sides
        if (m_x + m_radius >= brick.getX() && m_x - m_radius <= brick.getX() + brick.getWidth() &&
            m_y + m_radius >= brick.getY() && m_y - m_radius <= brick.getY() + brick.getHeight())
        {
            // Collision detected

            // Calcul every overlap
            double overlapLeft = m_x + m_radius - brick.getX();
            double overlapRight = brick.getX() + brick.getWidth() - (m_x - m_radius);
            double overlapTop = m_y + m_radius - brick.getY();
            double overlapBottom = brick.getY() + brick.getHeight() - (m_y - m_radius);

            // Smallest Overlap to detect from which side the ball collide
            double smallestOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

            if (smallestOverlap == overlapLeft)
            {
                // Left collision
                printf("Left collision\n");
                m_velocityX = -m_velocityX;
            }
            else if (smallestOverlap == overlapRight)
            {
                // Right collision
                printf("Right collision\n");
                m_velocityX = -m_velocityX;
            }
            else if (smallestOverlap == overlapTop)
            {
                // Top collision
                printf("Top collision\n");
                m_velocityY = -m_velocityY;
            }
            else if (smallestOverlap == overlapBottom)
            {
                // Bot collision
                printf("Bottom collision\n");
                m_velocityY = -m_velocityY;
            }

            // Reduce durability
            bricks.setBrickDurability(i, brick.getDurability() - 20);

            // Don't loop on the last bricks
            break;
        }
    }
}

void Ball::handleCollisionsPaddle(Paddle paddle)
{
    if (m_x + m_radius >= paddle.getX() && m_x - m_radius <= paddle.getX() + paddle.getWidth() &&
        m_y + m_radius >= paddle.getY() && m_y - m_radius <= paddle.getY() + (paddle.getHeight() / 2))
    {
        // Collision
        // Change direction depending on where it hits
        double ratioCollision = static_cast<double>(m_x - (paddle.getX() + paddle.getWidth() / 2)) / static_cast<double>(paddle.getWidth() / 2);
        // printf("ratio : %f\n",ratioCollision);
        double angle = (abs(ratioCollision)) * (M_PI / 3); // Reduce de range of the angle possible
        // printf("angle : %f\n",(angle*180)/M_PI);
        if (ratioCollision < 0)
        {
            m_velocityX = -m_velocity * sin(angle);
            m_velocityY = -m_velocity * cos(angle);
        }
        else
        {
            m_velocityX = m_velocity * sin(angle);
            m_velocityY = -m_velocity * cos(angle);
        }
        // Juste in case, the ball will hit just one time
        m_y = paddle.getY() - m_radius - 1;
    }
}

void Ball::handleCollisionsBorder(int windowWidth, int windowHeight)
{
    // Border collision
    // printf("posX : %d\nposY : %d\n",m_x - m_radius,m_y - m_radius);
    if (m_x - m_radius < 0)
    {
        // Left
        m_x = m_radius;
        m_velocityX = -m_velocityX;
    }
    else if (m_x + m_radius > windowWidth)
    {
        // Right
        m_x = windowWidth - m_radius;
        m_velocityX = -m_velocityX;
    }
    if (m_y - m_radius < 0)
    {
        // Top
        m_y = m_radius;
        m_velocityY = -m_velocityY;
    }
    else if (m_y + m_radius > windowHeight)
    {
        // Bottom
        // reset for now
        this->reset();
    }
}

void Ball::reset()
{
    // reset position and velocity
    m_x = m_screenWidth / 2;
    m_y = m_screenHeight / 2;
    m_velocityX = 0;
    m_velocityY = m_velocity;
}

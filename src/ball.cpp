#include <cmath>
#include <math.h>
#include <algorithm>
#include "../include/ball.hpp"
#include "../include/colour.hpp"

#define VELOCITY 600
#define RANGE_ANGLE 4
#define STARTING_ANGLE (M_PI / 4)

Ball::Ball(int radius, int initialX, int initialY, int screenWidth, int screenHeight) : m_radius(radius),
                                                                                        m_position(Vector2D(initialX,initialY)),
                                                                                        m_velocity(Vector2D(0,VELOCITY)),
                                                                                        m_screenWidth(screenWidth),
                                                                                        m_screenHeight(screenHeight),
                                                                                        m_updateCounter(0),
                                                                                        m_justCollide(false) {}

void Ball::update(float deltaTime, Paddle paddle, Bricks &bricks, GameStatus &gameStatus)
{
    m_updateCounter++; // Ajouter 1 mise à jour pour la balle
    
    // Gérer les collisions
    m_position = m_position + m_velocity * deltaTime;

    handleCollisionsBorder(m_screenWidth, m_screenHeight, gameStatus);
    handleCollisionsPaddle(paddle);
    handleCollisionsBricks(bricks, gameStatus);
}


void Ball::handleInput(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
    {
        this->resetBall();
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
    drawCircle(renderer, m_position.x, m_position.y, m_radius);
}

#include "ball.hpp"
#include "bricks.hpp"

void Ball::handleCollisionsBricks(Bricks &bricks, GameStatus &gameStatus)
{
    if (m_justCollide)
    {
        if (m_updateCounter >= 2)
        {
            m_justCollide = false;
            m_updateCounter = 0;
        }
        return;
    }

    // Get all bricks
    const std::vector<Brick> &allBricks = bricks.getAllBricks();
    // Browse all bricks
    for (size_t i = 0; i < allBricks.size(); ++i)
    {
        const Brick &brick = allBricks[i];

        // Verify collision on each sides
        if (m_position.x + m_radius >= brick.getX() && m_position.x - m_radius <= brick.getX() + brick.getWidth() &&
            m_position.y + m_radius >= brick.getY() && m_position.y - m_radius <= brick.getY() + brick.getHeight())
        {
            // Collision detected
            m_justCollide = true;
            // Calcul every overlap
            double overlapLeft = m_position.x + m_radius - brick.getX();
            double overlapRight = brick.getX() + brick.getWidth() - (m_position.x - m_radius);
            double overlapTop = m_position.y + m_radius - brick.getY();
            double overlapBottom = brick.getY() + brick.getHeight() - (m_position.y - m_radius);

            // Smallest Overlap to detect from which side the ball collide
            double smallestOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

            if (smallestOverlap == overlapLeft)
            {
                // Left collision
                printf("Left collision\n");
                m_velocity.x = -m_velocity.x;
            }
            else if (smallestOverlap == overlapRight)
            {
                // Right collision
                printf("Right collision\n");
                m_velocity.x = -m_velocity.x;
            }
            else if (smallestOverlap == overlapTop)
            {
                // Top collision
                printf("Top collision\n");
                m_velocity.y = -m_velocity.y;
            }
            else if (smallestOverlap == overlapBottom)
            {
                // Bot collision
                printf("Bottom collision\n");
                m_velocity.y = -m_velocity.y;
            }

            // Reduce durability
            bricks.setBrickDurability(i, brick.getDurability() - 20);
            gameStatus.increaseScore();
            std::cout << "score : " << gameStatus.getScore() << std::endl;
            // Don't loop on the last bricks
            if (brick.getDurability() <= 0)
                bricks.removeBrick(i);
            break;
        }
    }
}

void Ball::handleCollisionsPaddle(Paddle paddle)
{
    if (m_position.x + m_radius >= paddle.getX() && m_position.x - m_radius <= paddle.getX() + paddle.getWidth() &&
        m_position.y + m_radius >= paddle.getY() && m_position.y - m_radius <= paddle.getY() + (paddle.getHeight() / 2))
    {
        // Collision
        // Change direction depending on where it hits
        double ratioCollision = static_cast<double>(m_position.x - (paddle.getX() + paddle.getWidth() / 2)) / static_cast<double>(paddle.getWidth() / 2);
        // printf("ratio : %f\n",ratioCollision);
        double angle = (abs(ratioCollision)) * (M_PI / 3); // Reduce de range of the angle possible
        // printf("angle : %f\n",(angle*180)/M_PI);
        if (ratioCollision < 0)
        {
            m_velocity.x = -VELOCITY * sin(angle);
            m_velocity.y = -VELOCITY * cos(angle);
        }
        else
        {
            m_velocity.x = VELOCITY * sin(angle);
            m_velocity.y = -VELOCITY * cos(angle);
        }
        // Juste in case, the ball will hit just one time
        m_position.y = paddle.getY() - m_radius - 1;
    }
}

void Ball::handleCollisionsBorder(int windowWidth, int windowHeight, GameStatus &gameStatus)
{
    // Border collision
    // printf("posX : %d\nposY : %d\n",m_position.x - m_radius,m_position.y - m_radius);
    if (m_position.x - m_radius < 0)
    {
        // Left
        m_position.x = m_radius;
        m_velocity.x = -m_velocity.x;
    }
    else if (m_position.x + m_radius > windowWidth)
    {
        // Right
        m_position.x = windowWidth - m_radius;
        m_velocity.x = -m_velocity.x;
    }
    if (m_position.y - m_radius < 0)
    {
        // Top
        m_position.y = m_radius;
        m_velocity.y = -m_velocity.y;
    }
    else if (m_position.y + m_radius > windowHeight)
    {
        // Bottom
        // reset and decrease life
        gameStatus.decreaseLife();
        std::cout << "life : " << gameStatus.getLife() << std::endl;
        this->resetBall();
    }
}

void Ball::resetBall()
{
    // reset position and velocity
    m_position.x = m_screenWidth / 2;
    m_position.y = m_screenHeight / 2;
    m_velocity.x = 0;
    m_velocity.y = VELOCITY;
}

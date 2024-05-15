#include <iostream>
#include <algorithm>
#include <math.h>
#include "../include/paddle.hpp"
#include "../include/balls.hpp"

void Paddle::handleInput(SDL_Event &event, int screenWidth)
{
    switch (event.type)
    {
    case SDL_MOUSEMOTION:
        if (event.motion.x >= 0 && event.motion.x < screenWidth)
        {
            m_x = event.motion.x - m_width / 2;
        }
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
            if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT])
            {
                m_velocity = 0;
            }
            else
            {
                m_velocity = -PADDLE_SPEED;
            }
            break;
        case SDLK_RIGHT:
            if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])
            {
                m_velocity = 0;
            }
            else
            {
                m_velocity = PADDLE_SPEED;
            }
            break;
        }
        break;
    case SDL_KEYUP:
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
            if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT])
            {
                m_velocity = PADDLE_SPEED;
            }
            else
            {
                m_velocity = 0;
            }
            break;
        case SDLK_RIGHT:
            if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])
            {
                m_velocity = -PADDLE_SPEED;
            }
            else
            {
                m_velocity = 0;
            }
            break;
        }
        break;
    }
}

void Paddle::handleCollisionsBonuses(Bonuses &bonuses, Balls &balls, GameStatus &gameStatus)
{
    // Get all bonuses
    std::vector<Bonus> &allBonuses = bonuses.getBonuses();
    // Iterate through all bonuses
    for (size_t i = 0; i < allBonuses.size(); ++i)
    {
        Bonus &bonus = allBonuses[i];

        // Get bonus position and dimensions
        int bonus_x = bonus.getX();
        int bonus_y = bonus.getY();
        int bonus_width = bonus.getWidth();
        int bonus_height = bonus.getHeight();

        // Check collision between paddle and bonus
        if (m_x + m_width >= bonus_x &&
            m_x <= bonus_x + bonus_width &&
            m_y + m_height >= bonus_y &&
            m_y <= bonus_y + bonus_height &&
            bonus.isActive())
        {
            // Apply bonus effect based on bonus type
            bonus.setActive(false);
            switch (bonus.getType())
            {
            case 0:                                                   // Increase paddle size
                this->setWidth(std::min(200, this->getWidth() + 50)); // Ensure paddle width doesn't go above 200
                std::cout << "paddle width : " << this->getWidth() << std::endl;
                break;
            case 1: // Duplicate ball
                // Add a ball to the balls vector
                balls.addBall(balls.getBall(0));
                break;
            case 2:                                                                // Decrease ball size
                balls.changeRadius(std::max(5, balls.getBall(0).getRadius() - 5)); // Ensure ball radius doesn't go below 5
                break;
            case 3: // Increase life
                gameStatus.increaseLife();
                std::cout << "life : " << gameStatus.getLife() << std::endl;
                break;
            case 4: // Increase score ratio
                gameStatus.increaseScoreRatio();
                break;
            case 5:                                                                             // Increase ball speed
                balls.changeVelocityRatio(std::min(2.0, balls.getBall(0).getVelocity() + 0.5)); // Ensure ball speed doesn't go above 2.0
                break;
            case 6:                                                  // Decrease paddle size
                this->setWidth(std::max(50, this->getWidth() - 50)); // Ensure paddle width doesn't go below 50
                std::cout << "paddle width : " << this->getWidth() << std::endl;
                break;
            default:
                break;
            }

            // Remove the collected bonus
            std::cout << "Bonus collected" << std::endl;
            break; // Exit loop after processing collision with one bonus
        }
    }
}

void Paddle::drawPaddle(SDL_Renderer *renderer) const
{
    SDL_Rect rect = {m_x, m_y, m_width, m_height};
    SDL_Color c = Colours::White;
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderFillRect(renderer, &rect);
}

void Paddle::update(float deltaTime, Balls &balls, Bonuses &bonuses, GameStatus &gameStatus)
{
    m_x += m_velocity * deltaTime;

    if (m_x < 0)
    {
        m_x = 0;
    }
    else if (m_x + m_width > m_screenWidth)
    {
        m_x = m_screenWidth - m_width;
    }
    handleCollisionsBonuses(bonuses, balls, gameStatus);
}

void Paddle::resetPaddle()
{
    m_x = (m_screenWidth - m_width) / 2;
    m_y = m_screenHeight - 100;
    m_width = 100;
}
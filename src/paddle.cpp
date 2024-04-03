#include "../include/paddle.hpp"
#include "../include/colour.hpp"

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

void Paddle::drawPaddle(SDL_Renderer *renderer) const
{
    SDL_Rect rect = {m_x, m_y, m_width, m_height};
    SDL_SetRenderDrawColor(renderer, Colours::White.r, Colours::White.g, Colours::White.b, Colours::White.a);
    SDL_RenderFillRect(renderer, &rect);
}

void Paddle::update(float deltaTime)
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
}

void Paddle::resetPaddle()
{
    m_x = (m_screenWidth - m_width) / 2;
    m_y = m_screenHeight - 100;
}
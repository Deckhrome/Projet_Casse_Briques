#include <cmath>
#include "../include/ball.hpp"
#include "../include/colours.hpp"

#define VELOCITY_X 300
#define VELOCITY_Y 400


Ball::Ball(int radius, int initialX, int initialY, int screenWidth, int screenHeight,std::unique_ptr<Paddle> paddle) :
    m_radius(radius),
    m_x(initialX),
    m_y(initialY),
    m_velocityX(VELOCITY_X),
    m_velocityY(VELOCITY_Y),
    m_screenWidth(screenWidth),
    m_screenHeight(screenHeight),
    m_paddle(std::move(paddle)) {}

void Ball::update(float deltaTime) {
    m_x += static_cast<int>(m_velocityX * deltaTime);
    m_y += static_cast<int>(m_velocityY * deltaTime);
    // Handle collision
    handleCollisionsBorder(m_screenWidth, m_screenHeight);
    handleCollisionsPaddle();
}


void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    for (int x = -radius; x <= radius; ++x) {
        int height = static_cast<int>(std::sqrt(radius * radius - x * x));
        SDL_RenderDrawLine(renderer, centerX + x, centerY - height, centerX + x, centerY + height);
    }
}

void Ball::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, Colours::Red.r, Colours::Red.g, Colours::Red.b, Colours::Red.a);
    drawCircle(renderer, m_x, m_y, m_radius);
}

void Ball::handleCollisionsPaddle() {
    if (m_x + m_radius >= m_paddle->getX() && m_x - m_radius <= m_paddle->getX() + m_paddle->getWidth() &&
        m_y + m_radius >= m_paddle->getY() && m_y - m_radius <= m_paddle->getY() + m_paddle->getHeight()) {
        // La balle est en collision avec le paddle

        // Inverser la direction verticale pour simuler le rebond
        m_velocityY = -m_velocityY;

        // Déplacer la balle juste au-dessus du paddle pour éviter une collision répétée
        m_y = m_paddle->getY() - m_radius;
    }
}


void Ball::handleCollisionsBorder(int windowWidth, int windowHeight) {
    // Border collision
    //printf("posX : %d\nposY : %d\n",m_x - m_radius,m_y - m_radius);
    if (m_x - m_radius < 0) {
        // Left
        m_x = m_radius;
        m_velocityX = -m_velocityX;
    } else if (m_x + m_radius > windowWidth) {
        // Right
        m_x = windowWidth - m_radius;
        m_velocityX = -m_velocityX; 
    }
    if (m_y - m_radius < 0) {
        // Top
        m_y = m_radius;
        m_velocityY = -m_velocityY; 
    } else if (m_y + m_radius > windowHeight) {
        // Bottom
        m_y = windowHeight - m_radius;
        m_velocityY = -m_velocityY; 
        }
    }


void Ball::reset() {
    // reset position and velocity
    m_x = m_screenWidth / 2;
    m_y = m_screenHeight / 2;
    m_velocityX = VELOCITY_X;
    m_velocityY = VELOCITY_Y;
}

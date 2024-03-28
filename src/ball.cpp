#include <cmath>
#include <math.h>
#include "../include/ball.hpp"
#include "../include/colours.hpp"

#define VELOCITY 400
#define RANGE_ANGLE 4

Ball::Ball(int radius, int initialX, int initialY, int screenWidth, int screenHeight) :
    m_radius(radius),
    m_x(initialX),
    m_y(initialY),
    m_velocity(VELOCITY),
    m_velocityX(m_velocity*cos(M_PI/4)),
    m_velocityY(-m_velocity*sin(M_PI/4)),
    m_screenWidth(screenWidth),
    m_screenHeight(screenHeight) {}

void Ball::update(float deltaTime, Paddle * paddle) {
    m_x += static_cast<int>(m_velocityX * deltaTime);
    m_y += static_cast<int>(m_velocityY * deltaTime);
    // Handle collision
    handleCollisionsBorder(m_screenWidth, m_screenHeight);
    handleCollisionsPaddle(*paddle);
}

void Ball::handleInput(SDL_Event& event){
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE){
        this->reset();
    }
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

void Ball::handleCollisionsPaddle(Paddle paddle) {
    if (m_x + m_radius >= paddle.getX() && m_x - m_radius <= paddle.getX() + paddle.getWidth() &&
        m_y + m_radius >= paddle.getY() && m_y - m_radius <= paddle.getY() + (paddle.getHeight()/2)) {
        // Collision

        // Change direction depending on where it hits
        double ratioCollision = static_cast<double>(m_x - (paddle.getX() + paddle.getWidth() / 2)) / static_cast<double>(paddle.getWidth() / 2);
        printf("ratio : %f\n",ratioCollision);
        double angle = (abs(ratioCollision)) * (M_PI / 3); // Reduce de range of the angle possible

        printf("angle sortie : %f\n",(angle*180)/M_PI);
        if(ratioCollision < 0){
            m_velocityX = -m_velocity*sin(angle);
            m_velocityY = -m_velocity*cos(angle);
        }
        else{
            m_velocityX = m_velocity*sin(angle);
            m_velocityY = -m_velocity*cos(angle);
        }
 
        // Déplacer la balle juste au-dessus du paddle pour éviter une collision répétée
        m_y = paddle.getY() - m_radius -1;
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
        //reset for now
        this->reset();
        }
    }


void Ball::reset() {
    // reset position and velocity
    m_x = m_screenWidth / 2;
    m_y = m_screenHeight / 2;
    m_velocityX = m_velocity*cos(M_PI/4);
    m_velocityY = m_velocity*sin(M_PI/4);
}

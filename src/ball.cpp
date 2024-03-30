#include <cmath>
#include <math.h>
#include "../include/ball.hpp"
#include "../include/colour.hpp"

#define VELOCITY 600
#define RANGE_ANGLE 4
#define STARTING_ANGLE (M_PI/4)

Ball::Ball(int radius, int initialX, int initialY, int screenWidth, int screenHeight) :
    m_radius(radius),
    m_x(initialX),
    m_y(initialY),
    m_velocity(VELOCITY),
    m_velocityX(m_velocity*cos(STARTING_ANGLE)),
    m_velocityY(-m_velocity*sin(STARTING_ANGLE)),
    m_screenWidth(screenWidth),
    m_screenHeight(screenHeight) {}

void Ball::update(float deltaTime, Paddle paddle, Bricks& bricks) {
    m_x += static_cast<int>(m_velocityX * deltaTime);
    m_y += static_cast<int>(m_velocityY * deltaTime);
    // Handle collision
    handleCollisionsBorder(m_screenWidth, m_screenHeight);
    handleCollisionsPaddle(paddle);
    handleCollisionsBricks(bricks);
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

void Ball::drawBall(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, Colours::Red.r, Colours::Red.g, Colours::Red.b, Colours::Red.a);
    drawCircle(renderer, m_x, m_y, m_radius);
}

#include "ball.hpp"
#include "bricks.hpp"

void Ball::handleCollisionsBricks(Bricks& bricks) {
    // Récupérer toutes les briques
    const std::vector<Brick>& allBricks = bricks.getAllBricks();

    // Parcourir toutes les briques
    for (size_t i = 0; i < allBricks.size(); ++i) {
        const Brick& brick = allBricks[i];

        // Vérifier si la brique est déjà détruite
        if (brick.getDurability() <= 0) {
            continue; // Passer à la brique suivante si celle-ci est déjà détruite
        }

        // Verify collision on each sides
        if (m_x + m_radius >= brick.getX() && m_x - m_radius <= brick.getX() + brick.getWidth() &&
            m_y + m_radius >= brick.getY() && m_y - m_radius <= brick.getY() + brick.getHeight()) {
            // La balle est en collision avec la brique

            // Gérer la collision comme vous le souhaitez (par exemple, inverser la direction de la balle)
            m_velocityY = -m_velocityY; // Inverser la direction verticale

            // Réduire la durabilité de la brique
            int newDurability = brick.getDurability() - 20;
            bricks.setBrickDurability(i, newDurability);

            // Sortir de la boucle si une collision est détectée
            break;
        }
    }
}


void Ball::handleCollisionsPaddle(Paddle paddle) {
    if (m_x + m_radius >= paddle.getX() && m_x - m_radius <= paddle.getX() + paddle.getWidth() &&
        m_y + m_radius >= paddle.getY() && m_y - m_radius <= paddle.getY() + (paddle.getHeight()/2)) {
        // Collision
        // Change direction depending on where it hits
        double ratioCollision = static_cast<double>(m_x - (paddle.getX() + paddle.getWidth() / 2)) / static_cast<double>(paddle.getWidth() / 2);
        //printf("ratio : %f\n",ratioCollision);
        double angle = (abs(ratioCollision)) * (M_PI / 3); // Reduce de range of the angle possible
        //printf("angle : %f\n",(angle*180)/M_PI);
        if(ratioCollision < 0){
            m_velocityX = -m_velocity*sin(angle);
            m_velocityY = -m_velocity*cos(angle);
        }
        else{
            m_velocityX = m_velocity*sin(angle);
            m_velocityY = -m_velocity*cos(angle);
        }
        // Juste in case, the ball will hit just one time
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

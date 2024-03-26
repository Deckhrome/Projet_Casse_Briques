#ifndef BALL_HPP
#define BALL_HPP

#include "gameObject.hpp"
#include "paddle.hpp"
#include <memory> // Inclure la bibliothèque pour std::unique_ptr

class Ball : public GameObject {
public:
    // Constructeur
    Ball(int radius, int initialX, int initialY, int screenWidth, int screenHeight, std::unique_ptr<Paddle> paddle);

    // Méthodes héritées de GameObject
    void update(float deltaTime) override;
    void draw(SDL_Renderer* renderer) const override;
    void handleInput(SDL_Event& event) override {(void)event;}

    // Handle every type of collision (window for now)
    void handleCollisionsBorder(int windowWidth, int windowHeight);
    void handleCollisionsPaddle();

    // Getter
    int getX() const { return m_x; }
    int getY() const { return m_y; }

    // Reset position
    void reset();

private:
    int m_radius;
    int m_x;               
    int m_y;               
    int m_velocityX;       
    int m_velocityY;       
    int m_screenWidth;     
    int m_screenHeight;
    std::unique_ptr<Paddle> m_paddle; // Utilisation de std::unique_ptr pour le paddle
};

#endif

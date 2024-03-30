#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <memory>
#include "window.hpp"
#include "paddle.hpp"
#include "bricks.hpp"
#include "ball.hpp"

class Game {
public:
    Game(int screenWidth, int screenHeight, int paddleWidth, int paddleHeight, int ball_radius) :
        m_window(screenWidth, screenHeight),
        m_paddle((screenWidth - paddleWidth) / 2, screenHeight - 100, paddleWidth, paddleHeight, screenWidth),
        m_ball(ball_radius, screenWidth/2, screenHeight/2, screenWidth, screenHeight),
        m_bricks(4,8,screenWidth,screenHeight) {}
    void run();
    void draw(SDL_Renderer * renderer);
    void update();
    void handleInput(SDL_Event event);

private:
    Window m_window;
    Paddle m_paddle;
    Ball m_ball;
    Bricks m_bricks;
};


#endif // GAME_HPP

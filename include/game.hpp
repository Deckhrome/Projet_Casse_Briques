#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <memory>
#include <map>
#include "window.hpp"
#include "paddle.hpp"
#include "bricks.hpp"
#include "ball.hpp"
#include "menu.hpp"

enum class GameState
{
    MENU,
    LEVEL
};

enum class Level
{
    DEFAULT_LEVEL,
    LEVEL_1,
    LEVEL_2,
    LEVEL_3
};

class Game
{
public:
    Game(int screenWidth, int screenHeight, int paddleWidth, int paddleHeight, int ball_radius) : m_window(screenWidth, screenHeight),
                                                                                                  m_paddle((screenWidth - paddleWidth) / 2, screenHeight - 100, paddleWidth, paddleHeight, screenWidth),
                                                                                                  m_ball(ball_radius, screenWidth / 2, screenHeight / 2, screenWidth, screenHeight),
                                                                                                  m_bricks(2, 4, screenWidth, screenHeight),
                                                                                                  m_gameState(GameState::MENU),
                                                                                                  m_level(Level::LEVEL_1),
                                                                                                  m_menu(m_window.getRenderer(), screenWidth, screenHeight, m_window.getTexture(), m_window.getFont())

    {
        m_menu.initMenu();
    }
    void run();
    void drawLevel(SDL_Renderer *renderer);
    void update();
    void render();
    void renderMenu();
    void renderLevel(Level level);
    void handleLevelInput(SDL_Event event);
    void handleMenuInput(SDL_Event event);

private:
    Window m_window;
    Paddle m_paddle;
    Ball m_ball;
    Bricks m_bricks;
    GameState m_gameState;
    Level m_level;
    Menu m_menu;
};

#endif // GAME_HPP

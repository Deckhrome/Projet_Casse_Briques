#include "../include/game.hpp"
#include <time.h>
#include <iostream>
#include <random>

void Game::run()
{
    bool running = true;
    SDL_Event event;
    Uint32 lastFrameTime = SDL_GetTicks();
    srand(time(NULL));

    while (running)
    {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastFrameTime) / 1000.0f; // Second

        lastFrameTime = currentTime;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else
            {
                if (m_gameState == GameState::MENU)
                {
                    handleMenuInput(event);
                }
                else if (m_gameState == GameState::LEVEL)
                {
                    handleLevelInput(event);
                }
            }
        }
        if (m_gameState == GameState::MENU)
        {
            renderMenu();
        }
        else if (m_gameState == GameState::LEVEL)
        {
            renderLevel(m_level, deltaTime);
        }

        SDL_Delay(1000 / 60);
        stillPlaying();
    }
}

void Game::renderMenu()
{
    m_window.clear();
    m_menu.drawNumberedButtons();
    m_window.display();
}

void Game::renderLevel(Level currentLevel, float deltaTime)
{
    (void)currentLevel;
    this->update(deltaTime);
    this->render();
}

void Game::render()
{
    m_window.clear();
    SDL_Rect rect = {0, 0, m_window.getWidth(), m_window.getHeight()};
    SDL_RenderCopy(m_window.getRenderer(), m_window.getBackgroundTexture(), nullptr, &rect);
    this->drawLevel(m_window.getRenderer());
    m_window.display();
}

void Game::drawLevel(SDL_Renderer *renderer)
{
    m_paddle.drawPaddle(renderer);
    m_balls.drawBalls(renderer);
    m_bricks.drawBricks(renderer);
    m_bonuses.drawBonuses(renderer);
    m_gameStatus.drawGameStatus(renderer);
}
void Game::update(float deltaTime)
{
    m_bonuses.update(deltaTime);
    m_paddle.update(deltaTime);
    m_balls.update(deltaTime, m_paddle, m_bricks, m_bonuses, m_gameStatus);
}

void Game::reset()
{
    m_bonuses.resetBonuses();
    m_balls.resetBalls();
    m_paddle.resetPaddle();
    m_bricks.resetBricks();
    m_gameStatus.resetGameStatus();
}

void Game::handleLevelInput(SDL_Event event)
{
    m_paddle.handleInput(event, m_window.getWidth());
}

void Game::handleMenuInput(SDL_Event event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    {
        int mouseX = event.button.x;
        int mouseY = event.button.y;

        for (const auto &button : m_menu.getLevelButtons())
        {
            if (mouseX >= button.rect.x && mouseX <= button.rect.x + button.rect.w &&
                mouseY >= button.rect.y && mouseY <= button.rect.y + button.rect.h)
            {
                m_gameState = GameState::LEVEL;
                switch (button.number)
                {
                case 1:
                    m_level = Level::LEVEL_1;
                    this->m_bricks.initWithFile("data/Level/level1.1");
                    break;
                case 2:
                    m_level = Level::LEVEL_2;
                    this->m_bricks.initWithFile("data/Level/level1.2");
                    break;
                case 3:
                    m_level = Level::LEVEL_3;
                    this->m_bricks.initWithFile("data/Level/level1.3");
                    break;
                default:
                    break;
                };
            }
        }
    }
}

void Game::stillPlaying()
{
    if ((m_bricks.getTotalBricks() == 0 || m_gameStatus.getLife() <= 0) && GameState::LEVEL == m_gameState)
    {
        m_gameState = GameState::MENU;
        // reset
        this->reset();
        printf("Game Over\n");
        return;
    }
}
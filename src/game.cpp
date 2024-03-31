#include "../include/game.hpp"

void Game::run()
{
    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else
            {
                // We're in the menu
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
            renderLevel(m_level);
        }
        SDL_Delay(1000 / 60);
    }
}

void Game::renderMenu()
{
    m_window.clear();
    m_menu.drawLevelButtons();
    m_window.display();
}

void Game::renderLevel(Level currentLevel)
{
    switch (currentLevel)
    {
    case Level::LEVEL_1:
        this->update();
        this->render();
        break;
    case Level::LEVEL_2:

        break;
    case Level::LEVEL_3:

        break;
    }
}

void Game::render()
{
    m_window.clear();
    this->drawLevel(m_window.getRenderer());
    m_window.display();
}

void Game::drawLevel(SDL_Renderer *renderer)
{
    m_paddle.drawPaddle(renderer);
    m_ball.drawBall(renderer);
    m_bricks.drawBricks(renderer);
}
void Game::update()
{
    m_paddle.update(1.0f / 60);
    m_ball.update(1.0f / 60, m_paddle, m_bricks);
}

void Game::handleLevelInput(SDL_Event event)
{
    m_paddle.handleInput(event, m_window.getWidth());
    m_ball.handleInput(event);
}

void Game::handleMenuInput(SDL_Event event)
{
    (void)event;
}
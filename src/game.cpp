#include "../include/game.hpp"

void Game::run()
{
    bool running = true;
    SDL_Event event;

    // Temps écoulé depuis le début de la boucle de jeu
    Uint32 lastFrameTime = SDL_GetTicks();

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

        // Rendu en fonction de l'état du jeu
        if (m_gameState == GameState::MENU)
        {
            renderMenu();
        }
        else if (m_gameState == GameState::LEVEL)
        {
            renderLevel(m_level, deltaTime);
        }

        SDL_Delay(1000 / 60); // Limiter à environ 60 FPS
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
    switch (currentLevel)
    {
    case Level::LEVEL_1:
        this->update(deltaTime);
        this->render();
        break;
    case Level::LEVEL_2:

        break;
    case Level::LEVEL_3:

        break;
    case Level::DEFAULT_LEVEL:

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
void Game::update(float deltaTime)
{
    m_paddle.update(deltaTime);
    m_ball.update(deltaTime, m_paddle, m_bricks);
}

void Game::handleLevelInput(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
    {
        m_gameState = GameState::MENU;
        // reset
        m_ball.reset();
        m_paddle.reset();
        m_bricks.resetBricks();
        return;
    }
    m_paddle.handleInput(event, m_window.getWidth());
    m_ball.handleInput(event);
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
                    this->m_bricks.initWithFile("data/Level/level1.1");
                    break;
                case 3:
                    m_level = Level::LEVEL_3;
                    this->m_bricks.initWithFile("data/Level/level1.1");
                    break;
                default:
                    break;
                };
            }
        }
    }
}

#include "../include/game.hpp"

void Game::run() {
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            this->handleInput(event);
        }

        this->update();

        m_window.clear();

        this->draw(m_window.getRenderer());
        
        m_window.display();

        SDL_Delay(1000 / 60);
    }
}

void Game::draw(SDL_Renderer * renderer) {
    m_paddle.drawPaddle(renderer);
    m_ball.drawBall(renderer);
    m_bricks.drawBricks(renderer);
}
void Game::update(){
    m_paddle.update(1.0f / 60);
    m_ball.update(1.0f / 60, m_paddle, m_bricks);
}

void Game::handleInput(SDL_Event event){
    m_paddle.handleInput(event);
    m_ball.handleInput(event);
}


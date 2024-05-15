#ifndef GAMESTATUS_HPP
#define GAMESTATUS_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "colour.hpp"

#define INITIAL_LIFE 5
#define INITIAL_SCORE 0
#define INITIAL_SCORE_RATIO 1

/*
    Define the GameStatus class to manage the game status
*/

class GameStatus
{
private:
    TTF_Font *m_font;
    int m_screenWidth;
    int m_screenHeight;
    int m_life;
    int m_score;
    int m_scoreRatio;

public:
    GameStatus(TTF_Font *font, int screenWidth, int screenHeight) : m_font(font),
                                                                    m_screenWidth(screenWidth),
                                                                    m_screenHeight(screenHeight),
                                                                    m_life(INITIAL_LIFE),
                                                                    m_score(INITIAL_SCORE),
                                                                    m_scoreRatio(INITIAL_SCORE_RATIO) {}
    ~GameStatus() {}

    // Draw life and score
    void drawGameStatus(SDL_Renderer *renderer)
    {
        SDL_Color c = Colours::Black;
        SDL_Rect rect = {m_screenWidth - 100, m_screenHeight - 50, 100, 50};
        SDL_Surface *surface = TTF_RenderText_Solid(m_font, ("Life: " + std::to_string(m_life)).c_str(), c);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        rect = {0, m_screenHeight - 50, 100, 50};
        surface = TTF_RenderText_Solid(m_font, ("Score: " + std::to_string(m_score)).c_str(), c);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    // Reset
    void resetScore() { m_score = INITIAL_SCORE; }
    void resetLife() { m_life = INITIAL_LIFE; }
    void resetGameStatus()
    {
        resetScore();
        resetLife();
    }
    // Increase score ratio
    void increaseScoreRatio() { m_scoreRatio += 1; }

    // Increase score
    void increaseScore() { m_score += 10 * m_scoreRatio; }

    // Increase life
    void increaseLife() { m_life += 1; }

    // Decrease life
    void decreaseLife() { m_life -= 1; }

    // Getters
    int getLife() { return m_life; }
    int getScore() { return m_score; }
};

#endif
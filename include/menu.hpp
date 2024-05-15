#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "colour.hpp"

#define BUTTON_WIDTH 80
#define BUTTON_HEIGHT 80
#define NUMBER_OF_BUTTON 3
#define BUTTON_PADDING 20

class Menu
{
public:
    // Constructor
    Menu(SDL_Renderer *renderer, int screenWidth, int screenHeight, SDL_Texture *levelButtonTexture, TTF_Font *font)
        : m_renderer(renderer), m_screenWidth(screenWidth), m_screenHeight(screenHeight), m_levelButtonTexture(levelButtonTexture), m_font(font) { initMenu(); }

    // struct to store the level button
    struct LevelButton
    {
        SDL_Rect rect;
        SDL_Texture *texture;
        int number;
    };

    // Initialize the menu
    void initMenu();

    // Adding a level button
    void addLevelButton(int x, int y, int width, int height, int numberOnButton, SDL_Texture *texture);

    // Draw every buttons
    void drawNumberedButtons();

    // Render text
    void renderText(SDL_Renderer *renderer, const std::string &text, int x, int y, SDL_Color color);

    // getters
    std::vector<LevelButton> getLevelButtons() { return m_levelButtons; }

private:
    SDL_Renderer *m_renderer;
    int m_screenWidth;
    int m_screenHeight;
    std::vector<LevelButton> m_levelButtons;
    SDL_Texture *m_levelButtonTexture;
    TTF_Font *m_font;
};

#endif // MENU_HPP

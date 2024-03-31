#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

#define BUTTON_WIDTH 80
#define BUTTON_HEIGHT 80
#define NUMBER_OF_BUTTON 3
#define BUTTON_PADDING 20

class Menu
{
public:
    Menu(SDL_Renderer *renderer, int screenWidth, int screenHeight, SDL_Texture *levelButtonTexture)
        : m_renderer(renderer), m_screenWidth(screenWidth), m_screenHeight(screenHeight), m_levelButtonTexture(levelButtonTexture) {}

    struct LevelButton
    {
        SDL_Rect rect;
        SDL_Texture *texture;
    };
    void initMenu();

    // Adding a level button
    void addLevelButton(int x, int y, int width, int height, SDL_Texture *texture);

    // Draw every buttons
    void drawLevelButtons();

private:
    SDL_Renderer *m_renderer;
    int m_screenWidth;
    int m_screenHeight;
    std::vector<LevelButton> m_levelButtons;
    SDL_Texture *m_levelButtonTexture;
};

#endif // MENU_HPP

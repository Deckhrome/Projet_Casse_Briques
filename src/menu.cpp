#include "../include/menu.hpp"

void Menu::initMenu()
{
    int rows = (NUMBER_OF_BUTTON % 3) + 1; // Caculate number of button
    int cols = 3;                          // 3 columns
    // Starting position to place
    int startX = (m_screenWidth - cols * (BUTTON_WIDTH + BUTTON_PADDING)) / 2;
    int startY = (m_screenHeight - rows * (BUTTON_HEIGHT + BUTTON_PADDING)) / 2;

    // Adding buttons
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            // Calculate coords
            int x = startX + col * (BUTTON_WIDTH + BUTTON_PADDING);
            int y = startY + row * (BUTTON_HEIGHT + BUTTON_PADDING);

            addLevelButton(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, m_levelButtonTexture);
        }
    }
}

void Menu::addLevelButton(int x, int y, int width, int height, SDL_Texture *texture)
{
    LevelButton button;
    button.rect = {x, y, width, height};
    button.texture = texture;
    m_levelButtons.push_back(button);
}

void Menu::drawLevelButtons()
{
    for (const auto &button : m_levelButtons)
    {
        SDL_RenderCopy(m_renderer, button.texture, nullptr, &button.rect);
    }
}
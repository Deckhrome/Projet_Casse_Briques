#include "../include/menu.hpp"

void Menu::initMenu()
{
    int rows = (NUMBER_OF_BUTTON % 3) + 1; // Caculate number of button
    int cols = 3;                          // 3 columns
    // Starting position to place
    int startX = (m_screenWidth - cols * (BUTTON_WIDTH + BUTTON_PADDING)) / 2;
    int startY = (m_screenHeight - rows * (BUTTON_HEIGHT + BUTTON_PADDING)) / 2;
    int numberOnButton = 1; // Number of the button
    // Adding buttons
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            // Calculate coords
            int x = startX + col * (BUTTON_WIDTH + BUTTON_PADDING);
            int y = startY + row * (BUTTON_HEIGHT + BUTTON_PADDING);

            addLevelButton(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, numberOnButton, m_levelButtonTexture);
            numberOnButton++;
        }
    }
}

void Menu::addLevelButton(int x, int y, int width, int height, int numberOnButton, SDL_Texture *texture)
{
    LevelButton button;
    button.rect = {x, y, width, height};
    button.texture = texture;
    button.number = numberOnButton;
    m_levelButtons.push_back(button);
}

void Menu::drawNumberedButtons()
{
    for (const auto &button : m_levelButtons)
    {
        // Draw button
        SDL_RenderCopy(m_renderer, button.texture, nullptr, &button.rect);

        // Calculate position to draw the number of the button
        int textWidth, textHeight;
        TTF_SizeText(m_font, std::to_string(button.number).c_str(), &textWidth, &textHeight);
        int textX = button.rect.x + (button.rect.w - textWidth) / 2;
        int textY = button.rect.y + (button.rect.h - textHeight) / 2;

        // Render of this text
        SDL_Color textColor = Colours::Black;
        renderText(m_renderer, std::to_string(button.number), textX, textY, textColor);
    }
}
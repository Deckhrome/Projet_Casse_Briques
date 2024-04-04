#ifndef LEVELBUTTON_HPP
#define LEVELBUTTON_HPP

#include <SDL2/SDL.h>
#include <memory>

class LevelButton
{
public:
    // Default constructor
    LevelButton() = default;

    LevelButton(SDL_Rect rect, std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture, int number)
        : m_rect(rect), m_texture(std::move(texture)), m_number(number) {}

    // Getters
    SDL_Rect getRect() const { return m_rect; }

    SDL_Texture* getTexture() const { return m_texture.get(); }

    int getNumber() const { return m_number; }

private:
    SDL_Rect m_rect;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_texture;
    int m_number;
};



#endif // LEVELBUTTON_HPP

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <cstdlib>
#include <string>
#include <iostream>

class Window
{
public:
    Window(int width, int height);

    ~Window();

    // Getters
    // Get Render of window
    SDL_Renderer *getRenderer() const { return m_renderer.get(); }

    // Get texture of window
    SDL_Texture *getTexture() const { return m_levelButtonTexture; }

    // Get font of window
    TTF_Font *getFont() const { return m_font; }

    // Get Width of window
    int getWidth() const { return m_width; }

    // Get Height of window
    int getHeight() const { return m_height; }

    // functions
    void display()
    {
        SDL_RenderPresent(m_renderer.get());
    }

    void clear()
    {
        SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, 255);
        SDL_RenderClear(m_renderer.get());
    }

private:
    int m_width;
    int m_height;
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
    SDL_Texture *m_levelButtonTexture;
    TTF_Font *m_font;
    SDL_Texture *m_fontTexture;

    // Verification SDL, TTF functions
    void CHK_SDL(bool condition)
    {
        if (!condition)
        {
            std::cerr << "Failure SDL: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    void CHK_TTF(bool condition)
    {
        if (!condition)
        {
            std::cerr << "Failure TTF: " << TTF_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
    }
};

#endif
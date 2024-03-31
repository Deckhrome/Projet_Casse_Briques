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
    Window(int width, int height) : m_width(width), m_height(height)
    {
        CHK(SDL_Init(SDL_INIT_VIDEO) == 0);

        CHK((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG));

        m_window = SDL_CreateWindow("Bricks Breaker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        CHK(m_window != nullptr);

        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
        CHK(m_renderer != nullptr);

        SDL_Surface *Surface = IMG_Load("/home/verdon/CPP/projet/Projet_Casse_Briques/img/orange-cartoon-square-button-png.png");
        CHK(Surface != nullptr);

        m_levelButtonTexture = SDL_CreateTextureFromSurface(m_renderer, Surface);
        SDL_FreeSurface(Surface); // Free surface after creating texture

        CHK(m_levelButtonTexture != nullptr);
    }
    ~Window()
    {
        if (m_levelButtonTexture)
            SDL_DestroyTexture(m_levelButtonTexture);
        if (m_renderer)
            SDL_DestroyRenderer(m_renderer);
        if (m_window)
            SDL_DestroyWindow(m_window);
        IMG_Quit();
        SDL_Quit();
    }
    // Getters
    // Get Render of window
    SDL_Renderer *getRenderer() const
    {
        return m_renderer;
    }

    SDL_Texture *getTexture() const
    {
        return m_levelButtonTexture;
    }

    // Get Width of window
    int getWidth() const
    {
        return m_width;
    }

    // Get Height of window
    int getHeight() const
    {
        return m_height;
    }
    // functions
    void display()
    {
        SDL_RenderPresent(m_renderer);
    }

    void clear()
    {
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_renderer);
    }

private:
    int m_width;
    int m_height;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_levelButtonTexture;

    // Verification SDL functions
    void CHK(bool condition)
    {
        if (!condition)
        {
            std::cerr << "Failure SDL: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
    }
};

#endif
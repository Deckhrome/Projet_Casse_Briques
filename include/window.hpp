#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <cstdlib>
#include <string>
#include <iostream>

class Window
{
public:
    Window(int width, int height) : m_width(width), m_height(height){
        CHK(SDL_Init(SDL_INIT_VIDEO) == 0);

        m_window = SDL_CreateWindow("Bricks Breaker",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN);
        CHK(m_window != nullptr);

        m_renderer = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_ACCELERATED);
        CHK(m_renderer != nullptr);
    }
    ~Window(){
        if (m_renderer) SDL_DestroyRenderer(m_renderer);
        if (m_window) SDL_DestroyWindow(m_window);
        SDL_Quit();
    }
// Getters
    // Get Render of window
    SDL_Renderer * getRenderer() const {
        return m_renderer;
    }

    // Get Width of window
    int getWidth() const {
        return m_width;
    }

    // Get Height of window
    int getHeight() const {
        return m_height;
    }
// functions
    void display(){
        SDL_RenderPresent(m_renderer);
    }

    void clear() {
        SDL_SetRenderDrawColor(m_renderer,0,0,0,255);
        SDL_RenderClear(m_renderer);
    }
private:
    int m_width;
    int m_height;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    // Verification SDL functions
    void CHK(bool condition){
        if(!condition){
            std::cerr << "Failure SDL: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
    }
};


#endif
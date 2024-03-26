#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SDL2/SDL.h>
#include "gameObject.hpp"

class Paddle : public GameObject
{
public:
    // Constructor
    Paddle(int x, int y,int width, int height, int screenWidth) :
    m_x(x), m_y(y), m_width(width), m_height(height), m_screenWidth(screenWidth), m_velocity(0) {}
    ~Paddle(){}
    // Update
    void update(float deltaTime) override {
        m_x += m_velocity*deltaTime;

        if(m_x < 0){
            m_x =0;
        } else if(m_x + m_width > m_screenWidth){
            m_x = m_screenWidth - m_width;
        }
    }
    // Draw
    void draw(SDL_Renderer * renderer) const override {
        SDL_Rect rect = {m_x,m_y,m_width,m_height};
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderFillRect(renderer, &rect);
    }
    // handleInput
    void handleInput(SDL_Event& event) override {
    switch(event.type) {
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
                case SDLK_LEFT:
                    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]) {
                        m_velocity = 0;
                    } else {
                        m_velocity = -PADDLE_SPEED;
                    }
                    break;
                case SDLK_RIGHT:
                    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]) {
                        m_velocity = 0;
                    } else {
                        m_velocity = PADDLE_SPEED;
                    }
                    break;
            }
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym) {
                case SDLK_LEFT:
                    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]) {
                        m_velocity = PADDLE_SPEED;
                    } else {
                        m_velocity = 0;
                    }
                    break;
                case SDLK_RIGHT:
                    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]) {
                        m_velocity = -PADDLE_SPEED;
                    } else {
                        m_velocity = 0;
                    }
                    break;
            }
            break;
    }
}

    int get_x(){return m_x;}
private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    int m_screenWidth; // to know the screen limit
    int m_velocity;

    static constexpr int PADDLE_SPEED = 300;
};



#endif
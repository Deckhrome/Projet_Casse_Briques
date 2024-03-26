#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../include/gameWindow.hpp"
#include "../include/paddle.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define PADDLE_WIDTH 100
#define PADDLE_HEIGHT 20


int main(int argc, char * argv[]) {
    GameWindow gameWindow(SCREEN_WIDTH,SCREEN_HEIGHT);
    Paddle paddle((SCREEN_WIDTH - PADDLE_WIDTH)/2,SCREEN_HEIGHT - 100,PADDLE_WIDTH,PADDLE_HEIGHT,SCREEN_WIDTH);
    paddle.update(1.0f/60);
    printf("pos_x : %d\n",paddle.get_x());
    bool running = true;
    SDL_Event event;
    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }
            paddle.handleInput(event);
        }
        paddle.update(1.0f/60);

        gameWindow.clear();

        paddle.draw(gameWindow.getRenderer());

        gameWindow.display();

        SDL_Delay(1000/60);
    }
    (void)argc;
    (void)argv;

    return 0;
}

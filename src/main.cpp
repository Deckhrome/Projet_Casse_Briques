#include <iostream>
#include "../include/game.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define PADDLE_WIDTH 100
#define PADDLE_HEIGHT 20
#define BALL_RADIUS 10

int main(int argc, char *argv[])
{
    Game game(SCREEN_WIDTH, SCREEN_HEIGHT, PADDLE_WIDTH, PADDLE_HEIGHT, BALL_RADIUS);
    game.run();

    (void)argc;
    (void)argv;

    return 0;
}

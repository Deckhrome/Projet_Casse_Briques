#include <iostream>
#include "../include/game.hpp"

#define SCREEN_WIDTH 948
#define SCREEN_HEIGHT 525
#define PADDLE_WIDTH 100
#define PADDLE_HEIGHT 10
#define BALL_RADIUS 10

int main()
{
    Game game(SCREEN_WIDTH, SCREEN_HEIGHT, PADDLE_WIDTH, PADDLE_HEIGHT, BALL_RADIUS);
    game.run();
    return 0;
}

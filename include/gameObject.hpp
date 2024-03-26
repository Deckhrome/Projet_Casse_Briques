#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SDL2/SDL.h>

class GameObject {
public:
    // All virtual method for objects
    virtual void update(float deltaTime) = 0; // update object
    virtual void draw(SDL_Renderer * renderer) const = 0; // draw object
    virtual void handleInput(SDL_Event& event) = 0; // handle input
    virtual ~GameObject() {}
};

#endif
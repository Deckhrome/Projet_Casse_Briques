#ifndef BONUSES_HPP
#define BONUSES_HPP

#include <vector>
#include <stdexcept>
#include <SDL2/SDL.h>
#include "bonus.hpp"

// Define the Bonuses class
class Bonuses
{
public:
    // Constructor
    Bonuses(int screenWidth, int screenHeight);

    // Update all bonuses
    void update(float deltaTime);

    // Draw all bonuses
    void drawBonuses(SDL_Renderer *renderer) const;

    // Add one bonus
    void pushBonus(const Bonus &bonus);

    // Remove one bonus by index
    void removeBonus(size_t index);

    // Clear all bonuses
    void resetBonuses();

    // Get bonuses
    std::vector<Bonus> &getBonuses();

    // Get the total number of bonuses
    int getNumBonuses() const;

    // Get a specific bonus by index
    const Bonus &getBonus(size_t index) const;

private:
    int m_screenWidth;
    int m_screenHeight;
    // Vector of bonuses
    std::vector<Bonus> m_all_bonuses;
};

#endif // BONUSES_HPP

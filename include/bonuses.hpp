#ifndef BONUSES_HPP
#define BONUSES_HPP

#include <vector>
#include <stdexcept>
#include <SDL2/SDL.h>
#include "bonus.hpp"

// Define the Bonuses class
class Bonuses {
public:
    // Constructor
    Bonuses(int screenWidth, int screenHeight) : m_screenWidth(screenWidth), m_screenHeight(screenHeight){};

    // Update all bonuses
    void update(float deltaTime){
        for(size_t i = 0; i < m_all_bonuses.size(); i++){
            if(m_all_bonuses[i].update(deltaTime) >= m_screenHeight){
                removeBonus(i);
            }
        
        }
    }

    // Draw all bonuses
    void drawBonuses(SDL_Renderer *renderer) const {
        for(const Bonus& bonus : m_all_bonuses){
            bonus.draw(renderer);
        }
    }

    // Add one bonus
    void pushBonus(const Bonus& bonus){
        m_all_bonuses.push_back(bonus);
    }

    // Remove one bonus by index 
    void removeBonus(size_t index){
        if(index < m_all_bonuses.size()){
            m_all_bonuses.erase(m_all_bonuses.begin() + static_cast<std::vector<Bonus>::difference_type>(index));
        }
    }

    // Clear all bonuses
    void resetBonuses() {
        m_all_bonuses.clear();
    }

    // Get bonuses
    const std::vector<Bonus>& getBonuses() const {
        return m_all_bonuses;
    }

    // Get the total number of bonuses
    int getNumBonuses() const {
        return m_all_bonuses.size();
    }

    // Get a specific bonus by index
    const Bonus& getBonus(size_t index) const {
        if (index < m_all_bonuses.size()) {
            return m_all_bonuses[index];
        }
        // Return a reference to an invalid bonus if index is out of range
        throw std::out_of_range("Invalid index for getting bonus");
    }

private:
    int m_screenWidth;
    int m_screenHeight;
    // Vector of bonuses
    std::vector<Bonus> m_all_bonuses;
};

#endif // BONUSES_HPP

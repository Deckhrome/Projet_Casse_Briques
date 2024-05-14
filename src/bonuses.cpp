#include "bonuses.hpp"
#include <algorithm>

Bonuses::Bonuses(int screenWidth, int screenHeight) : m_screenWidth(screenWidth), m_screenHeight(screenHeight){};

void Bonuses::update(float deltaTime)
{
    // m_all_bonuses.erase(std::remove_if(m_all_bonuses.begin(), m_all_bonuses.end(), [](const Bonus &bonus)
    //                                    { return !bonus.isActive(); }),
    //                     m_all_bonuses.end());
    for (size_t i = 0; i < m_all_bonuses.size(); i++)
    {
        if (m_all_bonuses[i].update(deltaTime) >= m_screenHeight)
        {
            removeBonus(i);
        }
        if (!m_all_bonuses[i].isActive())
        {
            removeBonus(i);
        }
    }
}

void Bonuses::drawBonuses(SDL_Renderer *renderer) const
{
    for (const Bonus &bonus : m_all_bonuses)
    {
        bonus.draw(renderer);
    }
}

void Bonuses::pushBonus(const Bonus &bonus)
{
    m_all_bonuses.push_back(bonus);
}

void Bonuses::removeBonus(size_t index)
{
    if (index < m_all_bonuses.size())
    {
        m_all_bonuses.erase(m_all_bonuses.begin() + static_cast<std::vector<Bonus>::difference_type>(index));
    }
}

void Bonuses::resetBonuses()
{
    m_all_bonuses.clear();
}

std::vector<Bonus> &Bonuses::getBonuses()
{
    return m_all_bonuses;
}

int Bonuses::getNumBonuses() const
{
    return m_all_bonuses.size();
}

const Bonus &Bonuses::getBonus(size_t index) const
{
    if (index < m_all_bonuses.size())
    {
        return m_all_bonuses[index];
    }
    // Return a reference to an invalid bonus if index is out of range
    throw std::out_of_range("Invalid index for getting bonus");
}
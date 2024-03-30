#ifndef BRICKS_HPP
#define BRICKS_HPP

#include <vector>
#include "brick.hpp"

class Bricks
{
private:
    std::vector<Brick> m_all_bricks;

public:
    Bricks(int rows, int cols, int screenWidth, int screenHeight) { initBricks(rows, cols, screenWidth, screenHeight / 4); } // Constructeur par défaut

    // init with rectangle brick
    void initBricks(int rows, int cols, int width, int height);

    // add Brick
    void addBrick(const Brick &brick)
    {
        m_all_bricks.push_back(brick);
    }

    void drawBricks(SDL_Renderer *renderer)
    {
        for (auto brick : m_all_bricks)
        {
            if (brick.getDurability() > 0)
            {
                brick.draw(renderer);
            }
        }
    }

    // Remove brick
    void removeBrick(size_t index)
    {
        if (index < m_all_bricks.size())
        {
            m_all_bricks.erase(m_all_bricks.begin() + static_cast<std::vector<Brick>::difference_type>(index));
        }
    }

    void setBrickDurability(size_t index, int newDurability)
    {
        m_all_bricks[index].setDurability(newDurability);
    }

    // Number of brick
    int getTotalBricks() const
    {
        return m_all_bricks.size();
    }

    // Get brick
    Brick &getBrick(int index)
    {
        return m_all_bricks[index];
    }

    // Get all bricks
    const std::vector<Brick> &getAllBricks() const
    {
        return m_all_bricks;
    }
};

#endif // BRICKS_HPP

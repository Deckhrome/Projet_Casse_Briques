#ifndef BRICKS_HPP
#define BRICKS_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "brick.hpp"

class Bricks
{
private:
    std::vector<Brick> m_all_bricks;
    int m_screenWidth;
    int m_screenHeight;
    int m_padding;
    int m_brickWidth;
    int m_brickHeight;

public:
    Bricks(int screenWidth, int screenHeight, int padding) : m_screenWidth(screenWidth), m_screenHeight(screenHeight), m_padding(padding) {} // Default constructor

    // Init with ASCII file
    void initWithFile(const std::string path);
    // Calculate brick width and height
    void initBrickWidthAndHeight(std::ifstream &file);
    // Add brick
    void addBrick(const Brick &brick)
    {
        m_all_bricks.push_back(brick);
    }

    void drawBricks(SDL_Renderer *renderer);

    // Reset
    void resetBricks()
    {
        m_all_bricks.clear();
    }

    // Remove brick
    void removeBrick(size_t index)
    {
        if (index < m_all_bricks.size())
        {
            m_all_bricks.erase(m_all_bricks.begin() + static_cast<std::vector<Brick>::difference_type>(index));
        }
    }

    // Set brick durability
    void setBrickDurability(size_t index, int newDurability) { m_all_bricks[index].setDurability(newDurability);}

    // Number of brick
    int getTotalBricks() const { return m_all_bricks.size();}

    // Getters
    Brick &getBrick(int index){ return m_all_bricks[index]; }
    const std::vector<Brick> &getAllBricks() const { return m_all_bricks; }
};

#endif // BRICKS_HPP

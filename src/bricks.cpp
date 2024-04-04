#include "bricks.hpp"

#define DURABILITY 61

void Bricks::initBrickWidthAndHeight(std::ifstream &file)
{
    int countRows = 0;
    int countCols = 0;
    std::string line;
    while (std::getline(file, line))
    {
        ++countRows;
        if (countRows == 1)
        {
            countCols = line.size();
        }
    }
    // Calculate Brick
    m_brickWidth = (m_screenWidth - (countCols + 1) * m_padding) / countCols;
    m_brickHeight = (m_screenHeight / 3 - (countRows + 1) * m_padding) / countRows;
    file.clear();
    file.seekg(0, std::ios::beg);
}

void Bricks::initWithFile(const std::string path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << path << std::endl;
        return;
    }
    initBrickWidthAndHeight(file);
    std::string line;
    int y = 0; // Starting position
    while (std::getline(file, line))
    {
        int x = m_padding;
        for (char brickChar : line)
        {
            if (brickChar == 'B')
            {
                Brick brick(x, y, m_brickWidth, m_brickHeight, DURABILITY);
                addBrick(brick);
            }
            x += m_brickWidth + m_padding; // Next column
        }
        y += m_brickHeight + m_padding; // Next line
    }

    file.close();
}

void Bricks::drawBricks(SDL_Renderer *renderer)
{
    for (auto brick : m_all_bricks)
    {
        if (brick.getDurability() > 0)
        {
            brick.draw(renderer);
        }
    }
}
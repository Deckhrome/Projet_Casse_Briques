#include "bricks.hpp"

#define DURABILITY 100

void Bricks::initBricks(int rows, int cols, int width, int height)
{
    int padding = 4;

    int brickWidth = (width - (cols + 1) * padding) / cols;
    int brickHeight = (height - (rows + 1) * padding) / rows;

    // Starting position
    int startX = (width - (cols * (brickWidth + padding)));
    int startY = 50;

    // Create all bricks
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            int x = startX + col * (brickWidth + padding);
            int y = startY + row * (brickHeight + padding);

            Brick brick(x, y, brickWidth, brickHeight, DURABILITY);
            addBrick(brick);
        }
    }
}

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
    int y = 50; // Position de départ en Y
    while (std::getline(file, line))
    {
        int x = m_padding; // Position de départ en X
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
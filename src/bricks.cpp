#include "bricks.hpp"

#define DURABILITY 100

void Bricks::initBricks(int rows, int cols, int width, int height) {
    int padding = 20;

    int brickWidth = (width - (cols + 1) * padding) / cols;
    int brickHeight = (height - (rows + 1) * padding) / rows;

    // Position de départ pour le pavage de briques
    int startX = (width - (cols * (brickWidth + padding)));
    int startY = 50;

    // Boucle pour créer les briques
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            // Calcul de la position de chaque brique
            int x = startX + col * (brickWidth + padding);
            int y = startY + row * (brickHeight + padding);

            // Création de la brique et ajout à la collection
            Brick brick(x, y, brickWidth, brickHeight, DURABILITY);
            addBrick(brick);
        }
    }
}


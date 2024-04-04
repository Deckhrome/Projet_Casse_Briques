#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <math.h>
 
class Vector2D {
public:
    float x;
    float y;

    // Constructeur par défaut
    Vector2D() : x(0.0f), y(0.0f) {}

    // Constructeur avec initialisation explicite
    Vector2D(float xVal, float yVal) : x(xVal), y(yVal) {}

    // Surcharge des opérateurs
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    Vector2D operator*(float scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    // Méthodes pour calculer la magnitude et la normalisation du vecteur
    float magnitude() const {
        return sqrt(x * x + y * y);
    }

    Vector2D normalize() const {
        float mag = magnitude();
        if (mag != 0) {
            return *this * (1.0f / mag);
        } else {
            return *this;
        }
    }
};

#endif
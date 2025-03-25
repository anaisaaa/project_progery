#include "Math.h"

sf::Vector2f Math::NormalaizeVector(sf::Vector2f vector) 
{
    float m = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    sf::Vector2f normalaizedVector;
    normalaizedVector.x = vector.x / m;
    normalaizedVector.y = vector.y / m;
    return normalaizedVector;
}

bool Math::DidRectCollide(sf::FloatRect rect1, sf::FloatRect rect2)
{
    if (rect1.left + rect1.width > rect2.left &&
        rect2.left + rect2.width > rect1.left &&
        rect2.top + rect2.height > rect1.top &&
        rect1.top + rect1.height > rect2.top)
        return true;
    return false;
}

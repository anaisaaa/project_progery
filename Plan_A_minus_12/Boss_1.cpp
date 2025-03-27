#include "Boss_1.h"
#include <iostream>
#include "Math.h"

Boss_1::Boss_1(int hp, float speed) : health(hp), m_speed(speed)
{
}

Boss_1::~Boss_1()
{
}

void Boss_1::ChangeHealth(int damage)
{
	health += damage;
	healthText.setString(std::to_string(health));
}

void Boss_1::Initialize()
{
	//boundingRectangle.setFillColor(sf::Color::Transparent);
	//boundingRectangle.setOutlineColor(sf::Color::Blue);
	//boundingRectangle.setOutlineThickness(1);

	size = sf::Vector2i(38, 78);
}

void Boss_1::Load(float X, float Y)
{
    if (font.loadFromFile("Assets/Fonts/arial.ttf")) {
        //std::cout << "Font loaded\n";
        healthText.setFont(font);
        healthText.setString(std::to_string(health));
    }
    else {
        //std::cout << "Font load ERROR\n";
    }
    if (texture.loadFromFile("Assets/Boss_1/Textures/Boss_1.png"))
    {
        //std::cout << "Boss_1 Loaded\n";
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(X, Y));

        /*int XIndex = 1;
        int YIndex = 2;

        sprite.setTextureRect(sf::IntRect(XIndex * size.x, YIndex * size.y, size.x, size.y));*/
        sprite.scale(sf::Vector2f(10, 1));

        //boundingRectangle.setSize(sf::Vector2f(size.x * sprite.getScale().x, size.y * sprite.getScale().y));
    }
}

void Boss_1::Update(const sf::Vector2f& target, double deltaTime)
{
    if (health > 0) {
        direction = Math::NormalaizeVector(target - sprite.getPosition());
        sprite.setPosition(sprite.getPosition() + direction * m_speed * (float)deltaTime);
        //boundingRectangle.setPosition(sprite.getPosition());
        healthText.setPosition(sprite.getPosition());
    }
}

void Boss_1::Draw(sf::RenderWindow& window)
{
    if (health > 0) {
        window.draw(sprite);
        window.draw(boundingRectangle);
        window.draw(healthText);
    }
}

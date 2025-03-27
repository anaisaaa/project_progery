#pragma once

#include <SFML/Graphics.hpp>
class Boss_2
{
private:
	sf::Texture texture;
	sf::Vector2f direction;
	sf::Text healthText;
	sf::Font font;
	float m_speed;
public:
	sf::Sprite sprite;
	sf::RectangleShape boundingRectangle;
	sf::Vector2i size;

	int health;

public:
	Boss_2(int hp, float speed);
	~Boss_2();

	void ChangeHealth(int hp);
	void Initialize();
	void Load(float X, float Y);
	void Update(const sf::Vector2f& target, double deltaTime);
	void Draw(sf::RenderWindow& window);

};

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class GoldenAtc
{
private:
	sf::Vector2f direction;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i size;
	int damage;
	float speed;
public:
	GoldenAtc();
	~GoldenAtc();
	void Initialize(const sf::Vector2f& position, const sf::Vector2f& target, float GoldenAtcSpeed);
	void Load();
	void Update(double deltaTime);
	void Draw(sf::RenderWindow& window);

	inline const sf::FloatRect GetGlobalBounds() { return sprite.getGlobalBounds(); }
};


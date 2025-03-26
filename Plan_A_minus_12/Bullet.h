#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Bullet
{
private:
	sf::Vector2f direction;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i size;
	int damage;
	float speed;
public:
	Bullet();
	~Bullet();
	void Initialize(const sf::Vector2f& position,const sf::Vector2f& target, float BulletSpeed);
	void Load();
	void Update(double deltaTime);
	void Draw(sf::RenderWindow& window);

	inline const sf::FloatRect GetGlobalBounds() { return sprite.getGlobalBounds(); }
};


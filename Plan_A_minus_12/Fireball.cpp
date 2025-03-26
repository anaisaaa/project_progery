#include "Fireball.h"
#include "Math.h"

Fireball::Fireball(): speed(0), damage(0)
{
}

Fireball::~Fireball()
{
}

void Fireball::Initialize(const sf::Vector2f& position, const sf::Vector2f& target, float FireballSpeed)
{
	speed = FireballSpeed;
	sprite.setPosition(position);
	direction = Math::NormalaizeVector(target - position);
	size = sf::Vector2i(78, 70);
}

void Fireball::Load()
{
	if (texture.loadFromFile("assets/attack/fireball.png"))
	{
		//std::cout << "Shuriken loaded\n";
		sprite.setTexture(texture);

		int XIndex = 0;
		int YIndex = 0;
		//32, 0, 32, 29 
		sprite.setTextureRect(sf::IntRect(XIndex * size.x, YIndex * size.y, size.x, size.y));
		//sprite.scale(sf::Vector2f(2, 2));
	}
}

void Fireball::Update(double deltaTime)
{
	sprite.setPosition(sprite.getPosition() + direction * speed * (float)deltaTime);
}

void Fireball::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

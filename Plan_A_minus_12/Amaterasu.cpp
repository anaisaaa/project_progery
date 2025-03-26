#include "Amaterasu.h"
#include "Math.h"
Amaterasu::Amaterasu() : speed(0), damage(0)
{
}

Amaterasu::~Amaterasu()
{
}

void Amaterasu::Initialize(const sf::Vector2f& position, const sf::Vector2f& target, float BulletSpeed)
{
	speed = BulletSpeed;
	sprite.setPosition(position);
	direction = Math::NormalaizeVector(target - position);
	size = sf::Vector2i(58, 58);
}

void Amaterasu::Load()
{
	if (texture.loadFromFile("assets/attack/amaterasu.png"))
	{
		std::cout << "Amaterasu loaded\n";
		sprite.setTexture(texture);

		int XIndex = 0;
		int YIndex = 0;
		//32, 0, 32, 29 
		sprite.setTextureRect(sf::IntRect(XIndex * size.x, YIndex * size.y, size.x, size.y));
		sprite.scale(sf::Vector2f(2, 2));
	}
}

void Amaterasu::Update(double deltaTime)
{
	sprite.setPosition(sprite.getPosition() + direction * speed * (float)deltaTime);
}

void Amaterasu::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

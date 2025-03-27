#include "Rasengun.h"
#include "Math.h"
Rasengun::Rasengun() : speed(0), damage(0)
{
}

Rasengun::~Rasengun()
{
}

void Rasengun::Initialize(const sf::Vector2f& position, const sf::Vector2f& target, float BulletSpeed)
{
	speed = BulletSpeed;
	sprite.setPosition(position);
	direction = Math::NormalaizeVector(target - position);
	size = sf::Vector2i(34, 34);
}

void Rasengun::Load()
{
	if (texture.loadFromFile("assets/attack/rasengun.png"))
	{
		std::cout << "Rasengun loaded\n";
		sprite.setTexture(texture);

		int XIndex = 0;
		int YIndex = 0;
		//32, 0, 32, 29 
		sprite.setTextureRect(sf::IntRect(XIndex * size.x, YIndex * size.y, size.x, size.y));
		sprite.scale(sf::Vector2f(2, 2));
	}
}

void Rasengun::Update(double deltaTime)
{
	sprite.setPosition(sprite.getPosition() + direction * speed * (float)deltaTime);
}

void Rasengun::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

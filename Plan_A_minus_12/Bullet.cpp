#include "Bullet.h"
#include "Math.h"
Bullet::Bullet() : speed(0), damage(0)
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize(const sf::Vector2f& position, const sf::Vector2f& target, float BulletSpeed)
{
	speed = BulletSpeed; 
	sprite.setPosition(position);
	direction = Math::NormalaizeVector(target - position);
	size = sf::Vector2i(32, 29);
}

void Bullet::Load()
{
	if (texture.loadFromFile("assets/attack/shuriken.png"))
	{
		//std::cout << "Shuriken loaded\n";
		sprite.setTexture(texture);

		int XIndex = 1;
		int YIndex = 0;
		//32, 0, 32, 29 
		sprite.setTextureRect(sf::IntRect(XIndex * size.x, YIndex * size.y, size.x, size.y));
		sprite.scale(sf::Vector2f(2, 2));
	}
}

void Bullet::Update(double deltaTime)
{
	sprite.setPosition(sprite.getPosition() + direction * speed * (float)deltaTime);
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

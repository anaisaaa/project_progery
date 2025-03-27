#include "Rasenshuriken.h"
#include "Math.h"

Rasenshuriken::Rasenshuriken(): speed(0), damage(0)
{
}

Rasenshuriken::~Rasenshuriken()
{
}

void Rasenshuriken::Initialize(const sf::Vector2f& position, const sf::Vector2f& target, 
	float RasenshurikenSpeed)
{
	speed = RasenshurikenSpeed;
	sprite.setPosition(position);
	direction = Math::NormalaizeVector(target - position);
	size = sf::Vector2i(142, 26);
}

void Rasenshuriken::Load()
{
	if (texture.loadFromFile("assets/attack/rasenshuriken.png"))
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

void Rasenshuriken::Update(double deltaTime)
{
	sprite.setPosition(sprite.getPosition() + direction * speed * (float)deltaTime);
}

void Rasenshuriken::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

#include "GoldenAtc.h"
#include "Math.h"

GoldenAtc::GoldenAtc(): speed(0), damage(0)
{
}

GoldenAtc::~GoldenAtc()
{
}

void GoldenAtc::Initialize(const sf::Vector2f& position, const sf::Vector2f& target, float GoldenAtcSpeed)
{
	speed = GoldenAtcSpeed;
	sprite.setPosition(position);
	direction = Math::NormalaizeVector(target - position);
	size = sf::Vector2i(60, 54);
}

void GoldenAtc::Load()
{
	if (texture.loadFromFile("assets/attack/goldenAtc.png"))
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

void GoldenAtc::Update(double deltaTime)
{
	sprite.setPosition(sprite.getPosition() + direction * speed * (float)deltaTime);
}

void GoldenAtc::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

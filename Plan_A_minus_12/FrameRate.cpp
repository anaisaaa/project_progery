#include "FrameRate.h"
#include <iostream>
FrameRate::FrameRate() : timer(0)
{
}

FrameRate::~FrameRate()
{
}

void FrameRate::Initialize()
{
}

void FrameRate::Load()
{
    if (font.loadFromFile("Assets/Fonts/arial.ttf")) {
        std::cout << "Font loaded\n";
        frameRateText.setFont(font);
    }
    else {
        std::cout << "Font load ERROR\n";
    }
}

void FrameRate::Update(double deltaTime)
{
    timer += deltaTime;
    if (timer >= 100.0)
    {
        float fps = 1000.0 / deltaTime;
        frameRateText.setString("FPS: " + std::to_string((int)fps) +
            " frame time: " + std::to_string((int)deltaTime));
        timer = 0;
    }
}

void FrameRate::Draw(sf::RenderWindow& window)
{
    window.draw(frameRateText); 
}

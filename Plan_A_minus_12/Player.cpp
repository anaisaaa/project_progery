#include "Player.h"
#include <iostream>
#include "Math.h"
#include <algorithm>


Player::Player() :
    playerSpeed(0.4f), hp(100), chakra(100), maxHP(100), maxChakra(100),
    healTimer(0), plusChacraTimer(0),
    playerLVL(0), buffLVL(0), toLVLup(25),
    bulletMaxFireRate(250.0f), bulletFireRateTimer(0),
    skeletonMaxDamadgeRate(1000.0f), skeletonDamageRate(0),
    boss1MaxDamadgeRate(1000.0f), boss1DamageRate(0),
    boss2MaxDamadgeRate(1000.0f), boss2DamageRate(0),
    rasengunMaxFireRate(1000.0f), rasengunFireRateTimer(0),
    amaterasuMaxFireRate(5000.0f), amaterasuFireRateTimer(0),
    fireballMaxFireRate(700.0f), fireballFireRateTimer(0),
    goldenAtclMaxFireRate(3000.0f), goldenAtcFireRateTimer(0),
    rasenshurikenlMaxFireRate(2600.0f), rasenshurikenFireRateTimer(0)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
    //boundingRectangle.setFillColor(sf::Color::Transparent); 
    //boundingRectangle.setOutlineColor(sf::Color::Red); 
    //boundingRectangle.setOutlineThickness(1);
    size = sf::Vector2i(24, 32);  
}

void Player::Load()
{
    
    if (texture.loadFromFile("Assets/Player/Textures/FumikoSpritesheet.png")) {
        std::cout << "Hero Loaded\n"; 
        
        if (font.loadFromFile("Assets/Fonts/arial.ttf"))
        {
            std::cout << "Font loaded\n";
            healthText.setFont(font);
            healthText.setString(std::to_string(hp));

            chakraText.setFont(font);
            chakraText.setString(std::to_string(chakra));

            lvlText.setFont(font);
            lvlText.setString(std::to_string(playerLVL));
        }
        
        int XIndex = 4;
        int YIndex = 2;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(XIndex * size.x, YIndex * size.y, size.x, size.y));
        sprite.setPosition(sf::Vector2f(100, 100));

        sprite.scale(sf::Vector2f(2, 2));
        //boundingRectangle.setSize(sf::Vector2f(size.x * sprite.getScale().x, size.y * sprite.getScale().y));
    }
    else
        std::cout << "ERROR\n";
}

void Player::Update(double deltaTime, sf::Vector2f& mousePosition)
{
    healTimer += deltaTime;
    if (healTimer >= 1000.0f && hp < maxHP)
    {
        hp++;
        healTimer = 0;
    }
    plusChacraTimer += deltaTime;
    if (plusChacraTimer >= 1000.0f && chakra < maxChakra)
    {
        chakra++;
        plusChacraTimer = 0;
    }


    if (buffLVL >= toLVLup)
    {
        playerLVL++;
        toLVLup += 25;
        buffLVL = 0;
        //20 это пока наша константа
        hp = maxHP + 20 * playerLVL;
        chakra = maxChakra + 20 * playerLVL;
        maxHP = maxHP + 20 * playerLVL;
        maxChakra = maxChakra + 20 * playerLVL;
    }
    //Moving up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sprite.getPosition().y > 0) {
        //take current position of image
        sf::Vector2f position = sprite.getPosition();
        //add pixels to coordinate to move it
        sprite.setPosition(position + sf::Vector2f(0, -1) * playerSpeed * (float)deltaTime);
    }
    //Moving down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sprite.getPosition().y + size.y * sprite.getScale().y < 1080) {
        sf::Vector2f position = sprite.getPosition();
        sprite.setPosition(position + sf::Vector2f(0, 1) * playerSpeed * (float)deltaTime);
    }
    //Moving left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sprite.getPosition().x > 0) {
        sf::Vector2f position = sprite.getPosition();
        sprite.setPosition(position + sf::Vector2f(-1, 0) * playerSpeed * (float)deltaTime);
    }
    //Moving right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sprite.getPosition().x + size.x * sprite.getScale().x < 1920) {
        sf::Vector2f position = sprite.getPosition();
        sprite.setPosition(position + sf::Vector2f(1, 0) * playerSpeed * (float)deltaTime);
    }
    //--------------------------BULLET--------------------------
    bulletFireRateTimer += deltaTime;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && bulletFireRateTimer >= bulletMaxFireRate)
    {
        bullets.push_back(new Bullet());
        int i = bullets.size() - 1;
        bullets[i]->Initialize(sprite.getPosition(), mousePosition, 0.5f);
        bullets[i]->Load();
        bulletFireRateTimer = 0;
    }
    for (size_t i = 0; i < bullets.size(); ++i)
    {
        bullets[i]->Update(deltaTime);
        
    }
    //--------------------------BULLET--------------------------
    //--------------------------RASENGUN------------------------
    rasengunFireRateTimer += deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && rasengunMaxFireRate <= rasengunFireRateTimer
        && chakra >= 15)
    {
        rasenguns.push_back(new Rasengun());
        int i = rasenguns.size() - 1;
        rasenguns[i]->Initialize(sprite.getPosition(), mousePosition, 0.5f);
        rasenguns[i]->Load();
        rasengunFireRateTimer = 0;

        chakra -= 15;
    }
    for (size_t i = 0; i < rasenguns.size(); ++i)
    {
        rasenguns[i]->Update(deltaTime);

    }
    //--------------------------RASENGUN------------------------
    //--------------------------AMATERASU------------------------
    amaterasuFireRateTimer += deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && amaterasuMaxFireRate <= amaterasuFireRateTimer
        && chakra >= 30)
    {
        amaterasus.push_back(new Amaterasu());
        int i = amaterasus.size() - 1;
        amaterasus[i]->Initialize(sprite.getPosition(), mousePosition, 0.5f);
        amaterasus[i]->Load();
        amaterasuFireRateTimer = 0;

        chakra -= 30;
    }
    for (size_t i = 0; i < amaterasus.size(); i++)
    {
        amaterasus[i]->Update(deltaTime);
    }
    //--------------------------AMATERASU------------------------
    //--------------------------FIREBALL------------------------
    fireballFireRateTimer += deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && fireballMaxFireRate <= fireballFireRateTimer
        && chakra >= 10)
    {
        fireball.push_back(new Fireball());
        int i = fireball.size() - 1;
        fireball[i]->Initialize(sprite.getPosition(), mousePosition, 0.5f);
        fireball[i]->Load();
        fireballFireRateTimer = 0;

        chakra -= 10;
    }
    for (size_t i = 0; i < fireball.size(); i++)
    {
        fireball[i]->Update(deltaTime);
    }
    //--------------------------FIREBALL------------------------
    //--------------------------GOLDEN--------------------------
    goldenAtcFireRateTimer += deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && goldenAtclMaxFireRate <= goldenAtcFireRateTimer
        && chakra >= 25)
    {
        goldenAtc.push_back(new GoldenAtc());
        int i = goldenAtc.size() - 1;
        goldenAtc[i]->Initialize(sprite.getPosition(), mousePosition, 0.5f);
        goldenAtc[i]->Load();
        goldenAtcFireRateTimer = 0;

        chakra -= 25;
    }
    for (size_t i = 0; i < goldenAtc.size(); i++)
    {
        goldenAtc[i]->Update(deltaTime);
    }
    //--------------------------GOLDEN--------------------------
    //--------------------------rasenshuriken--------------------------
    rasenshurikenFireRateTimer += deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && rasenshurikenlMaxFireRate <= rasenshurikenFireRateTimer
        && chakra >= 20)
    {
        rasenshuriken.push_back(new Rasenshuriken());
        int i = rasenshuriken.size() - 1;
        rasenshuriken[i]->Initialize(sprite.getPosition(), mousePosition, 0.5f);
        rasenshuriken[i]->Load();
        rasenshurikenFireRateTimer = 0;

        chakra -= 20;
    }
    for (size_t i = 0; i < rasenshuriken.size(); i++)
    {
        rasenshuriken[i]->Update(deltaTime);
    }
    //--------------------------rasenshuriken--------------------------
    //--------------------------HEALTH--------------------------
    healthText.setString("HP: " + std::to_string(hp) + "/" + std::to_string(maxHP));
    //healthText.setPosition(sprite.getPosition());
    healthText.setPosition(1, 50);

    chakraText.setString("Chakra: " + std::to_string(chakra) + "/" + std::to_string(maxChakra));
    chakraText.setPosition(1, 100);

    lvlText.setString("LVL: " + std::to_string(playerLVL));
    lvlText.setPosition(1, 150);

    //boundingRectangle.setPosition(sprite.getPosition());
}

void Player::UpdateSkeleton(double deltaTime, Skeleton*& skeleton)
{
    //--------------------------BULLET--------------------------
    for (size_t i = 0; i < bullets.size(); ++i)
    {
        if (skeleton->health > 0) {
            if (Math::DidRectCollide(bullets[i]->GetGlobalBounds(), skeleton->sprite.getGlobalBounds())) 
            {
                skeleton->ChangeHealth(-(10 + 2 * playerLVL)); 
                bullets.erase(bullets.begin() + i); 
                //std::cout << "Collision" << "\n";
            }
        }
    }
    //--------------------------BULLET--------------------------
    //--------------------------RASENGUN------------------------
    for (size_t i = 0; i < rasenguns.size(); ++i)
    {
        if (skeleton->health > 0) {
            if (Math::DidRectCollide(rasenguns[i]->GetGlobalBounds(), skeleton->sprite.getGlobalBounds()))
            {
                skeleton->ChangeHealth(-(30 + 5 * playerLVL));
                rasenguns.erase(rasenguns.begin() + i);
                std::cout << "Collision" << "\n";
            }
        }
    }
    //--------------------------RASENGUN------------------------
    //--------------------------AMATERASUS----------------------
    for (size_t i = 0; i < amaterasus.size(); ++i)
    {
        if (skeleton->health > 0) {
            if (Math::DidRectCollide(amaterasus[i]->GetGlobalBounds(), skeleton->sprite.getGlobalBounds()))
            {
                skeleton->ChangeHealth(-(100 + 10 * playerLVL));
                amaterasus.erase(amaterasus.begin() + i);
                std::cout << "Collision" << "\n";
            }
        }
    }
    //--------------------------AMATERASUS----------------------
    //--------------------------FIREBALL----------------------
    for (size_t i = 0; i < fireball.size(); ++i)
    {
        if (skeleton->health > 0) {
            if (Math::DidRectCollide(fireball[i]->GetGlobalBounds(), skeleton->sprite.getGlobalBounds()))
            {
                skeleton->ChangeHealth(-(15 + 3 * playerLVL));
                fireball.erase(fireball.begin() + i);
                std::cout << "Collision" << "\n";
            }
        }
    }
    //--------------------------FIREBALL----------------------
    //--------------------------GOLDEN----------------------
    for (size_t i = 0; i < goldenAtc.size(); ++i)
    {
        if (skeleton->health > 0) {
            if (Math::DidRectCollide(goldenAtc[i]->GetGlobalBounds(), skeleton->sprite.getGlobalBounds()))
            {
                skeleton->ChangeHealth(-(70 + 7 * playerLVL));
                goldenAtc.erase(goldenAtc.begin() + i);
                std::cout << "Collision" << "\n";
            }
        }
    }
    //--------------------------GOLDEN----------------------
    //--------------------------rasenshuriken----------------------
    for (size_t i = 0; i < rasenshuriken.size(); ++i)
    {
        if (skeleton->health > 0) {
            if (Math::DidRectCollide(rasenshuriken[i]->GetGlobalBounds(), skeleton->sprite.getGlobalBounds()))
            {
                skeleton->ChangeHealth(-(50 + 5 * playerLVL));
                rasenshuriken.erase(rasenshuriken.begin() + i);
                std::cout << "Collision" << "\n";
            }
        }
    }
    //--------------------------rasenshuriken----------------------
    //--------------------------SKELETON------------------------
    boundingRectangle.setPosition(sprite.getPosition());
    skeletonDamageRate += deltaTime;
    if (Math::DidRectCollide(skeleton->sprite.getGlobalBounds(), this->sprite.getGlobalBounds()) && skeletonDamageRate >= skeletonMaxDamadgeRate)
    {
        hp -= 10;
        skeletonDamageRate = 0;
        //std::cout << "Collision" << "\n";
    }
    //healthText.setString("HP: " + std::to_string(hp) + "/100");
    //healthText.setPosition(sprite.getPosition());
    //--------------------------SKELETON------------------------
}

void Player::Update_Boss_1(double deltaTime, Boss_1*& boss_1)
{
    //--------------------------BULLET--------------------------
    for (size_t i = 0; i < bullets.size(); ++i)
    {
        //bullets[i]->Update(deltaTime);
        if (boss_1->health > 0) {
            if (Math::DidRectCollide(bullets[i]->GetGlobalBounds(), boss_1->sprite.getGlobalBounds()))
            {
                boss_1->ChangeHealth(-(10 + 2 * playerLVL));
                bullets.erase(bullets.begin() + i);
                //std::cout << "Collision" << "\n";
            }
        }
    }
    //--------------------------BULLET--------------------------
    //--------------------------RASENGUN------------------------
    for (size_t i = 0; i < rasenguns.size(); ++i)
    {
        if (boss_1->health > 0) {
            if (Math::DidRectCollide(rasenguns[i]->GetGlobalBounds(), boss_1->sprite.getGlobalBounds()))
            {
                boss_1->ChangeHealth(-(30 + 5 * playerLVL));
                rasenguns.erase(rasenguns.begin() + i);
                std::cout << "Collision" << "\n";
            }
        }
    }
    //--------------------------RASENGUN------------------------
    //--------------------------AMATERASUS----------------------
    for (size_t i = 0; i < amaterasus.size(); ++i)
    {
        if (boss_1->health > 0) {
            if (Math::DidRectCollide(amaterasus[i]->GetGlobalBounds(), boss_1->sprite.getGlobalBounds()))
            {
                boss_1->ChangeHealth(-(100 + 10 * playerLVL));
                amaterasus.erase(amaterasus.begin() + i);
                std::cout << "Collision" << "\n";
            }
        }
    }
    //--------------------------AMATERASUS----------------------
    //--------------------------BOSS1---------------------------
    boundingRectangle.setPosition(sprite.getPosition());
    boss1DamageRate += deltaTime;
    if (Math::DidRectCollide(boss_1->sprite.getGlobalBounds(), this->sprite.getGlobalBounds()) && boss1DamageRate >= boss1MaxDamadgeRate)
    {
        hp -= 70;
        boss1DamageRate = 0;
        //std::cout << "Collision" << "\n";
    }
    //healthText.setString(std::to_string(hp) + "/100");
    //healthText.setPosition(sprite.getPosition());
    //--------------------------BOSS1---------------------------
    //--------------------------FIREBALL----------------------
    for (size_t i = 0; i < fireball.size(); ++i)
    {
        if (boss_1->health > 0) {
            if (Math::DidRectCollide(fireball[i]->GetGlobalBounds(), boss_1->sprite.getGlobalBounds()))
            {
                boss_1->ChangeHealth(-(15 + 3 * playerLVL));
                fireball.erase(fireball.begin() + i);
                std::cout << "Collision" << "\n";
            }
        }
    }
    //--------------------------FIREBALL---------------------- 
    //--------------------------GOLDEN----------------------
    for (size_t i = 0; i < goldenAtc.size(); ++i) 
    { 
        if (boss_1->health > 0) { 
            if (Math::DidRectCollide(goldenAtc[i]->GetGlobalBounds(), boss_1->sprite.getGlobalBounds())) 
            { 
                boss_1->ChangeHealth(-(70 + 7 * playerLVL));
                goldenAtc.erase(goldenAtc.begin() + i); 
                std::cout << "Collision" << "\n"; 
            }
        }
    }
    //--------------------------GOLDEN----------------------
    //--------------------------rasenshuriken----------------------
    for (size_t i = 0; i < rasenshuriken.size(); ++i)
    {
        if (boss_1->health > 0) {
            if (Math::DidRectCollide(rasenshuriken[i]->GetGlobalBounds(), boss_1->sprite.getGlobalBounds()))
            {
                boss_1->ChangeHealth(-(50 + 5 * playerLVL));
                rasenshuriken.erase(rasenshuriken.begin() + i);
                std::cout << "Collision" << "\n";
            }
        }
    }
    //--------------------------rasenshuriken----------------------
}

void Player::Update_Boss_2(double deltaTime, Boss_2*& boss_2)
{
    for (size_t i = 0; i < bullets.size(); ++i)
    {
        //bullets[i]->Update(deltaTime);
        if (boss_2->health > 0) {
            if (Math::DidRectCollide(bullets[i]->GetGlobalBounds(), boss_2->sprite.getGlobalBounds()))
            {
                boss_2->ChangeHealth(-(10 + 2 * playerLVL));
                bullets.erase(bullets.begin() + i);
                //std::cout << "Collision" << "\n";
            }
        }
    }
    //--------------------------RASENGUN------------------------
    for (size_t i = 0; i < rasenguns.size(); ++i)
    {
        if (boss_2->health > 0) {
            if (Math::DidRectCollide(rasenguns[i]->GetGlobalBounds(), boss_2->sprite.getGlobalBounds()))
            {
                boss_2->ChangeHealth(-(30 + 5 * playerLVL));
                rasenguns.erase(rasenguns.begin() + i);
                std::cout << "Collision" << "\n";
            }
        }
    }
    //--------------------------RASENGUN------------------------
    //--------------------------AMATERASUS----------------------
    for (size_t i = 0; i < amaterasus.size(); ++i)
    {
        if (boss_2->health > 0) {
            if (Math::DidRectCollide(amaterasus[i]->GetGlobalBounds(), boss_2->sprite.getGlobalBounds()))
            {
                boss_2->ChangeHealth(-(100 + 10 * playerLVL));
                amaterasus.erase(amaterasus.begin() + i);
                std::cout << "Collision" << "\n";
            }
        }
    }
    //--------------------------AMATERASUS----------------------
    //--------------------------FIREBALL----------------------
    for (size_t i = 0; i < fireball.size(); ++i)
    {
        if (boss_2->health > 0) {
            if (Math::DidRectCollide(fireball[i]->GetGlobalBounds(), boss_2->sprite.getGlobalBounds()))
            {
                boss_2->ChangeHealth(-(100 + 20 * playerLVL));
                fireball.erase(fireball.begin() + i);
                std::cout << "Collision" << "\n";
            }
        }
    }
    //--------------------------BOSS2---------------------------
    boundingRectangle.setPosition(sprite.getPosition());
    boss2DamageRate += deltaTime;
    if (Math::DidRectCollide(boss_2->sprite.getGlobalBounds(), this->sprite.getGlobalBounds()) && boss2DamageRate >= boss2MaxDamadgeRate)
    {
        hp -= 105;
        boss2DamageRate = 0;
        //std::cout << "Collision" << "\n";
    }
    //healthText.setString(std::to_string(hp) + "/100");
    //healthText.setPosition(sprite.getPosition());
    //--------------------------BOSS2---------------------------
    //--------------------------GOLDEN----------------------
    for (size_t i = 0; i < goldenAtc.size(); ++i)
    {
        if (boss_2->health > 0) {
            if (Math::DidRectCollide(goldenAtc[i]->GetGlobalBounds(), boss_2->sprite.getGlobalBounds()))
            {
                boss_2->ChangeHealth(-(50 + 5 * playerLVL));
                goldenAtc.erase(goldenAtc.begin() + i);
                std::cout << "Collision" << "\n";
            }
        }
    }
    //--------------------------GOLDEN----------------------
    //--------------------------rasenshuriken----------------------
    for (size_t i = 0; i < rasenshuriken.size(); ++i)
    {
        if (boss_2->health > 0) {
            if (Math::DidRectCollide(rasenshuriken[i]->GetGlobalBounds(), boss_2->sprite.getGlobalBounds()))
            {
                boss_2->ChangeHealth(-(50 + 5 * playerLVL));
                rasenshuriken.erase(rasenshuriken.begin() + i);
                std::cout << "Collision" << "\n";
            }
        }
    }
    //--------------------------rasenshuriken----------------------
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(sprite); 
    window.draw(boundingRectangle);
    window.draw(healthText);
    window.draw(chakraText);
    window.draw(lvlText);

    for (size_t i = 0; i < bullets.size(); ++i) 
        bullets[i]->Draw(window); 
    for (size_t i = 0; i < rasenguns.size(); ++i)
        rasenguns[i]->Draw(window);
    for (size_t i = 0; i < amaterasus.size(); ++i)
        amaterasus[i]->Draw(window);
    for (size_t i = 0; i < fireball.size(); ++i)
        fireball[i]->Draw(window);
    for (size_t i = 0; i < goldenAtc.size(); ++i)
        goldenAtc[i]->Draw(window);
    for (size_t i = 0; i < rasenshuriken.size(); ++i)
        rasenshuriken[i]->Draw(window);
}

void Player::SetBufLvl(int buf)
{
    buffLVL += buf;
}

int Player::GetHp()
{
    return hp;
}

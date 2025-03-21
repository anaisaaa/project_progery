#include <SFML/Graphics.hpp>  
#include <iostream>
#include "Player.h"
#include "Skeleton.h"
#include "FrameRate.h"
#include "Map.h"
#include "MapLoader.h"
#include <vector>
#include <random>
#include "Boss_1.h"
#include "Boss_2.h"
int main()
{
    //--------------INITIALIZE---------------
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    //create window                      width, height, window header
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Dungeon master: Deep Dark Fantasy", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    //--------------INITIALIZE---------------
    FrameRate frameRate;
    sf::Texture dota;
    sf::Sprite dotaMap;
    dota.loadFromFile("Assets/image.png");
    dotaMap.setTexture(dota);
    dotaMap.setScale(sf::Vector2f(1.3f, 1.3f));



    int wave = 0;
    int skeletons_num = 4;
    int skeleton_hp = 100;

    std::vector<Skeleton*>skeletons;

    Boss_1* boss_1 = new Boss_1(3000, 0.3f);

    Boss_2* boss_2 = new Boss_2(7000, 0.35f);

    Player player;

    float SpeedOfSkelet= 0.3f;

    for (int i = 0; i < 4; i++)
    {
        skeletons.push_back(new Skeleton(skeleton_hp, SpeedOfSkelet));
    }
    
    MapLoader mapLoader;
    //--------------INITIALIZE---------------
    frameRate.Initialize();
    for (int i = 0; i < 4; i++)
    {
        
        skeletons[i]->Initialize();
    }
    player.Initialize();  
    //--------------INITIALIZE---------------


    //--------------LOAD---------------
    frameRate.Load();
   
    srand(time(0));
    for (int i = 0; i < skeletons.size(); i++)
    {
        float X = (rand() * rand() + rand() + 200) % 1820, Y = (rand() * rand() + rand() + 200) % 980;
        std::cout << X << ' ' << Y << '\n';
        while (abs(X - 100) < 100 && abs(Y - 100) < 100)
        {
            X = (rand() * rand() + rand() + 200) % 1820, Y = (rand() * rand() + rand() + 200) % 980;
        }
        skeletons[i]->Load(X, Y);
    }
   
    player.Load();
    //--------------LOAD---------------
    sf::Clock clock;
    while(window.isOpen()) 
    {
        if (player.GetHp() <= 0) {
            exit(0);
        }
        sf::Time deltaTimer = clock.restart();
        double deltaTime = deltaTimer.asMicroseconds()/1000.0;
        

        //--------------Update---------------
        sf::Event event; 
        while (window.pollEvent(event)) 
        {
             
            if (event.type == sf::Event::Closed)  
                window.close(); 
        }
        sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window)); 

        frameRate.Update(deltaTime);
        player.Update(deltaTime, mousePosition);

        for (int i = 0; i < skeletons.size(); i++)
        {
            skeletons[i]->Update(player.sprite.getPosition(), deltaTime);
            player.UpdateSkeleton(deltaTime, skeletons[i]);

            if (skeletons[i]->health <= 0)
            {
                player.SetBufLvl(4);
                skeletons.erase(skeletons.begin() + i);
            }
        }

        if (skeletons.size() == 0 && wave < 3) 
        {
            skeletons.clear();
            skeletons_num++;
            skeleton_hp += 25;
            for (int i = 0; i < skeletons_num; i++) 
            {
                skeletons.push_back(new Skeleton(skeleton_hp, SpeedOfSkelet));  
                skeletons[i]->Initialize();  
            }
            for (int i = 0; i < skeletons.size(); i++) 
            { 
                float X = (rand() * rand() + rand() + 200) % 1820, Y = (rand() * rand() + rand() + 200) % 980; 
                std::cout << X << ' ' << Y << '\n'; 
                while (abs(X - 100) < 100 && abs(Y - 100) < 100) 
                {
                    X = (rand() * rand() + rand() + 200) % 1820, Y = (rand() * rand() + rand() + 200) % 980; 
                }
                skeletons[i]->Load(X, Y); 
            }

            wave++;
            std::cout << wave << '\n';
        }

        if (wave == 3 && skeletons.size() == 0)
        {
            boss_1->Initialize();
            boss_1->Load(800,600);
            boss_1->Draw(window);
            wave++;
        }

        if (wave == 4)
        {
            boss_1->Update(player.sprite.getPosition(), deltaTime);
            player.Update_Boss_1(deltaTime, boss_1);
        }

        if(boss_1->health <= 0 && wave == 4)
        {
            wave++;
            player.SetBufLvl(30);
            boss_1->~Boss_1();
        }

        if (skeletons.size() == 0 && wave > 4 && wave < 9)
        {
            skeletons.clear();
            skeletons_num++;
            skeleton_hp += 25;
            for (int i = 0; i < skeletons_num; i++)
            {
                skeletons.push_back(new Skeleton(skeleton_hp, SpeedOfSkelet));
                skeletons[i]->Initialize();
            }
            for (int i = 0; i < skeletons.size(); i++)
            {
                float X = (rand() * rand() + rand() + 200) % 1820, Y = (rand() * rand() + rand() + 200) % 980;
                std::cout << X << ' ' << Y << '\n';
                while (abs(X - 100) < 100 && abs(Y - 100) < 100)
                {
                    X = (rand() * rand() + rand() + 200) % 1820, Y = (rand() * rand() + rand() + 200) % 980;
                }
                skeletons[i]->Load(X, Y);
            }

            wave++;
        }

        if (wave == 9 && skeletons.size() == 0)
        {
            boss_2->Initialize();
            boss_2->Load(800, 600);
            wave++;
        }
        
        if (wave == 10)
        {
            boss_2->Update(player.sprite.getPosition(), deltaTime);
            player.Update_Boss_2(deltaTime, boss_2);
        }

        if (boss_2->health <= 0 && wave == 10)
        {
            boss_2->~Boss_2();
            player.SetBufLvl(50);
            wave++;
        }

        //--------------Update---------------
        
        //--------------Draw---------------
        window.clear(sf::Color::Black);  
        window.draw(dotaMap);
        for (int i = 0; i < skeletons.size(); i++)
        {
            if (skeletons[i]->health > 0)
            {
                skeletons[i]->Draw(window);
            }
            
        }
        player.Draw(window);
        if (boss_1)
        {
            boss_1->Draw(window);
        }
        if (boss_2)
        {
            boss_2->Draw(window);
        }
        frameRate.Draw(window); 
        window.display();  
        //--------------Draw---------------
    }
    return 0;
}
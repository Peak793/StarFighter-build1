#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<cstdlib>

class Enemy {
public:
	sf::Sprite eSprite;
	sf::Clock timer;
	sf::Clock timer1;
	RectangleShape innerHp;
	RectangleShape Hpbar;
	int hp;
	int hpmax;

	Enemy(Texture &eTex,sf::IntRect a,Vector2f pos)
	{
		/*if (!eTex.loadFromFile(imgdirectory))
			std::cerr << "Error\n";*/
		this->hpmax = rand()%2+1;
		this->hp = this->hpmax;
		this->innerHp.setSize(Vector2f(30, 5));
		this->Hpbar.setSize(Vector2f(30, 5));
		this->innerHp.setOrigin(this->innerHp.getSize().x/2,0);
		this->Hpbar.setOrigin(this->innerHp.getSize().x/2, 0);
		Hpbar.setFillColor(Color::Red);
		innerHp.setFillColor(Color::Magenta);
		eSprite.setTexture(eTex);
		eSprite.setTextureRect(a);
		eSprite.setOrigin(32, 32);
		eSprite.setScale(0.9f,0.9f);
		eSprite.setPosition(pos);
		Hpbar.setPosition(pos.x, pos.y + 40);
		innerHp.setPosition(pos.x, pos.y + 40);
	}
};
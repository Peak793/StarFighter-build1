#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
class Player {
public:
	sf::Sprite pSprite;
	int hp;
	int hpmax;
	Player() {
		//Default
	}
	Player(std::string imgDirectory, sf::IntRect &a)
	{
		this->hpmax = 5;
		this->hp = this->hpmax;
		if (!pTexture.loadFromFile(imgDirectory))
		{
			std::cerr << "Error\n";
		}
		pSprite.setTexture(pTexture);
		pSprite.setTextureRect(a);
	}

	void drawPlayer(sf::RenderWindow &window)
	{
		window.draw(pSprite);
	}

	void pAnimetion(sf::IntRect &a)
	{

		if (clock.getElapsedTime().asMilliseconds() > 100.f)
		{
			if (a.left == 192)
				a.left = 0;
			else
				a.left += 64;
			pSprite.setTextureRect(a);
			clock.restart();

		}

	}

	void moveplayer(float moveSpeed){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			pSprite.move(0, -moveSpeed);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			pSprite.move(0, moveSpeed);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			pSprite.move(-moveSpeed, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			pSprite.move(moveSpeed, 0);
	}

	void checkpos()
	{
		if (pSprite.getPosition().x < 32)
			pSprite.setPosition(32, pSprite.getPosition().y);
		if (pSprite.getPosition().x > 568)
			pSprite.setPosition(568, pSprite.getPosition().y);
		if (pSprite.getPosition().y <32)
			pSprite.setPosition(pSprite.getPosition().x, 32);
		if (pSprite.getPosition().y >868)
			pSprite.setPosition(pSprite.getPosition().x, 868);
	}
	
	void setOrigin()
	{
		pSprite.setOrigin(32,32);
	}
	
	void setpos(int x,int y)
	{
		pSprite.setPosition(x, y);
	}
	
	int getPosx()
	{
		return pSprite.getPosition().x;
	}

	int getPosy()
	{
		return pSprite.getPosition().y;
	}
private:
	sf::Texture pTexture;
	sf::Clock clock;
};
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy {
public:
	Enemy(std::string imgdirectory,sf::IntRect a)
	{
		if (!eTex.loadFromFile(imgdirectory))
			std::cerr << "Error\n";
		eSprite.setTexture(eTex);
		eSprite.setTextureRect(a);
	}
private:
	sf::Texture eTex;
	sf::Sprite eSprite;
};
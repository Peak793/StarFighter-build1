#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Bg {
public:
	Bg(std::string imgdirectory, sf::IntRect &a)
	{
		if (!bg.loadFromFile(imgdirectory))
			std::cerr << "Error\n";
		Sbg.setTexture(bg);
		Sbg.setTextureRect(a);		
		Sbg.setOrigin(0, 14270);
		Sbg.setPosition(0, 900);
	}

	void bgmove()
	{
			Sbg.move(0,3);
			if (Sbg.getPosition().y ==13000 )
			{	
				Sbg.setPosition(0, 900);
			}
	}

	void drawbg(sf::RenderWindow &window)
	{
		window.draw(Sbg);
	}

private:
	sf::Texture bg;
	sf::Sprite Sbg;
	sf::Clock n;
};
#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<SFML/Audio.hpp>
class Bullet {
public:
	Bullet(sf::Vector2f size,std::string bullettexture,std::string sound)
	{
		bullet.setSize(size);
		bullet.setOrigin(size.x/2,size.y/2);
		if (!btex.loadFromFile(bullettexture))
			std::cerr << "Error\n";
		if (!buffer.loadFromFile(sound))
			std::cerr << "Error\n";
		bullet.setTexture(&btex);
		Fsound.setBuffer(buffer);
	}

	void fire(int speed,sf::Vector2i &playerpos)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && a.getElapsedTime().asMilliseconds()>500)
		{
			bullet.setPosition(playerpos.x,playerpos.y-32);
			bulletvec.push_back(sf::RectangleShape(bullet));
			Fsound.play();
			a.restart();
		}
	}

	void Bmove(int bulletspeed)
	{
		for (int i = 0 ;i< bulletvec.size(); i++) 
		{
			bulletvec[i].move(0, -bulletspeed);
		}
		for (int i = 0; i < bulletvec.size(); i++)
		{
			if (bulletvec[i].getPosition().y < 32)
			{
				bulletvec.erase(bulletvec.begin() + i);
				break;
			}
		}
	}

	void bulletdraw(sf::RenderWindow &window)
	{
		for (int i = 0; i < bulletvec.size(); i++)
		{
			window.draw(bulletvec[i]);
		}
	}
private:
	sf::Texture btex;
	sf::RectangleShape bullet;
	std::vector<sf::RectangleShape> bulletvec;
	sf::Clock a;
	sf::SoundBuffer buffer;
	sf::Sound Fsound;
 };
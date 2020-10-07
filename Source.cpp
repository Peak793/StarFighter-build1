#include"SFML/System.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Window.hpp"
#include<iostream>
#include<vector>
#include<cstdlib>
#include <math.h>
#include "Player.h"
#include "Bullet.h"
#include "bg.h"
int main() 
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(600.f, 900.f), "StarFighter", sf::Style::Default);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(true);
	
	//player
		sf::IntRect pRect(0, 0, 64, 64);
		Player myPlayer("img/PlayerS.png",pRect);
		myPlayer.setOrigin();
		myPlayer.setpos(window.getSize().x / 2, window.getSize().y-64);
	
	//Bullet
		Bullet mybullet(sf::Vector2f(10, 20),"img/bullet.png","sounds/firesound.ogg");

	//Blackground
		sf::IntRect bgRect(0,0, 600, 27000);
		Bg blackground("img/long.png",bgRect);

	while (window.isOpen())
	{
		sf::Event event;
		sf::Vector2i playerpos(myPlayer.getPosx(), myPlayer.getPosy());
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
		}
		//update
			myPlayer.pAnimetion(pRect);
			myPlayer.moveplayer(5);
			mybullet.fire(15,playerpos);
			mybullet.Bmove(15);
			blackground.bgmove();
		//draw
		window.clear();
		blackground.drawbg(window);
		myPlayer.drawPlayer(window);
		mybullet.bulletdraw(window);
		window.display();
	}
}
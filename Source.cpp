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
#include "Enemy.h"
//#include "Enemy.h"

int main() 
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(600.f, 900.f), "StarFighter", sf::Style::Default);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(true);
	//font
	Font font;
	font.loadFromFile("font/kenvector_future.ttf");

	//bullet
	Bullet mybullet(sf::Vector2f(10, 20), "img/bullet.png", "sounds/firesound.ogg");
restart:
	long long playerscore=0;
	Clock timer;
	Text Scoretext("SCORE : " + std::to_string(playerscore),font,20);
	Scoretext.setPosition(400,0);

	RectangleShape Hpbar;
	RectangleShape Hpbarback;
	Hpbar.setFillColor(Color::Red);
	Hpbar.setPosition(5, 5);
	Hpbarback.setFillColor(Color::Black);
	Hpbarback.setPosition(5, 5);
	
	int lv = 1;
	//player
		sf::IntRect pRect(0, 0, 64, 64);
		Player myPlayer("img/PlayerS.png", pRect);
		myPlayer.setOrigin();
		myPlayer.setpos(window.getSize().x / 2, window.getSize().y-64);
		Text Playerhp("HP " + std::to_string(myPlayer.hp) + "/" + std::to_string(myPlayer.hpmax),font,20);
		Playerhp.setPosition(12,8);
		Hpbar.setSize(Vector2f(myPlayer.hpmax*20, 30.f));
		Hpbarback.setSize(Vector2f(myPlayer.hpmax*20, 30.f));
		Hpbarback.setOutlineColor(Color::Blue);
		Hpbarback.setOutlineThickness(5.f);

	//Blackground
		sf::IntRect bgRect(0,0, 600, 27000);
		BG blackground("img/long.png");

	//Enemy
		sf::IntRect enemyRect(0, 0, 64, 64);
		Texture eTex;
		eTex.loadFromFile("img/Enemy1.png");
		/*Enemy myenemy("img/Enemy1.png",enemyRect);*/
		std::vector<Enemy>Enemys;


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
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && myPlayer.hp==0)
			{

				goto restart;
			}
		}
		//update
		if (myPlayer.hp > 0)
		{
			myPlayer.pAnimetion(pRect);
			myPlayer.moveplayer(5);
			mybullet.fire(400, playerpos);
			mybullet.Bmove(20);
			blackground.bgAnimation();
			/*myenemy.spawn(1000);
			myenemy.move();
			myenemy.enemyCollision(mybullet.bulletvec,myPlayer.pSprite);*/
			myPlayer.checkpos();
			/*myenemy.size();*/

			//Enemy spwan
			if (timer.getElapsedTime().asSeconds() >= lv)
			{
				Vector2f pos(rand() % 569, -64);
				Vector2f Tpos(pos.x > 32 ? pos.x : 32, pos.y);
				Enemys.push_back(Enemy(eTex, enemyRect, Tpos));
				timer.restart();
			}

			//Enemy move
			for (int i = 0; i < Enemys.size(); i++)
			{
				Enemys[i].eSprite.move(0, 3);
				Enemys[i].Hpbar.setPosition(Enemys[i].eSprite.getPosition().x, Enemys[i].eSprite.getPosition().y + 40);
				Enemys[i].innerHp.setPosition(Enemys[i].eSprite.getPosition().x, Enemys[i].eSprite.getPosition().y + 40);
			}
			for (int i = 0; i < Enemys.size(); i++)
			{
				if (Enemys[i].eSprite.getPosition().y >= window.getSize().y + 64)
				{
					Enemys.erase(Enemys.begin() + i); 
				}
			}

			//Bullet collision
			for (int i = 0; i < mybullet.bulletvec.size(); i++)
			{
				for (int k = 0; k < Enemys.size(); k++)
				{
					if (mybullet.bulletvec[i].getGlobalBounds().intersects(Enemys[k].eSprite.getGlobalBounds()))
					{
						Enemys[k].hp--;
						int percent = (Enemys[k].hp * 30) / Enemys[k].hpmax;
						Enemys[k].Hpbar.setSize(Vector2f(percent,5));
						mybullet.bulletvec.erase(mybullet.bulletvec.begin() + i);
						break;
					}
					if (Enemys[k].hp <= 0)
					{
						Enemys.erase(Enemys.begin() + k);
						playerscore += 100;
						break;
					}
				}
			}

			//Player collision
			for (int i = 0; i < Enemys.size(); i++)
			{
				if (Enemys[i].eSprite.getGlobalBounds().intersects(myPlayer.pSprite.getGlobalBounds()))
				{
					Enemys.erase(Enemys.begin() + i);
					/*myPlayer.setpos(window.getSize().x / 2, window.getSize().y - 64);*/
					myPlayer.hp--;
					Hpbar.setSize(Vector2f(myPlayer.hp*20,30.f));
					break;
				}
			}


			Scoretext.setString("SCORE : " + std::to_string(playerscore));
			Playerhp.setString("HP " + std::to_string(myPlayer.hp) + "/" + std::to_string(myPlayer.hpmax));
		}


			//for (int i = 0; i < Enemys.size(); i++)
			//{
			//	Enemys[i].hpText.setPosition(Enemys[i].eSprite.getPosition().x,Enemys[i].eSprite.getPosition().y-12);
			//	Enemys[i].hpText.setString(Enemys[i].hp + "/" + Enemys[i].hpmax);
			//}

		//draw
		window.clear();
		blackground.draw(window);
		for (int i = 0; i < Enemys.size(); i++)
		{
			window.draw(Enemys[i].eSprite);
			window.draw(Enemys[i].innerHp);
			window.draw(Enemys[i].Hpbar);
			/*window.draw(Enemys[i].hpText);*/
		}
		if(myPlayer.hp>0)
		myPlayer.drawPlayer(window);
		/*myenemy.drawEnemy(window);*/
		mybullet.bulletdraw(window);
		window.draw(Scoretext);
		//for (int i = 0; i < Enemys.size(); i++)
		//{
		//	window.draw(Enemys[i].hpText);
		//}
		if (myPlayer.hp <= 0)
		{
			Text GameOver("GAME OVER", font, 30);
			Text Restart("Press Enter to restart",font,30);
			GameOver.setPosition(window.getSize().x /2-100, window.getSize().y / 2-50);
			Restart.setPosition(window.getSize().x / 2 - 250, window.getSize().y / 2 - 10);
			window.draw(GameOver);
			window.draw(Restart);
		}
		window.draw(Hpbarback);
		window.draw(Hpbar);
		window.draw(Playerhp);
		window.display();
	}
}
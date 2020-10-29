#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
class BG
{
public:
	Sprite bg;
	Texture bgTex;
	Clock timer;
	BG(std::string Text)
	{
		bgTex.loadFromFile(Text);
		bg.setTexture(bgTex);

		bg.setPosition(0, -13500);
	}

	void bgAnimation()
	{
		if (timer.getElapsedTime().asMilliseconds() >= 1000)
		{
			bg.move(0, 1);
			if (bg.getPosition().y == 0)
				bg.setPosition(0, -13500);
		}
	}


	void draw(RenderWindow& window)
	{
		window.draw(bg);
	}
};
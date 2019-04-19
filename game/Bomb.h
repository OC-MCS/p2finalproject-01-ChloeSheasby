#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Bomb
{
private:
	Sprite bomb;
public:
	Bomb(Texture &texture)
	{
		bomb.setTexture(texture);
		bomb.setScale(.5, .5);
	}
	void setDifferentTexture(Texture &texture)
	{
		bomb.setTexture(texture);
	}
	void setPositionByEnemy(Vector2f pos)
	{
		bomb.setPosition(pos);
	}
	void setScale(float x, float y)
	{
		bomb.setScale(x, y);
	}
	void moveBomb()
	{
		const float DISTANCE = 5.0f;
		bomb.move(0, DISTANCE);
	}
	void drawBomb(RenderWindow &win)
	{
		win.draw(bomb);
	}
	Sprite returnBombSprite() const
	{
		return bomb;
	}
	bool hitShip(FloatRect shipBounds)
	{
		FloatRect bombBounds = bomb.getGlobalBounds();
		bool hasHit;

		if (bombBounds.intersects(shipBounds))
		{
			hasHit = true;
		}
		else
		{
			hasHit = false;
		}
		return hasHit;
	}
	bool belowScreen()
	{
		bool belowScreen = false;
		Vector2f pos = bomb.getPosition();
		if (pos.y > 600)
		{
			belowScreen = true;
		}
		return belowScreen;
	}
};

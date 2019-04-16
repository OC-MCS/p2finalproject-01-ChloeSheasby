#pragma once
#include <iostream>
#include "Ship.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Missile
{
private:
	Sprite missile;
public:
	Missile(Texture &texture)
	{
		missile.setTexture(texture);
	}
	void setPositionByShip(Vector2f pos)
	{
		missile.setPosition(pos);
	}
	void moveMissile()
	{
		const float DISTANCE = 10.0f;
		missile.move(0, -DISTANCE);
	}
	void drawMissile(RenderWindow &win)
	{
		win.draw(missile);
	}
	Sprite returnMissileSprite() const
	{
		return missile;
	}
	bool isAHIT(FloatRect enemyBounds, int &aliensHit)
	{
		FloatRect missileBounds = missile.getGlobalBounds();
		bool hasNotHitYet = true;

		if (missileBounds.intersects(enemyBounds))
		{
			if (hasNotHitYet)
			{
				aliensHit++;
				hasNotHitYet = false;
			}
		}
		else
		{
			hasNotHitYet = true;
		}
		return hasNotHitYet;
	}
	bool isOffscreen()
	{
		bool isOffscreen = false;
		Vector2f pos = missile.getPosition();
		if (pos.y < 0)
		{
			isOffscreen = true;
		}
		return isOffscreen;
	}
};

#pragma once
#include <iostream>
#include <list>
#include "Missile.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Enemy
{
private:
	Sprite enemy;
	float distance;		// holds how fast the enemy goes
public:
	Enemy(Vector2f pos, Texture &texture)
	{
		enemy.setTexture(texture);
		// makes the enemy smaller so it's harder to hit
		enemy.setScale(.75, .75);

		enemy.setPosition(pos);

		distance = 0.2f;
	}
	void setDifferentTexture(Texture &texture)
	{
		enemy.setTexture(texture);
	}
	void setDifferentPosition(Vector2f pos)
	{
		// really only changes the y value of position
		enemy.setPosition(pos);
	}
	void setMovingDistance(float d)
	{
		distance = d;
	}
	void drawEnemy(RenderWindow &win)
	{
		win.draw(enemy);
	}
	void moveEnemy()
	{
		enemy.move(0, distance);
	}
	Sprite returnEnemySprite()
	{
		return enemy;
	}
	float getXPosition() const
	{
		return enemy.getPosition().x;
	}
	Vector2f returnPosition() const
	{
		return enemy.getPosition();
	}
	bool offScreen()
	{
		bool offScreen = false;
		Vector2f pos = enemy.getPosition();
		if (pos.y > 600)
		{
			offScreen = true;
		}
		return offScreen;
	}
	bool isEnemyHit(list<Missile> &manyMissiles)
	{
		bool enemyIsHit = false;
		list<Missile>::iterator tempMissile;
		for (tempMissile = manyMissiles.begin(); tempMissile != manyMissiles.end() && !enemyIsHit;)
		{
			if (tempMissile->isAHIT(enemy.getGlobalBounds()))
			{
				tempMissile = manyMissiles.erase(tempMissile);
				cout << "A missile hit an enemy." << endl;
				enemyIsHit = true;
			}
			else
			{
				tempMissile++;
			}
		}
		return enemyIsHit;
	}
	bool reachedShip(Vector2f shipPos)
	{
		bool hasHit;

		if (enemy.getPosition().y > shipPos.y)
		{
			hasHit = true;
		}
		else
		{
			hasHit = false;
		}
		return hasHit;
	}
};

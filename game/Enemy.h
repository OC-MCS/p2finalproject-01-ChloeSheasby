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
	Sprite enemy;		// holds the enemy's sprite
	float distance;		// holds how fast the enemy goes
public:
	//===========================================================================
	// this constructor sets the texture, scale, and position of the enemy
	//===========================================================================
	Enemy(Vector2f pos, Texture &texture)
	{
		enemy.setTexture(texture);
		// makes the enemy smaller so it's harder to hit
		enemy.setScale(.75, .75);

		enemy.setPosition(pos);

		distance = 0.2f;
	}

	//===========================================================================
	// this sets a different texture that is passed as a parameter
	//===========================================================================
	void setDifferentTexture(Texture &texture)
	{
		enemy.setTexture(texture);
	}

	//=====================================================
	// this sets the y coordinate to a different position
	//=====================================================
	void setDifferentPosition(Vector2f pos)
	{
		enemy.setPosition(pos);
	}

	//===========================================================================
	// this changes the speed that the enemy moves down the screen
	//===========================================================================
	void setMovingDistance(float d)
	{
		distance = d;
	}

	//=======================
	// this draws the enemy
	//=======================
	void drawEnemy(RenderWindow &win)
	{
		win.draw(enemy);
	}

	//=======================
	// this moves the enemy
	//=======================
	void moveEnemy()
	{
		enemy.move(0, distance);
	}

	//================================
	// this returns the enemy sprite
	//================================
	Sprite returnEnemySprite()
	{
		return enemy;
	}

	//=========================================================
	// this returns the x coordinate of the enemy's position
	//=========================================================
	float getXPosition() const
	{
		return enemy.getPosition().x;
	}

	//===============================================
	// this returns the whole position of the enemy
	//===============================================
	Vector2f returnPosition() const
	{
		return enemy.getPosition();
	}

	//===========================================================================
	// this checks if an enemy is hit by a missile by cycling through each 
	// missile and cycling through each enemy (by calling the isAHIT function)
	// it then returns a bool depending on if the enemy was hit or not
	//===========================================================================
	bool isEnemyHit(list<Missile> &manyMissiles)
	{
		bool enemyIsHit = false;
		list<Missile>::iterator tempMissile;
		for (tempMissile = manyMissiles.begin(); tempMissile != manyMissiles.end() && !enemyIsHit;)
		{
			if (tempMissile->isAHIT(enemy.getGlobalBounds()))		// calls a function in Missile.h
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

	//===========================================================================
	// this checks if the enemy's position has reached the ship's position so 
	// that the level can be reset
	// it returns a boolean accordingly
	//===========================================================================
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

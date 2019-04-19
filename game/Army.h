#pragma once
#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>
#include "Enemy.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Army
{
private:
	list<Enemy> army;	//creates a linked list of enemies
	Texture enemyTexture;
	Texture badderTexture;
	Texture ocTexture;
public:
	Army(Vector2f pos)
	{
		if (!enemyTexture.loadFromFile("enemy.bmp"))
		{
			cout << "Unable to load enemy texture!" << endl;
			exit(EXIT_FAILURE);
		}
		if (!badderTexture.loadFromFile("BadderEnemy.bmp"))
		{
			cout << "Unable to load badder enemy texture!" << endl;
			exit(EXIT_FAILURE);
		}
		if (!ocTexture.loadFromFile("OC.bmp"))
		{
			cout << "Unable to load OC texture!" << endl;
			exit(EXIT_FAILURE);
		}

		Vector2f position = pos;
		for (int i = 0; i < 12; i++)
		{
			Enemy temp(position, enemyTexture);
			army.push_back(temp);
			position.x += 50;
		}
	}
	void resetArmy(Vector2f pos)
	{
		army.clear();
		Vector2f position = pos;
		for (int i = 0; i < 12; i++)
		{
			Enemy temp(position, enemyTexture);
			army.push_back(temp);
			position.x += 50;
		}
	}
	void resetPosition(float posy)
	{
		float positionY = posy;
		Vector2f tempPos;
		tempPos.y = positionY;
		list<Enemy>::iterator tempEnemy;
		for (tempEnemy = army.begin(); tempEnemy != army.end(); tempEnemy++)
		{
			tempPos.x = tempEnemy->getXPosition();
			tempEnemy->setDifferentPosition(tempPos);
		}
	}
	void resetTexture(int level)
	{
		list<Enemy>::iterator tempEnemy;
		for (tempEnemy = army.begin(); tempEnemy != army.end(); tempEnemy++)
		{
			if (level == 1)
			{
				tempEnemy->setDifferentTexture(badderTexture);
			}
			else if (level == 2)
			{
				tempEnemy->setDifferentTexture(ocTexture);
			}

		}
	}
	void setSpeed(float speed)
	{
		list<Enemy>::iterator tempEnemy;
		for (tempEnemy = army.begin(); tempEnemy != army.end(); tempEnemy++)
		{
			tempEnemy->setMovingDistance(speed);
		}
	}
	bool moveArmy(int &livesLeft)
	{
		list<Enemy>::iterator temp;
		bool enemyBelowScreen = false;
		for (temp = army.begin(); temp != army.end() && !enemyBelowScreen; temp++)
		{
			temp->moveEnemy();
			if (temp->offScreen())
			{
				enemyBelowScreen = true;
				livesLeft--;
			}
		}
		return enemyBelowScreen;
	}
	void drawArmy(RenderWindow &win)
	{
		list<Enemy>::iterator temp;
		for (temp = army.begin(); temp != army.end(); temp++)	
		{
			win.draw(temp->returnEnemySprite());		// how to load the individual sprites	
		}
	}
	list<Enemy> &returnArmyList() 
	{
		return army;
	}
	Vector2f returnRandomEnemyPosition() 
	{
		list<Enemy>::iterator temp;
		temp = army.begin();
		int random = rand() % army.size();
		advance(temp, random);
		return temp->returnEnemySprite().getPosition();
		// you have to get a sprite returned because enemy class isn;t just a sprite
	}
	bool hasArmyReachedEnemy(Sprite ship, int &livesLeft)
	{
		bool hasArmyReachedEnemy = false;
		FloatRect shipBounds = ship.getGlobalBounds();
		list<Enemy>::iterator tempEnemy;

		for (tempEnemy = army.begin(); tempEnemy != army.end() && !hasArmyReachedEnemy; tempEnemy++)
		{
			if (tempEnemy->reachedShip(ship.getPosition()))
			{
				hasArmyReachedEnemy = true;
				livesLeft--;
			}
		}
		return hasArmyReachedEnemy;
	}
	int returnEnemiesHit() const
	{
		return (12 - army.size());
	}
	void setNewLevel(int level)
	{
		army.clear();
		resetArmy(Vector2f(100, 40));
		setSpeed(0.75f);
		resetTexture(level);
	}
	void clearArmyList()
	{
		army.clear();
	}
};
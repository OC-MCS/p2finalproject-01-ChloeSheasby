#pragma once
#include <iostream>
#include <list>
#include "Missile.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class ManyMissiles		
{
private:
	list<Missile> manyMissiles;	// creates a list of missile
	Texture missileTexture;
	Texture moneyTexture;
public:
	ManyMissiles()
	{
		if (!missileTexture.loadFromFile("missile.png"))
		{
			cout << "Unable to load missile texture!" << endl;
			exit(EXIT_FAILURE);
		}
		if (!moneyTexture.loadFromFile("money.bmp"))
		{
			cout << "Unable to load money texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	void addMissileToGroup(Vector2f pos, int level)	// this simply adds a missile to the group of missiles
	{
		Missile temp(missileTexture);
		if (level == 2)
		{
			temp.setDifferentScale(3, 3);
			temp.setDifferentTexture(moneyTexture);
		}
		temp.setPositionByShip(pos);
		manyMissiles.push_back(temp);
	}
	void deleteMissileAndEnemy(list<Enemy> &army)	// delete once the missile is a hit
	{
		bool alienIsHit = false;
		list<Enemy>::iterator armyTemp;
		
		for (armyTemp = army.begin(); armyTemp != army.end() && !alienIsHit;)
		{
			if (armyTemp->isEnemyHit(manyMissiles))
			{
				armyTemp = army.erase(armyTemp);
				alienIsHit = true;
			}
			else
			{
				armyTemp++;
			}
		}
	}
	void moveMissiles()
	{
		list<Missile>::iterator temp;
		bool missileOffScreen = false;
		for (temp = manyMissiles.begin(); temp != manyMissiles.end() && !missileOffScreen;)
		{
			temp->moveMissile();
			if (temp->isOffscreen())
			{
				temp = manyMissiles.erase(temp);	// erases if missile is offscreen
				cout << "Missile went off screen." << endl;
				missileOffScreen = true;
			}
			else
			{
				temp++;
			}
		}
	}
	void drawManyMissiles(RenderWindow &win)
	{
		list<Missile>::iterator temp;
		for (temp = manyMissiles.begin(); temp != manyMissiles.end(); temp++)
		{
			win.draw(temp->returnMissileSprite());
		}
	}
	bool areAllAliensDead(int count)
	{
		bool areAllAliensDead = false;
		if (count == 12)
		{
			areAllAliensDead = true;
		}
		else
		{
			areAllAliensDead = false;
		}
		return areAllAliensDead;
	}
	void clearMissileList()
	{
		manyMissiles.clear();
	}
};

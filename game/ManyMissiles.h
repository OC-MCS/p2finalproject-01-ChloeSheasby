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
	list<Missile> many;	// creates a list of missile
	Texture missileTexture;
public:
	ManyMissiles()
	{
		if (!missileTexture.loadFromFile("missile.png"))
		{
			cout << "Unable to load missile texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	void addMissileToGroup(Vector2f pos)	// this simply adds a missile to the group of missiles
	{
		Missile temp(missileTexture);
		temp.setPositionByShip(pos);
		many.push_back(temp);
	}
	void deleteMissile(list<Enemy> &army, int &aliensHit)	// delete once the missile is a hit
	{
		bool alienIsHit = false;
		list<Missile>::iterator temp;
		temp = many.begin();
		list<Enemy>::iterator armyTemp;
		while (temp != many.end())
		{
			for (armyTemp = army.begin(); armyTemp != army.end() && !alienIsHit; armyTemp++)
			{
				if (temp->isAHIT(armyTemp->returnGlobalBounds(), aliensHit))
				{
					temp = many.erase(temp);
					cout << "A missile hit an enemy." << endl;
					//armyTemp = army.erase(armyTemp);	// can I do this to handle deleting the aliens too?
					alienIsHit = true;
				}
				else
				{
					// this is where it is breaking
					temp++;
				}
			}
		}
	}
	void moveMissiles()
	{
		list<Missile>::iterator temp;
		temp = many.begin();
		while (temp != many.end())
		{
			temp->moveMissile();
			if (temp->isOffscreen())
			{
				temp = many.erase(temp);	// erases if missile is offscreen
				cout << "Missile went off screen." << endl;
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
		for (temp = many.begin(); temp != many.end(); temp++)
		{
			win.draw(temp->returnMissileSprite());
		}
	}
	bool areAllAliensDead(int count)
	{
		bool areAllAliensDead = false;
		if (count == 10)
		{
			areAllAliensDead = true;
		}
		else
		{
			areAllAliensDead = false;
		}
		return areAllAliensDead;
	}
};

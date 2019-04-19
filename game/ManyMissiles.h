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
	Texture missileTexture;		// holds the texture for the missile
	Texture moneyTexture;		// holds the texture for the special third level
public:
	//=================================================
	// this constructor simply loads all the textures 
	//=================================================
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

	//===========================================================================
	// this adds a missile to the group of missiles
	// one of its parameters is the level, which helps it change certain things
	// if it is the third level
	//===========================================================================
	void addMissileToGroup(Vector2f pos, int level)	
	{
		Missile temp(missileTexture);
		if (level == 2)		// if it is level three
		{
			temp.setDifferentScale(3, 3);
			temp.setDifferentTexture(moneyTexture);
		}
		temp.setPositionByShip(pos);
		manyMissiles.push_back(temp);
	}

	//===========================================================================
	// this cycles through the list of enemies and deletes the enemy if it is 
	// hit by a missile
	// it also calls a function in Enemy.h that cycles through each missile and 
	// deletes missiles if any of them hit one of the enemies
	// it then returns a boolean if the alien is hit or not
	//===========================================================================
	void deleteMissileAndEnemy(list<Enemy> &army)	
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

	//===========================================================================
	// this moves the missiles and also tests if the missiles go offscreen
	// if they do go offscreen, they are deleted
	//===========================================================================
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

	//=============================================
	// this draws all of the missiles in the list
	//=============================================
	void drawManyMissiles(RenderWindow &win)
	{
		list<Missile>::iterator temp;
		for (temp = manyMissiles.begin(); temp != manyMissiles.end(); temp++)
		{
			win.draw(temp->returnMissileSprite());
		}
	}

	//============================================================================
	// this checks if all of the aliens are dead and returns a boolean accordingly
	//===========================================================================
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

	//=========================================
	// this simply clears the list of missiles
	//=========================================
	void clearMissileList()
	{
		manyMissiles.clear();
	}
};

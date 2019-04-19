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
	Texture enemyTexture;	// holds the enemy texture
	Texture badderTexture;	// holds the 2nd level enemy texture
	Texture ocTexture;		// holds the 3rd level enemy texture
public:
	//===========================================================================
	// this constructor loads all of the texture, and initializes the list of
	// enemies with singular enemies (their positions and textures)
	//===========================================================================
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
			position.x += 50;		// this offsets each enemy so that they aren't printed on top of each other
		}
	}

	//===========================================================================
	// this function clears the list and then resets the enemies in the list
	//===========================================================================
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

	//===========================================================================
	// this resets the y coordinate of the position of each enemy in the enemy 
	// list, which is used when the ship loses a life but is not dead yet
	// the x coordinate must remain the same because each alien must stay in the
	// place it was before even if the aliens next to it have been destroyed
	//===========================================================================
	void resetPosition(float posy)
	{
		float positionY = posy;
		Vector2f tempPos;
		tempPos.y = positionY;
		list<Enemy>::iterator tempEnemy;
		for (tempEnemy = army.begin(); tempEnemy != army.end(); tempEnemy++)
		{
			tempPos.x = tempEnemy->getXPosition();		// gets the x coordinate of the enemy so it will remain the same
			tempEnemy->setDifferentPosition(tempPos);	// calls a function in Enemy.h
		}
	}

	//===========================================================================
	// this resets the texture of each enemy in the list according to the level
	//===========================================================================
	void resetTexture(int level)
	{
		list<Enemy>::iterator tempEnemy;
		for (tempEnemy = army.begin(); tempEnemy != army.end(); tempEnemy++)
		{
			if (level == 1)		// sees if the level is now level two
			{
				tempEnemy->setDifferentTexture(badderTexture);
			}
			else if (level == 2)	// sees if the level is now level three
			{
				tempEnemy->setDifferentTexture(ocTexture);
			}
		}
	}

	//===========================================================================
	// this changes the speed that the aliens move down the screen
	//===========================================================================
	void setSpeed(float speed)
	{
		list<Enemy>::iterator tempEnemy;
		for (tempEnemy = army.begin(); tempEnemy != army.end(); tempEnemy++)
		{
			tempEnemy->setMovingDistance(speed);
		}
	}

	//======================================
	// this moves the army down the screen
	//======================================
	void moveArmy()
	{
		list<Enemy>::iterator temp;
		for (temp = army.begin(); temp != army.end(); temp++)
		{
			temp->moveEnemy();
		}
	}

	//==================================================================================
	// this draws the army by getting the individual sprites from each enemy in the list
	//==================================================================================
	void drawArmy(RenderWindow &win)
	{
		list<Enemy>::iterator temp;
		for (temp = army.begin(); temp != army.end(); temp++)	
		{
			win.draw(temp->returnEnemySprite());		// how to load the individual sprites	
		}
	}

	//===============================================
	// this returns the list of enemies by reference
	//===============================================
	list<Enemy> &returnArmyList() 
	{
		return army;
	}

	//===========================================================================
	// this generates a random number, finds that random enemy by using it as an
	// index, and returns that enemy's position
	//===========================================================================
	Vector2f returnRandomEnemyPosition() 
	{
		list<Enemy>::iterator temp;
		temp = army.begin();		// puts the iterator at the beginning of the list
		int random = rand() % army.size();	// generates the random number within the range of enemies
		advance(temp, random);		// finds the enemy with that index number
		return temp->returnEnemySprite().getPosition();
	}

	//===============================================================================
	// this checks to see if the army has reached the ship by checking their 
	// positions
	// it cycles through each enemy to test if any of them have arrived at that level
	// it then returns a boolean depending on if the army has reached the ship or not
	// it also takes the lives left as a parameter and decrements it if the army has
	// reached the ship (making the ship lose a life)
	//===============================================================================
	bool hasArmyReachedShip(Sprite ship, int &livesLeft)
	{
		bool hasArmyReachedShip = false;
		FloatRect shipBounds = ship.getGlobalBounds();
		list<Enemy>::iterator tempEnemy;

		for (tempEnemy = army.begin(); tempEnemy != army.end() && !hasArmyReachedShip; tempEnemy++)
		{
			if (tempEnemy->reachedShip(ship.getPosition()))
			{
				hasArmyReachedShip = true;
				livesLeft--;	// decrements the lives the ship has left
			}
		}
		return hasArmyReachedShip;
	}

	//===========================================================================
	// returns the number of aliens hit by checking the size and subtracting it
	// from how many aliens were initially in the list
	//===========================================================================
	int returnEnemiesHit() const
	{
		return (12 - army.size());
	}

	//===========================================================================
	// this sets up the new level by calling a bunch of functions within in class
	// this makes it cleaner/more organized
	// it clears the list of aliens, and resets the texture, speed, and 
	// individual aliens
	//===========================================================================
	void setNewLevel(int level)
	{
		army.clear();
		resetArmy(Vector2f(100, 40));
		setSpeed(0.75f);
		resetTexture(level);
	}
};
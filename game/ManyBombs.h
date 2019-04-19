#pragma once
#include <iostream>
#include <list>
#include "Bomb.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class ManyBombs
{
private:	
	list<Bomb> manyBombs;	// creates a list of bombs
	Texture bombTexture;	// holds the texture of the bomb
	Texture loanTexture;	// holds the special texture for the third level bomb
public:
	//======================================
	// this constructor loads the textures
	//======================================
	ManyBombs()
	{
		if (!bombTexture.loadFromFile("bomb.bmp"))
		{
			cout << "Unable to load bomb texture!" << endl;
			exit(EXIT_FAILURE);
		}
		if (!loanTexture.loadFromFile("loans.bmp"))
		{
			cout << "Unable to load loan texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}

	//===========================================================================
	// this adds a bomb to the list and sets the position to a random alien
	// it also sets the scale/texture based on the level
	//===========================================================================
	void randomAlienDrop(Vector2f pos, int level)	
	{
		Bomb temp(bombTexture);
		if (level == 1)		// if it is level two
		{
			temp.setScale(1, 1);
		}
		else if (level == 2)	// if is it level three
		{
			temp.setScale(1.2, 1.2);
			temp.setDifferentTexture(loanTexture);
		}
		temp.setPositionByEnemy(Vector2f(pos.x + 5, pos.y - 5));
		manyBombs.push_back(temp);
		cout << "a bomb is being added" << endl;
	}

	//===========================================================================
	// this cycles through the list of bombs and deletes them if any of them hit 
	// the ship
	// it also decrements the lives left if the ship is hit
	//===========================================================================
	bool deleteBomb(Sprite ship, int &livesLeft)
	{
		list<Bomb>::iterator tempBomb;
		FloatRect shipBounds = ship.getGlobalBounds();
		bool shipIsHit = false;

		for (tempBomb = manyBombs.begin(); tempBomb != manyBombs.end() && !shipIsHit;)
		{
			if (tempBomb->hitShip(shipBounds))	
			{
				tempBomb = manyBombs.erase(tempBomb);
				shipIsHit = true;
				livesLeft--;	// lives left is decremented
			}
			else
			{
				tempBomb++;
			}
		}
		return shipIsHit;
	}

	//===========================================================================
	// this moves the bombs and also tests if the bombs go offscreen
	// if they do go offscreen, they are deleted
	//===========================================================================
	void moveBombs()
	{
		list<Bomb>::iterator temp;
		bool bombBelowScreen = false;
		for (temp = manyBombs.begin(); temp != manyBombs.end() && !bombBelowScreen;)
		{
			temp->moveBomb();
			if (temp->belowScreen())
			{
				temp = manyBombs.erase(temp);
				bombBelowScreen = true;
			}
			else
			{
				temp++;
			}
		}
	}

	//==========================================
	// this draws all of the bombs in the list
	//==========================================
	void drawBombs(RenderWindow &win)
	{
		list<Bomb>::iterator temp;
		for (temp = manyBombs.begin(); temp != manyBombs.end(); temp++)
		{
			win.draw(temp->returnBombSprite());
		}
	}

	//===========================================================================
	// this checks if all of the ship's lives have been used up and returns 
	// a boolean accordingly
	//===========================================================================
	bool isShipDead(int count)
	{
		bool isShipDead = false;
		if (count == 0)
		{
			isShipDead = true;
		}
		else
		{
			isShipDead = false;
		}
		return isShipDead;
	}

	//======================================
	// this simply clears the list of bombs
	//======================================
	void clearBombList()
	{
		manyBombs.clear();
	}
};

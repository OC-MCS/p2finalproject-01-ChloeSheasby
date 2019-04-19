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
	list<Bomb> manyBombs;
	Texture bombTexture;
	Texture loanTexture;
public:
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
	void randomAlienDrop(Vector2f pos, int level)		// this adds a bomb to the list
	{
		Bomb temp(bombTexture);
		if (level == 1)
		{
			temp.setScale(1, 1);
		}
		else if (level == 2)
		{
			temp.setScale(1.2, 1.2);
			temp.setDifferentTexture(loanTexture);
		}
		temp.setPositionByEnemy(Vector2f(pos.x + 5, pos.y - 5));
		manyBombs.push_back(temp);
		cout << "a bomb is being added" << endl;
	}
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
				livesLeft--;
			}
			else
			{
				tempBomb++;
			}
		}
		return shipIsHit;
	}
	void moveBombs()
	{
		list<Bomb>::iterator temp;
		bool bombBelowScreen = false;
		for (temp = manyBombs.begin(); temp != manyBombs.end() && !bombBelowScreen;)
			// I think this kicks out of the loop as soon as a bomb leaves the screen
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
	void drawBombs(RenderWindow &win)
	{
		list<Bomb>::iterator temp;
		for (temp = manyBombs.begin(); temp != manyBombs.end(); temp++)
		{
			win.draw(temp->returnBombSprite());
		}
	}
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
	void clearBombList()
	{
		manyBombs.clear();
	}
};

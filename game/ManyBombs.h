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
	list<Bomb> many;
	Texture bombTexture;
public:
	ManyBombs()
	{
		if (!bombTexture.loadFromFile("bomb.bmp"))
		{
			cout << "Unable to load bomb texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	void randomAlienDrop(Sprite randomEnemy)		// this also adds a bomb to the list
	{
		Vector2f pos = randomEnemy.getPosition();
		Bomb temp(bombTexture);
		temp.setPositionByEnemy(Vector2f(pos.x + 5, pos.y - 5));
		many.push_back(temp);
	}
	void deleteBomb(Sprite ship, int &livesLost)	// should this instead be that if a bomb hits the ship, 
													// the level resets, so the bomb gets deleted anyway?
	{
		list<Bomb>::iterator temp;
		temp = many.begin();
		FloatRect shipBounds = ship.getGlobalBounds();
		while (temp != many.end())
		{
			if (temp->hitShip(shipBounds, livesLost))
			{
				temp = many.erase(temp);
			}
			else
			{
				temp++;
			}
		}
	}
	void moveBombs()
	{
		list<Bomb>::iterator temp;
		temp = many.begin();
		while (temp != many.end())
		{
			temp->moveBomb();
			if (temp->belowScreen())
			{
				temp = many.erase(temp);
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
		for (temp = many.begin(); temp != many.end(); temp++)
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
};

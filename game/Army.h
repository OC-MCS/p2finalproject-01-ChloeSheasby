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
public:
	Army(Vector2f pos)
	{
		if (!enemyTexture.loadFromFile("enemy.bmp"))
		{
			cout << "Unable to load enemy texture!" << endl;
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
	void moveArmy()
	{
		list<Enemy>::iterator temp;
		for (temp = army.begin(); temp != army.end(); temp++)
		{
			temp->moveEnemy();
		}
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
	Sprite returnRandomEnemy() 
	{
		list<Enemy>::iterator temp;
		temp = army.begin();

		unsigned seed = time(0);
		srand(seed);
		int random = (rand() % army.size()) + 1;

		advance(temp, random);

		return temp->returnEnemySprite();
	}
};
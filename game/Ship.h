#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Ship
{
private:
	Sprite ship;	
	Texture shipTexture;
public:
	Ship(Vector2f pos)
	{
		if (!shipTexture.loadFromFile("ship.png"))
		{
			cout << "Unable to load ship texture!" << endl;
			exit(EXIT_FAILURE);
		}
		ship.setTexture(shipTexture);

		ship.setPosition(pos);
	}
	void moveShip()
	{
		const float DISTANCE = 5.0;

		if (Keyboard::isKeyPressed(Keyboard::Left) && (ship.getPosition().x > 0))
		{
			// left arrow is pressed: move our ship left 5 pixels
			// 2nd parm is y direction. We don't want to move up/down, so it's zero.
			ship.move(-DISTANCE, 0);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) && (ship.getPosition().x < (800 - shipTexture.getSize().x)))
		{
			// right arrow is pressed: move our ship right 5 pixels
			ship.move(DISTANCE, 0);
		}
	}
	void drawShip(RenderWindow &win)
	{
		win.draw(ship);
	}
	Vector2f returnPosition() const
	{
		return ship.getPosition();
	}
	Sprite returnShipSprite() const
	{
		return ship;
	}
};

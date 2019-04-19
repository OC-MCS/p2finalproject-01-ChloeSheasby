#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Ship
{
private:
	Sprite ship;		// holds the ship's sprite
	Texture shipTexture;	// holds the ship's texture
public:
	//===========================================================================
	// this constructor takes a position as a parameter and initializes the ship
	//===========================================================================
	Ship(Vector2f pos)
	{
		if (!shipTexture.loadFromFile("ship.png"))
		{
			cout << "Unable to load ship texture!" << endl;
			exit(EXIT_FAILURE);
		}
		ship.setTexture(shipTexture);	// sets texture

		ship.setPosition(pos);			// sets position
	}

	//============================================
	// this handles moving the ship left to right
	//============================================
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

	//=====================================================
	// this is just a wrapper function that draws the ship
	//=====================================================
	void drawShip(RenderWindow &win)
	{
		win.draw(ship);
	}

	//================================
	// this resets the ships position
	//================================
	void resetPosition(Vector2f pos)
	{
		ship.setPosition(pos);
	}

	//============================
	// returns the ship's position
	//============================
	Vector2f returnPosition() const
	{
		return ship.getPosition();
	}

	//===========================
	// returns the ship's sprite
	//===========================
	Sprite returnShipSprite() const
	{
		return ship;
	}
};

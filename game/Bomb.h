#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Bomb
{
private:
	Sprite bomb;	// this holds the sprite of a bomb
public:
	//=======================================================
	// this constructor sets the texture and scale of a bomb
	//=======================================================
	Bomb(Texture &texture)
	{
		bomb.setTexture(texture);
		bomb.setScale(.5, .5);
	}

	//================================================================
	// this sets the special texture of the bomb for the third level
	//================================================================
	void setDifferentTexture(Texture &texture)
	{
		bomb.setTexture(texture);
	}

	//=====================================================================
	// this sets the position of the bomb based on which enemy it is being
	// dropped by
	//=====================================================================
	void setPositionByEnemy(Vector2f pos)
	{
		bomb.setPosition(pos);
	}

	//=================================
	// this sets the scale of the bomb
	//=================================
	void setScale(float x, float y)
	{
		bomb.setScale(x, y);
	}

	//=====================
	// this moves the bomb
	//=====================
	void moveBomb()
	{
		const float DISTANCE = 5.0f;
		bomb.move(0, DISTANCE);
	}

	//=====================
	// this draws the bomb
	//=====================
	void drawBomb(RenderWindow &win)
	{
		win.draw(bomb);
	}

	//================================
	// this returns the bomb's sprite
	//================================
	Sprite returnBombSprite() const
	{
		return bomb;
	}

	//===========================================================================
	// this checks if the bomb hits the ship and returns a boolean accordingly
	//===========================================================================
	bool hitShip(FloatRect shipBounds)
	{
		FloatRect bombBounds = bomb.getGlobalBounds();
		bool hasHit;

		if (bombBounds.intersects(shipBounds))
		{
			hasHit = true;
		}
		else
		{
			hasHit = false;
		}
		return hasHit;
	}

	//===========================================================================
	// this checks if the bomb is offscreen and returns a boolean accordingly
	//===========================================================================
	bool belowScreen()
	{
		bool belowScreen = false;
		Vector2f pos = bomb.getPosition();
		if (pos.y > 600)
		{
			belowScreen = true;
		}
		return belowScreen;
	}
};

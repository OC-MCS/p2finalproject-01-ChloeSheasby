#pragma once
#include <iostream>
#include "Ship.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Missile
{
private:
	Sprite missile;	// holds the sprite of a missile
public:
	//==========================================================
	// this constructor simply sets the texture of the missile
	//==========================================================
	Missile(Texture &texture)
	{
		missile.setTexture(texture);
	}

	//===========================================================================
	// this helps set a different texture (for the third level for example)
	//===========================================================================
	void setDifferentTexture(Texture &texture)
	{
		missile.setTexture(texture);
	}

	//=============================================
	// this sets a different scale for the missile
	//=============================================
	void setDifferentScale(float x, float y)
	{
		missile.setScale(x, y);
	}

	//=============================================================================
	// this sets the position of the missile to shoot from the position of the ship
	//=============================================================================
	void setPositionByShip(Vector2f pos)
	{
		missile.setPosition(pos);
	}

	//===============================
	// this simply moves the missile
	//===============================
	void moveMissile()
	{
		const float DISTANCE = 10.0f;
		missile.move(0, -DISTANCE);
	}

	//========================
	// this draws the missile
	//========================
	void drawMissile(RenderWindow &win)
	{
		win.draw(missile);
	}

	//====================================
	// this returns the missile's sprite
	//====================================
	Sprite returnMissileSprite() const
	{
		return missile;
	}

	//============================================================
	// this checks if a missile has sit an enemy
	// it returns a bool depending on if an enemy was hit or not
	//============================================================
	bool isAHIT(FloatRect enemyBounds)
	{
		FloatRect missileBounds = missile.getGlobalBounds();
		bool hasHit;

		if (missileBounds.intersects(enemyBounds))
		{
			hasHit = true;
		}
		else
			hasHit = false;

		return hasHit;
	}

	//===========================================================================
	// this checks if the missile is offscreen and returns a boolean accordingly
	//===========================================================================
	bool isOffscreen()
	{
		bool isOffscreen = false;
		Vector2f pos = missile.getPosition();
		if (pos.y < 0)
		{
			isOffscreen = true;
		}
		return isOffscreen;
	}
};

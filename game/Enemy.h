#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Enemy
{
private:
	Sprite enemy;
public:
	Enemy(Vector2f pos, Texture &texture)
	{
		enemy.setTexture(texture);
		// makes the enemy smaller so it's harder to hit
		enemy.setScale(.75, .75);

		enemy.setPosition(pos);
	}
	void drawEnemy(RenderWindow &win)
	{
		win.draw(enemy);
	}
	void moveEnemy()
	{
		const float DISTANCE = 0.2f;
		enemy.move(0, DISTANCE);
	}
	Sprite returnEnemySprite()
	{
		return enemy;
	}
	Vector2f returnPosition() const
	{
		return enemy.getPosition();
	}
	FloatRect returnGlobalBounds() const
	{
		return enemy.getGlobalBounds();
	}
};

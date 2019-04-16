//=========================================================
// This is just the starting point for your final project.
// You are expected to modify and add classes/files as needed.
// The code below is the original code for our first graphics
// project (moving the little green ship). 
//========================================================
#include <iostream>
#include "Ship.h"
#include "Enemy.h"
#include "Army.h"
#include "Missile.h"
#include "Bomb.h"
#include "ManyBombs.h"
#include "UI.h"
#include "ManyMissiles.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf; 

//===============================
// Chloe Sheasby
// Programming Assignment #7
// Description: GAME
// Due Date: Friday, April 19th
//===============================

// note: a Sprite represents an image on screen. A sprite knows and remembers its own position
// ship.move(offsetX, offsetY) adds offsetX, offsetY to 
// the current position of the ship. 
// x is horizontal, y is vertical. 
// 0,0 is in the UPPER LEFT of the screen, y increases DOWN the screen

int main()
{
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Invaders");
	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);

	float shipX = window.getSize().x / 2.0f;
	float shipY = 500;

	// this is here so that I can test a single enemy if wanted
	Texture enemyTexture;
	if (!enemyTexture.loadFromFile("enemy.bmp"))
	{
		cout << "Unable to load enemy texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture missileTexture;
	if (!missileTexture.loadFromFile("missile.png"))
	{
		cout << "Unable to load missile texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture bombTexture;
	if (!bombTexture.loadFromFile("bomb.bmp"))
	{
		cout << "Unable to load bomb texture!" << endl;
		exit(EXIT_FAILURE);
	}


	Ship ship(Vector2f(shipX, shipY));
	//Enemy enemy(Vector2f(100, 40), enemyTexture);
	Army army(Vector2f(100, 40));
	UI title;
	//Missile missile(missileTexture);
	ManyMissiles manyMissiles;

	//Bomb bomb(bombTexture);
	//Vector2f pos = enemy.returnPosition();
	//bomb.setPositionByEnemy(Vector2f(pos.x + 5, pos.y - 5));

	ManyBombs manyBombs;


	bool start = false;
	int aliensHit = 0;		// how many aliens hit
	int livesLeft = 3;		// sets the initial amount of lives for the player
	bool aliensWon = false;

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		// For now, we just need this so we can click on the window and close it
		Event event;

		// draw background first, so everything that's drawn later 
		// will appear on top of background
		title.drawBackground(window);

		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Space)
				{
					Vector2f pos = ship.returnPosition();
					//missile.setPositionByShip(Vector2f(pos.x + 5, pos.y - 5));
					manyMissiles.addMissileToGroup(Vector2f(pos.x + 5, pos.y - 5));
					cout << "Adding a missile to the missile group." << endl;
				}
			}
		}

	//===========================================================
	// Everything from here to the end of the loop is where you put your
	// code to produce ONE frame of the animation. The next iteration of the loop will
	// render the next frame, and so on. All this happens ~ 60 times/second.
	//===========================================================

		if (!start)
		{
			title.drawTitlePage(window);
			if (event.type == Event::MouseButtonReleased)
			{
				// maybe they just clicked on one of the settings "buttons"
				// check for this and handle it.
				Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				start = title.handleMouseClicked(mousePos);
				// should change start to true if the start button is clicked
				if (!start)
				{
					exit(-1);
				}
			}
		}
		else
		{
			title.drawLabels(window, livesLeft, aliensHit);
			ship.moveShip();
	
			// draw the ship on top of background 
			// (the ship from previous frame was erased when we drew background)
			ship.drawShip(window);
	
			//enemy.drawEnemy(window);
	
			//bomb.drawBomb(window);
			//bomb.moveBomb();
	
			army.moveArmy();
			army.drawArmy(window);
	
			// this should only happen every 1 to 5 seconds 
			// not sure how to do that yet
			//manyBombs.randomAlienDrop(army.returnRandomEnemy());
			//manyBombs.moveBombs();
			//manyBombs.drawBombs(window);
	
			//missile.drawMissile(window);
			//missile.moveMissile();
	
			manyMissiles.moveMissiles();
			manyMissiles.drawManyMissiles(window);
			manyMissiles.deleteMissile(army.returnArmyList(), aliensHit);

			// this function makes the program crash as soon as the spacebar is pressed
	
			//manyBombs.deleteBomb(ship.returnShipSprite(), livesLost);
		}

		if (manyBombs.isShipDead(livesLeft))
		{
			aliensWon = true;
			title.drawEndOfLevel(window, aliensWon);
			start = false;	// redraws the starting page
			// if just one bomb hits the ship, the level needs to start over
		}

		if (manyMissiles.areAllAliensDead(aliensHit))
		{
			aliensWon = false;
			title.drawEndOfLevel(window, aliensWon);
			start = false;	// redraws the starting page
			// the next level should start
		}

		// end the current frame; this makes everything that we have 
		// already "drawn" actually show up on the screen
		window.display();

		// At this point the frame we have built is now visible on screen.
		// Now control will go back to the top of the animation loop
		// to build the next frame. Since we begin by drawing the
		// background, each frame is rebuilt from scratch.

	}	 // end body of animation loop

	return 0;
}


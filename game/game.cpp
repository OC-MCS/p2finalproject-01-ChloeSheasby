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
#include "ManyMissiles.h"
#include "Bomb.h"
#include "ManyBombs.h"
#include "UI.h"
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
	const int WINDOW_WIDTH = 800;		// the size of the window
	const int WINDOW_HEIGHT = 600;
	const int MIN_SECONDS = 60;			// helps with making a bomb drop randomly
	const int MAX_SECONDS = 300;

	unsigned seed = time(0);			// also helps with making a bomb drop randomly
	srand(seed);

	// initializes the window
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Invaders");
	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);

	// gets the coordinates for the middle bottom of the screen that will be used to initialize ship
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
	Army army(Vector2f(100, 40));
	UI title;
	ManyMissiles manyMissiles;
	ManyBombs manyBombs;


	bool start = false;
	int livesLeft = 3;		// sets the initial amount of lives for the player
	bool aliensWon = false;
	bool mouseClicked = false;
	Level level = LEVEL_ONE;
	int randomSecond = 0;


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
					manyMissiles.addMissileToGroup(Vector2f(pos.x + 5, pos.y - 5), level);
					cout << "Adding a missile to the missile group." << endl;
				}
			}
			else if (event.type == Event::MouseButtonReleased)
			{
				Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				if (level != END)
				{
					start = title.handleStartClicked(mousePos);
				}
				else
				{
					start = false;
				}
				if (!start)
				{
					exit(-1);
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
			if (level == END)
			{
				title.drawEndOfGame(window, aliensWon);
			}
			else
			{
				title.drawTitlePage(window, level);
				if (level == LEVEL_TWO || level == LEVEL_THREE)
				{
					title.drawEndOfLevel(window);
				}
			}
		}
		else
		{
			title.drawLabels(window, livesLeft, army.returnEnemiesHit(), level);
			ship.moveShip();
	
			ship.drawShip(window);

			if (manyBombs.deleteBomb(ship.returnShipSprite(), livesLeft)
				|| army.hasArmyReachedEnemy(ship.returnShipSprite(), livesLeft) || army.moveArmy(livesLeft))
				// delete bomb returns true if the ship is hit once
			{
				// restart the level && move enemies to the top of the screen again
				army.resetPosition(40);
				// reset ship's position
				ship.resetPosition(Vector2f(shipX, shipY));
			}
		
			army.drawArmy(window);
	
			// this drops a bomb every 1 to 5 seconds 
			if (randomSecond == 0)
			{
				manyBombs.randomAlienDrop(army.returnRandomEnemyPosition(), level);
				if (level == LEVEL_THREE)
				{
					randomSecond = (rand() % 5) + 1;
				}
				else
				{
					randomSecond = (rand() % (MAX_SECONDS - MIN_SECONDS + 1)) + MIN_SECONDS;
				}
			}
			else
			{
				randomSecond--;
			}

			manyBombs.moveBombs();
			manyBombs.drawBombs(window);
		
			manyMissiles.moveMissiles();
			manyMissiles.drawManyMissiles(window);
			manyMissiles.deleteMissileAndEnemy(army.returnArmyList()); 
		}

		if (manyBombs.isShipDead(livesLeft))
		{
			aliensWon = true;
			start = false;	// redraws the starting page
			livesLeft = 3;
			level = END;
			// if just one bomb hits the ship, the level needs to start over
		}

		if (manyMissiles.areAllAliensDead(army.returnEnemiesHit()))
		{
			aliensWon = false;
			if (level == LEVEL_ONE)
			{
				level = LEVEL_TWO;
			}
			else if (level == LEVEL_TWO)
			{
				level = LEVEL_THREE;
			}
			else if (level == LEVEL_THREE)
			{
				level = END;
			}
			start = false;

			army.setNewLevel(level);
			manyBombs.clearBombList();
			manyMissiles.clearMissileList();
			ship.resetPosition(Vector2f(shipX, shipY));
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


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
	const int MAX_SECONDS = 180;

	unsigned seed = time(0);			// also helps with making a bomb drop randomly
	srand(seed);

	// initializes the window
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Invaders");
	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);

	// gets the coordinates for the middle bottom of the screen that will be used to initialize ship
	float shipX = window.getSize().x / 2.0f;
	float shipY = 500;

	Ship ship(Vector2f(shipX, shipY));	// creates the ship with the coordinates from above
	Army army(Vector2f(100, 40));		// creates the army with hard-coded coordinates
	UI title;							// creates a UI so different titles can be printed accordingly
	ManyMissiles manyMissiles;			// creates the group of missiles
	ManyBombs manyBombs;				// creates the group of bombs

	bool start = false;			// this flag gets changed based on if the start button is pressed or not
	int livesLeft = 3;			// sets the initial amount of lives for the player
	bool aliensWon = false;		// based on if the aliens won or not
	Level level = LEVEL_ONE;	// initializes an enum as the first value, which corresponds to the first level
	int randomSecond = 0;		// this helps in dropping bombs regularly

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		// For now, we just need this so we can click on the window and close it
		Event event;

		// draw background first, so everything that's drawn later will appear on top of background
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
					// initializes the missile when created based on the position of the ship
					Vector2f pos = ship.returnPosition();
					// adds a missile to the group of missile
					manyMissiles.addMissileToGroup(Vector2f(pos.x + 5, pos.y - 5), level);
					cout << "Adding a missile to the missile group." << endl;
				}
			}
			else if (event.type == Event::MouseButtonReleased)
			{
				Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				if (level != END)
				{
					// changes the start boolean based on if the mouse clicks the separate buttons
					start = title.handleStartClicked(mousePos);
				}
				else
				{
					// if it is the end of the game, start is automatically false so that the game must be exited
					start = false;
				}

				// if start is false, that means that the quit button was pressed and the program must be exited 
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
				// draws game over if the game is completely finished
				title.drawEndOfGame(window, aliensWon);
			}
			else
			{
				// the title is drawn with the start/continue and quit buttons
				title.drawTitlePage(window, level);

				// if the player can continue with another level, a different message is displayed
				if (level == LEVEL_TWO || level == LEVEL_THREE)
				{
					title.drawEndOfLevel(window);
				}
			}
		}
		else
		{
			// if the start button has been pressed, then the actual game is displayed
			// labels are drawn for the hit & life counters
			title.drawLabels(window, livesLeft, army.returnEnemiesHit(), level);

			ship.moveShip();
			ship.drawShip(window);

			// if the ship is hit once or the army reaches the ship, then these functions return true
			// delete bomb deletes a bomb if it hits the ship
			if (manyBombs.deleteBomb(ship.returnShipSprite(), livesLeft)
				|| army.hasArmyReachedShip(ship.returnShipSprite(), livesLeft))
			{
				// moves enemies to the top of the screen again 
				// and resets the ship's position if the ship is hit once
				army.resetPosition(40);
				ship.resetPosition(Vector2f(shipX, shipY));
			}
			
			army.moveArmy();
			army.drawArmy(window);
	
			// handles randomly dropping a bomb 
			if (randomSecond == 0)
			{
				// if the random second is 0 then manyBombs will drop a random bomb with the position of a random alien
				manyBombs.randomAlienDrop(army.returnRandomEnemyPosition(), level);

				// level three is special because bombs are dropped significantly closer together
				// than the other two "normal" levels
				if (level == LEVEL_THREE)
				{
					// this generates a new random second
					randomSecond = (rand() % 5) + 1;
				}
				else
				{
					// this generates a new random second that is within a reasonable range
					randomSecond = (rand() % (MAX_SECONDS - MIN_SECONDS + 1)) + MIN_SECONDS;
				}
			}
			else
			{
				// if the random second is not 0, then it decrements until it hits 0 and only drops a bomb then
				randomSecond--;
			}

			manyBombs.moveBombs();		// also deletes bombs if they move offscreen
			manyBombs.drawBombs(window);
		
			manyMissiles.moveMissiles();	// also deletes missiles if they move offscreen
			manyMissiles.drawManyMissiles(window);
			manyMissiles.deleteMissileAndEnemy(army.returnArmyList()); // deletes the missiles and enemies if they collide
		}

		// checks if ship is dead and if so, then the game is over and the aliens win
		if (manyBombs.isShipDead(livesLeft))	
		{
			aliensWon = true;
			start = false;	// redraws the starting page and allows the player to press quit
			level = END;	// sets the state of the game to game over
		}

		// checks if all the aliens are dead and if so, then the game is over and the player wins
		if (manyMissiles.areAllAliensDead(army.returnEnemiesHit()))
		{
			aliensWon = false;		// this says that the player has won
			if (level == LEVEL_ONE)
			{
				level = LEVEL_TWO;		// moves the level to the next one
			}
			else if (level == LEVEL_TWO)
			{
				level = LEVEL_THREE;
			}
			else if (level == LEVEL_THREE)
			{
				level = END;	// moves the state of the game to game over
			}	
			start = false;	// resets start so that the buttons can be used again

			army.setNewLevel(level);	// sets the new level based on which level it is
			manyBombs.clearBombList();	// clears the list of bombs
			manyMissiles.clearMissileList();	// clears the list of missiles
			ship.resetPosition(Vector2f(shipX, shipY));	// resets the ships position
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
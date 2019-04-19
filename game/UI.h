#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

enum Level { LEVEL_ONE, LEVEL_TWO, LEVEL_THREE, END };

class UI
{
private:
	Sprite background;
	Texture starsTexture;
	RectangleShape startBtn, quitBtn; // continueBtn;
	Font font;
public:
	UI()
	{
		if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))	// loads the font
			die("couldn't load font");

		if (!starsTexture.loadFromFile("stars.jpg"))
		{
			cout << "Unable to load stars texture!" << endl;
			exit(EXIT_FAILURE);
		}
		background.setTexture(starsTexture);
		// The texture file is 640x480, so scale it up a little to cover 800x600 window
		background.setScale(1.5, 1.5);
		
		startBtn.setPosition(Vector2f(250, 200));	// sets the button in the middle of the screen
		startBtn.setOutlineColor(Color::Transparent);
		startBtn.setOutlineThickness(2);
		startBtn.setSize(Vector2f(250, 50));
		startBtn.setFillColor(Color::Transparent);

		quitBtn.setPosition(Vector2f(340, 275));
		quitBtn.setOutlineColor(Color::Transparent);
		quitBtn.setOutlineThickness(1);
		quitBtn.setSize(Vector2f(75, 30));
		quitBtn.setFillColor(Color::Transparent);
	}
	bool handleStartClicked(Vector2f mouse)
	{
		bool start = false;
		if (startBtn.getGlobalBounds().contains(mouse))
		{
			start = true;
		}
		else if (quitBtn.getGlobalBounds().contains(mouse))
		{
			start = false;
		}
		return start;
	}
	void drawBackground(RenderWindow &win)
	{
		win.draw(background);
	}
	void drawTitlePage(RenderWindow &win, Level level)
	{
		win.draw(startBtn);
		win.draw(quitBtn);
		string startOrContinue;

		if (level == LEVEL_ONE)
		{
			startOrContinue = "START GAME";
		}
		else 
		{
			startOrContinue = "CONTINUE";
		}

		Text title("SPACE INVADERS", font, 55);
		title.setPosition(150, 100);
		title.setFillColor(Color::Yellow);
		win.draw(title);

		Text startColor(startOrContinue, font, 35);	// prints text
		startColor.setPosition(262, 204);
		startColor.setFillColor(Color::White);
		win.draw(startColor);

		drawQuit(win);
	}
	void drawQuit(RenderWindow &win)
	{
		Text quitColor("QUIT", font, 25);
		quitColor.setPosition(347, 275);
		quitColor.setFillColor(Color::White);
		win.draw(quitColor);
	}
	void drawLabels(RenderWindow &win, int &livesLeft, int aliensHit, Level level)
	{
		string numLives = to_string(livesLeft);
		string numAliens = to_string(aliensHit);
		string levelName;

		if (level == LEVEL_ONE)
		{
			levelName = "LEVEL ONE";
		}
		else if (level == LEVEL_TWO)
		{
			levelName = "LEVEL TWO";
		}
		else if (level == LEVEL_THREE)
		{
			levelName = "LEVEL THREE";
		}

		Text displayLivesLeft("Lives Left: ", font, 15);
		displayLivesLeft.setPosition(15, 15);
		displayLivesLeft.setFillColor(Color::White);
		win.draw(displayLivesLeft);

		Text numberOfLives(numLives, font, 15);
		numberOfLives.setPosition(90, 15);
		numberOfLives.setFillColor(Color::White);
		win.draw(numberOfLives);

		Text displayAliensHit("Aliens Hit: ", font, 15);
		displayAliensHit.setPosition(15, 32);
		displayAliensHit.setFillColor(Color::White);
		win.draw(displayAliensHit);

		Text numberOfAliens(numAliens, font, 15);
		numberOfAliens.setPosition(90, 32);
		numberOfAliens.setFillColor(Color::White);
		win.draw(numberOfAliens);

		Text displayLevel(levelName, font, 18);
		displayLevel.setPosition(350, 15);
		displayLevel.setFillColor(Color::Yellow);
		win.draw(displayLevel);
	}
	void drawEndOfGame(RenderWindow &win, bool aliensWon)
	{
		Text gameOver("GAME OVER", font, 55);
		gameOver.setPosition(150, 100);
		gameOver.setFillColor(Color::Yellow);
		win.draw(gameOver);

		win.draw(quitBtn);
		drawQuit(win);

		string winner;
		if (aliensWon)
		{
			winner = "ALIENS";
		}
		else
		{
			winner = "PLAYER";
		}

		Text displayWinner("WINNER", font, 55);
		displayWinner.setPosition(275, 325);
		displayWinner.setFillColor(Color::Yellow);
		win.draw(displayWinner);

		Text whoTheWinnerIs(winner, font, 100);
		whoTheWinnerIs.setPosition(200, 375);
		whoTheWinnerIs.setFillColor(Color::Yellow);
		win.draw(whoTheWinnerIs);
	}
	void drawEndOfLevel(RenderWindow &win)
	{
		Text continueNext("continue to next level...", font, 30);
		continueNext.setPosition(275, 325);
		continueNext.setFillColor(Color::Yellow);
		win.draw(continueNext);
	}
	//==================================================
	// this exits the program if the font does not load
	//==================================================
	void die(string msg)
	{
		cout << msg << endl;
		exit(-1);
	}

};

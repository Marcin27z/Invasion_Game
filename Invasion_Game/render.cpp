/*#include "render.h"
#include <string>
#include <iostream>
#include <sstream>
std::string intToStr(int s)
{
	std::stringstream ss;
	ss << s;
	return ss.str();
}
void setTextBox(sf::Text *text, sf::Font *font, std::string s, int size, sf::Color color)
{
	text->setFont(*font);
	text->setString(s);
	text->setCharacterSize(size);
	text->setFillColor(color);
}
void setSprite(sf::Sprite *sprite, sf::Texture *texture, int originX = 0, int originY = 0, int scaleX = 1, int scaleY = 1, int positionX = 0, int positionY = 0, int rotation = 0)
{
	sprite->setTexture(*texture);
	sprite->setScale(scaleX, scaleY);
	sprite->setOrigin(originX, originY);
	sprite->setPosition(positionX, positionY);
	sprite->setRotation(rotation);
}
void center(sf::Text *text, int offsetY = 0, int offsetX = 0)
{
	sf::FloatRect  TextRect = text->getLocalBounds();
	text->setOrigin(TextRect.left + TextRect.width / 2.0f, TextRect.top + TextRect.height / 2.0f);
	text->setPosition(sf::Vector2f((1024 / 2.0f) + offsetX, (768 / 2.0f) + offsetY));
}
void renderingThread(sf::RenderWindow* window)
{
	extern int opt;
	extern bool game;
	sf::Font font;
	font.loadFromFile("nasalization-rg.ttf");
	sf::Color color(65, 105, 255);
	sf::Color selectedColor(200, 100, 100);
	sf::Text menu;
	sf::Text play;
	sf::Text exit;

	////
	/*menu.setFont(font);
	menu.setString("MENU");
	menu.setCharacterSize(64);
	menu.setFillColor(color);
	setTextBox(&menu, &font, "MENU", 64, color);
	/////
	/*play.setFont(font);
	play.setString("Play");
	play.setCharacterSize(32);
	play.setFillColor(color);
	setTextBox(&play, &font, "Play", 32, color);
	/////	
	/*exit.setFont(font);
	exit.setString("Exit");
	exit.setCharacterSize(32);
	exit.setFillColor(color);
	setTextBox(&exit, &font, "Exit", 32, color);
	/////
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("Space.gif");
	sf::Sprite background;
	setSprite(&background, &backgroundTexture, 0, 0, 3, 3);
	//background.setTexture(backgroundTexture);
	//background.setScale(3.0f, 3.0f);
	/*sf::FloatRect  menuTextRect = menu.getLocalBounds();
	sf::FloatRect playTextRect = play.getLocalBounds();
	sf::FloatRect exitTextRect = exit.getLocalBounds();

	menu.setOrigin(menuTextRect.left + menuTextRect.width / 2.0f, menuTextRect.top + menuTextRect.height / 2.0f);
	menu.setPosition(sf::Vector2f(1024 / 2.0f, (768 / 2.0f) - 60));
	play.setOrigin(playTextRect.left + playTextRect.width / 2.0f, playTextRect.top + playTextRect.height / 2.0f);
	play.setPosition(sf::Vector2f(1024 / 2.0f, (768 / 2.0f)));
	exit.setOrigin(exitTextRect.left + exitTextRect.width / 2.0f, exitTextRect.top + exitTextRect.height / 2.0f);
	exit.setPosition(sf::Vector2f(1024 / 2.0f, (768 / 2.0f) + 40));
	
	center(&menu, -60);
	center(&play);
	center(&exit, 40);

	//////
	while (!game)
	{
		if (opt == 0) play.setFillColor(selectedColor);
		else  play.setFillColor(color);
		if (opt == 1) exit.setFillColor(selectedColor);
		else  exit.setFillColor(color);
		window->clear();
		window->draw(background);
		window->draw(menu);
		window->draw(play);
		window->draw(exit);
		window->display();
	}
	////////////
	std::string points;
	sf::Text playAgain;
	sf::Text pointsText;
	sf::Text gameOverText;
	////
	/*playAgain.setFont(font);
	playAgain.setString("Play again");
	playAgain.setCharacterSize(32);
	playAgain.setFillColor(color);
	setTextBox(&playAgain, &font, "Play again", 32, color);
	////
	/*pointsText.setFont(font);
	pointsText.setString("Points: ");
	pointsText.setCharacterSize(24);
	pointsText.setFillColor(color);
	setTextBox(&pointsText, &font, "Points:", 24, color);
	//////
	/*gameOverText.setFont(font);
	gameOverText.setString("Game Over");
	gameOverText.setCharacterSize(64);
	gameOverText.setFillColor(color);
	
	setTextBox(&gameOverText, &font, "game Over", 64, color);
	///////
	/*sf::FloatRect playAgainTextRect = playAgain.getLocalBounds();
	sf::FloatRect  pointsTextRect = pointsText.getLocalBounds();
	sf::FloatRect gameOverTextRect = gameOverText.getLocalBounds();
	playAgain.setOrigin(playAgainTextRect.left + playAgainTextRect.width / 2.0f, playAgainTextRect.top + playAgainTextRect.height / 2.0f);
	playAgain.setPosition(sf::Vector2f(1024 / 2.0f, (768 / 2.0f) + 100));
	gameOverText.setOrigin(gameOverTextRect.left + gameOverTextRect.width / 2.0f, gameOverTextRect.top + gameOverTextRect.height / 2.0f);
	gameOverText.setPosition(sf::Vector2f(1024 / 2.0f, (768 / 2.0f) - 60));
	exit.setPosition(sf::Vector2f(1024 / 2.0f, (768 / 2.0f) + 140));
	center(&playAgain, 100);
	center(&gameOverText, -60);
	center(&exit, 140);
	/////////
	extern Player player;
	extern Ship::Projectile *proj[PPROJ];
	extern Enemy *enemy[10];
	extern Enemy::Projectile *enemyProj[EPROJ];
	extern Enemy::Projectile *enemyProjDiagonalLeft[EPROJ];
	extern Enemy::Projectile *enemyProjDiagonalRight[EPROJ];
	////
	sf::Texture playerShipTexture;
	playerShipTexture.loadFromFile("Statek.png");
	sf::Texture projectileTexture;
	projectileTexture.loadFromFile("projectile.png");
	sf::Texture enemyShipTexture;
	enemyShipTexture.loadFromFile("Statek.png");
	/////
	sf::Sprite hpSprite[MAX_HP];
	for (int i = 0; i < MAX_HP; i++)
	{
		/*hpSprite[i].setTexture(playerShipTexture);
		hpSprite[i].setPosition(10 + (32 * i), 740);
		hpSprite[i].setScale(1, 1);
		hpSprite[i].setOrigin(8, 8);
		setSprite(&hpSprite[i], &playerShipTexture, 8, 8, 1, 1, 10 + (32 * i), 740);
	}
	////////
	sf::Sprite playerShip;
	/*playerShip.setTexture(playerShipTexture);
	playerShip.setScale(2, 2);
	playerShip.setOrigin(16, -16);
	playerShip.setPosition(player.getx(), player.gety());
	setSprite(&playerShip, &playerShipTexture, 16, -16, 2, 2, player.getx(), player.gety());
	////////
	sf::Sprite enemyShip[ENEMY];
	for (int i = 0; i < ENEMY; i++)
	{
		/*enemyShip[i].setTexture(enemyShipTexture);
		enemyShip[i].setOrigin(16, 16);
		enemyShip[i].setRotation(180);
		enemyShip[i].setScale(2, 2);
		setSprite(&enemyShip[i], &enemyShipTexture, 16, 16, 2, 2, 0, 0, 180);
	}
	///////
	sf::Sprite projectile[PPROJ];
	for (int i = 0; i < PPROJ; i++)
	{
		/*projectile[i].setTexture(projectileTexture);
		projectile[i].setOrigin(8, -8);
		setSprite(&projectile[i], &projectileTexture, 8, -8);
	}
	sf::Sprite enemyProjectile[EPROJ];
	for (int i = 0; i < EPROJ; i++)
	{
		/*enemyProjectile[i].setTexture(projectileTexture);
		enemyProjectile[i].setOrigin(8, 8);
		setSprite(&enemyProjectile[i], &projectileTexture, 8, -8);
	}
	sf::Sprite enemyProjectileDiagonalLeft[EPROJ];
	for (int i = 0; i < EPROJ; i++)
	{
		/*enemyProjectileDiagonalLeft[i].setTexture(projectileTexture);
		enemyProjectileDiagonalLeft[i].setOrigin(8, 8);
		enemyProjectileDiagonalLeft[i].setRotation(45);
		setSprite(&enemyProjectileDiagonalLeft[i], &projectileTexture, 8, 8, 1, 1, 0 ,0, 45);
	}
	sf::Sprite enemyProjectileDiagonalRight[EPROJ];
	for (int i = 0; i < EPROJ; i++)
	{
		/*enemyProjectileDiagonalRight[i].setTexture(projectileTexture);
		enemyProjectileDiagonalRight[i].setOrigin(8, -8);
		enemyProjectileDiagonalRight[i].setRotation(-45);
		setSprite(&enemyProjectileDiagonalRight[i], &projectileTexture, 8, -8, 1, 1, 0, 0, -45);
	}
	///////////
	int y = player.gety();
	while (window->isOpen())
	{
		window->clear();
		window->draw(background);
		if (player.getHp() != 0) {
			playerShip.setPosition(player.getx(), y);
			for (int i = 0; i < PPROJ; i++)
			{
				if (proj[i] != NULL)
				{
					projectile[i].setPosition(proj[i]->getx(), proj[i]->gety());
					window->draw(projectile[i]);
				}
			}
			for (int i = 0; i < EPROJ; i++)
			{
				if (enemyProj[i] != NULL)
				{
					enemyProjectile[i].setPosition(enemyProj[i]->getx(), enemyProj[i]->gety());
					window->draw(enemyProjectile[i]);
				}
			}
			for (int i = 0; i < EPROJ; i++)
			{
				if (enemyProjDiagonalLeft[i] != NULL)
				{
					enemyProjectileDiagonalLeft[i].setPosition(enemyProjDiagonalLeft[i]->getx(), enemyProjDiagonalLeft[i]->gety());
					window->draw(enemyProjectileDiagonalLeft[i]);
				}
			}
			for (int i = 0; i < EPROJ; i++)
			{
				if (enemyProjDiagonalRight[i] != NULL)
				{
					enemyProjectileDiagonalRight[i].setPosition(enemyProjDiagonalRight[i]->getx(), enemyProjDiagonalRight[i]->gety());
					window->draw(enemyProjectileDiagonalRight[i]);
				}
			}
			for (int i = 0; i < ENEMY; i++)
			{
				if (enemy[i] != NULL)
				{
					enemyShip[i].setRotation(enemy[i]->getRotation());
					enemyShip[i].setPosition(enemy[i]->getx(), enemy[i]->gety());
					window->draw(enemyShip[i]);
				}
			}
			for (int i = 0; i < player.getHp(); i++)
			{
				window->draw(hpSprite[i]);
			}
			points = intToStr(player.getPoints());
			pointsText.setString("Points " + points);
			window->draw(playerShip);
		}
		else
		{
			pointsText.setCharacterSize(48);
			/*pointsTextRect = pointsText.getLocalBounds();
			pointsText.setOrigin(pointsTextRect.left + pointsTextRect.width / 2.0f, pointsTextRect.top + pointsTextRect.height / 2.0f);
			pointsText.setPosition(sf::Vector2f(1024 / 2.0f, (768 / 2.0f)));
			center(&pointsText);
			while (!game)
			{
				if (opt == 0) playAgain.setFillColor(selectedColor);
				else  playAgain.setFillColor(color);
				if (opt == 1) exit.setFillColor(selectedColor);
				else  exit.setFillColor(color);
				window->clear();
				window->draw(background);
				window->draw(gameOverText);
				window->draw(pointsText);
				window->draw(playAgain);
				window->draw(exit);
				window->display();
			}
			pointsText.setCharacterSize(24);
			pointsText.setOrigin(0, 0);
			pointsText.setPosition(0, 0);
		}
		window->draw(pointsText);
		window->display();
	}
}*/
#include "render.h"
std::string Render::intToStr(int s)
{
	std::stringstream ss;
	ss << s;
	return ss.str();
}
Render::Render() {
	y = 640;
	opt = 0;
	game = false;
}
void Render::center(sf::Text *text, int offsetY, int offsetX)
{
	sf::FloatRect  TextRect = text->getLocalBounds();
	text->setOrigin(TextRect.left + TextRect.width / 2.0f, TextRect.top + TextRect.height / 2.0f);
	text->setPosition(sf::Vector2f((1024 / 2.0f) + offsetX, (768 / 2.0f) + offsetY));
}

void Render::setColor(sf::Color *color, int r, int g, int b)
{
	sf::Color col(r, g, b);
	color = &col;
}
void Render::setTextBox(sf::Text *text, sf::Font *font, std::string s, int size, sf::Color color)
{
	text->setFont(*font);
	text->setString(s);
	text->setCharacterSize(size);
	text->setFillColor(color);
}
void Render::setSprite(sf::Sprite *sprite, sf::Texture *texture, int originX, int originY, int scaleX, int scaleY, int positionX, int positionY, int rotation)
{
	sprite->setTexture(*texture);
	sprite->setScale(scaleX, scaleY);
	sprite->setOrigin(originX, originY);
	sprite->setPosition(positionX, positionY);
	sprite->setRotation(rotation);
}
void Render::run()
{
	sf::Font font;
	font.loadFromFile("nasalization-rg.ttf");
	sf::Color color(65, 105, 255);
	sf::Color selectedColor(200, 100, 100);
	sf::Text menu;
	sf::Text play;
	sf::Text load;
	sf::Text exit;
	sf::Text loadLevel;
	setTextBox(&menu, &font, "MENU", 64, color);
	setTextBox(&play, &font, "Play", 32, color);
	setTextBox(&load, &font, "Load Game", 32, color);
	setTextBox(&exit, &font, "Exit", 32, color);
	setTextBox(&loadLevel, &font, "Load Level", 32, color);
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("Space.gif");
	sf::Sprite background;
	setSprite(&background, &backgroundTexture, 0, 0, 3, 3);
	center(&menu, -60);
	center(&play);
	center(&load, 40);
	center(&exit, 80);
	while (!game)
	{
		if (opt == 0) play.setFillColor(selectedColor);
		else  play.setFillColor(color);
		if (opt == 1) load.setFillColor(selectedColor);
		else  load.setFillColor(color);
		if(opt == 2) loadLevel.setFillColor(selectedColor);
		else  loadLevel.setFillColor(color);
		if (opt == 3) exit.setFillColor(selectedColor);
		else  exit.setFillColor(color);
		window->clear();
		window->draw(background);
		window->draw(menu);
		window->draw(play);
		window->draw(load);
		window->draw(exit);
		window->display();
	}
	std::string points;
	sf::Text playAgain;
	sf::Text pointsText;
	sf::Text gameOverText;
	setTextBox(&playAgain, &font, "Play again", 32, color);
	setTextBox(&pointsText, &font, "Points:", 24, color);
	setTextBox(&gameOverText, &font, "Game Over", 64, color);
	sf::Text continueText;
	sf::Text save;
	setTextBox(&continueText, &font, "Continue", 32, color);
	setTextBox(&save, &font, "Save", 32, color);
	sf::Texture playerShipTexture;
	playerShipTexture.loadFromFile("Statek.png");
	sf::Texture projectileTexture;
	projectileTexture.loadFromFile("projectile.png");
	sf::Texture enemyShipTexture;
	enemyShipTexture.loadFromFile("Statek.png");
	sf::Texture powerUpTexture[3];
	powerUpTexture[0].loadFromFile("powerup1.png");
	powerUpTexture[1].loadFromFile("powerup2.png");
	powerUpTexture[2].loadFromFile("powerup3.png");
	sf::Sprite hpSprite[MAX_HP];
	for (int i = 0; i < MAX_HP; i++) setSprite(&hpSprite[i], &playerShipTexture, 8, 8, 1, 1, 10 + (32 * i), 740);
	sf::Sprite playerShip;
	setSprite(&playerShip, &playerShipTexture, 16, -16, 2, 2, playerhandler.player.getx(), playerhandler.player.gety());
	sf::Sprite enemyShip[ENEMY];
	for (int i = 0; i < ENEMY; i++) setSprite(&enemyShip[i], &enemyShipTexture, 16, 16, 2, 2, 0, 0, 180);
	sf::Sprite projectile[5];
	for (int i = 0; i < 5; i++) setSprite(&projectile[i], &projectileTexture, 8, -8);
	sf::Sprite enemyProjectile[EPROJ];
	sf::Sprite enemyProjectileDiagonalLeft[EPROJ];
	sf::Sprite enemyProjectileDiagonalRight[EPROJ];
	for (int i = 0; i < EPROJ; i++)
	{
		setSprite(&enemyProjectile[i], &projectileTexture, 8, -8);
		setSprite(&enemyProjectileDiagonalLeft[i], &projectileTexture, 8, 8, 1, 1, 0, 0, 45);
		setSprite(&enemyProjectileDiagonalRight[i], &projectileTexture, 8, -8, 1, 1, 0, 0, -45);
	}
	sf::Sprite powerUp[3];
	for (int i = 0; i < 3; i++)
	{
		setSprite(&powerUp[i], &powerUpTexture[i], 8 - 8);
	}
	while (window->isOpen())
	{
		window->clear();
		window->draw(background);
		if (playerhandler.player.getHp() != 0) {
			playerShip.setPosition(playerhandler.player.getx(), y);
			for (int i = 0; i < playerhandler.player.getPlayerProjectile(); i++)
			{
				if (playerhandler.proj[i] != NULL)
				{
					projectile[i].setPosition(playerhandler.proj[i]->getx(), playerhandler.proj[i]->gety());
					window->draw(projectile[i]);
				}
			}
			for (int i = 0; i < EPROJ; i++)
			{
				if (enemyHandler.enemyProj[i] != NULL)
				{
					enemyProjectile[i].setPosition(enemyHandler.enemyProj[i]->getx(), enemyHandler.enemyProj[i]->gety());
					window->draw(enemyProjectile[i]);
				}
			}
			for (int i = 0; i < 3; i++)
			{
				if (playerhandler.powerUpHandler.powerUp[i] != NULL)
				{
						powerUp[i].setPosition(playerhandler.powerUpHandler.powerUp[i]->getx(), playerhandler.powerUpHandler.powerUp[i]->gety());
						window->draw(powerUp[i]);
				}
			}
			for (int i = 0; i < EPROJ; i++)
			{
				if (enemyHandler.enemyProjDiagonalLeft[i] != NULL)
				{
					enemyProjectileDiagonalLeft[i].setPosition(enemyHandler.enemyProjDiagonalLeft[i]->getx(), enemyHandler.enemyProjDiagonalLeft[i]->gety());
					window->draw(enemyProjectileDiagonalLeft[i]);
				}
			}
			for (int i = 0; i < EPROJ; i++)
			{
				if (enemyHandler.enemyProjDiagonalRight[i] != NULL)
				{
					enemyProjectileDiagonalRight[i].setPosition(enemyHandler.enemyProjDiagonalRight[i]->getx(), enemyHandler.enemyProjDiagonalRight[i]->gety());
					window->draw(enemyProjectileDiagonalRight[i]);
				}
			}
			for (int i = 0; i < ENEMY; i++)
			{
				if (enemyHandler.enemy[i] != NULL)
				{
					enemyShip[i].setRotation(enemyHandler.enemy[i]->getRotation());
					enemyShip[i].setPosition(enemyHandler.enemy[i]->getx(), enemyHandler.enemy[i]->gety());
					window->draw(enemyShip[i]);
				}
			}
			for (int i = 0; i < playerhandler.player.getHp(); i++)
			{
				window->draw(hpSprite[i]);
			}
			points = intToStr(playerhandler.player.getPoints());
			pointsText.setString("Points " + points);
			window->draw(playerShip);
		}
		else if(playerhandler.player.getHp() == 0)
		{
			pointsText.setCharacterSize(48);
			center(&pointsText);
			center(&playAgain, 100);
			center(&gameOverText, -60);
			center(&exit, 140);
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
		if (!playerhandler.nopause)
		{	
			center(&continueText, -40);
			center(&save);
			center(&load, 40);
			center(&exit, 80);
			while (!playerhandler.nopause)
			{
				if (opt == 0) continueText.setFillColor(selectedColor);
				else  continueText.setFillColor(color);
				if (opt == 1) save.setFillColor(selectedColor);
				else  save.setFillColor(color);
				if (opt == 2) load.setFillColor(selectedColor);
				else  load.setFillColor(color);
				if (opt == 3) exit.setFillColor(selectedColor);
				else  exit.setFillColor(color);
				window->clear();
				window->draw(background);
				window->draw(pointsText);
				window->draw(continueText);
				window->draw(save);
				window->draw(load);
				window->draw(exit);
				window->display();
			}
		}
		window->draw(pointsText);
		window->display();
	}
}


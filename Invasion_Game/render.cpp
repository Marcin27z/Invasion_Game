#include "render.h"
#include <string>
void renderingThread(sf::RenderWindow* window)
{
	extern Player player;
	extern Ship::Projectile *proj[PPROJ];
	extern Enemy *enemy[10];
	extern Enemy::Projectile *enemyProj[EPROJ];
	extern Enemy::Projectile *enemyProjDiagonalLeft[EPROJ];
	extern Enemy::Projectile *enemyProjDiagonalRight[EPROJ];
	////////////
	sf::Font font;
	font.loadFromFile("nasalization-rg.ttf");
	sf::Color color(65, 105, 255);
	sf::Text pointsText;
	sf::Text gameOverText;
	std::string points = std::to_string(player.getPoints());
	///////
	pointsText.setFont(font);
	pointsText.setString("Points: " + points);
	pointsText.setCharacterSize(24);
	pointsText.setFillColor(color);
	//////
	gameOverText.setFont(font);
	gameOverText.setString("Game Over");
	gameOverText.setCharacterSize(64);
	gameOverText.setFillColor(color);
	///////
	sf::Texture playerShipTexture;
	playerShipTexture.loadFromFile("Statek.png");
	sf::Texture projectileTexture;
	projectileTexture.loadFromFile("projectile.png");
	sf::Texture enemyShipTexture;
	enemyShipTexture.loadFromFile("Statek.png");
	sf::Sprite playerShip;
	playerShip.setTexture(playerShipTexture);
	playerShip.setScale(2, 2);
	playerShip.setOrigin(16, -16);
	playerShip.setPosition(player.getx(), player.gety());
	sf::Sprite enemyShip[10];
	for (int i = 0; i < 10; i++)
	{
		enemyShip[i].setTexture(enemyShipTexture);
		enemyShip[i].setOrigin(16, -16);
		enemyShip[i].setRotation(180);
		enemyShip[i].setScale(2, 2);
	}
	sf::Sprite projectile[PPROJ];
	for (int i = 0; i < PPROJ; i++)
	{
		projectile[i].setTexture(projectileTexture);
		projectile[i].setOrigin(8, -8);
	}
	sf::Sprite enemyProjectile[EPROJ];
	for (int i = 0; i < EPROJ; i++)
	{
		enemyProjectile[i].setTexture(projectileTexture);
		enemyProjectile[i].setOrigin(8, -8);
	}
	sf::Sprite enemyProjectileDiagonalLeft[EPROJ];
	for (int i = 0; i < EPROJ; i++)
	{
		enemyProjectileDiagonalLeft[i].setTexture(projectileTexture);
		enemyProjectileDiagonalLeft[i].setOrigin(8, -8);
		enemyProjectileDiagonalLeft[i].setRotation(45);
	}
	sf::Sprite enemyProjectileDiagonalRight[EPROJ];
	for (int i = 0; i < EPROJ; i++)
	{
		enemyProjectileDiagonalRight[i].setTexture(projectileTexture);
		enemyProjectileDiagonalRight[i].setOrigin(8, -8);
		enemyProjectileDiagonalRight[i].setRotation(-45);
	}
	///////////
	int y = player.gety();
	while (window->isOpen())
	{
		window->clear();
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
			for (int i = 0; i < 10; i++)
			{
				if (enemy[i] != NULL)
				{
					enemyShip[i].setPosition(enemy[i]->getx(), enemy[i]->gety());
					window->draw(enemyShip[i]);
				}
			}
			points = std::to_string(player.getPoints());
			pointsText.setString("Points " + points);
			window->draw(playerShip);
		}
		else
		{
			sf::FloatRect  pointsTextRect = pointsText.getLocalBounds();
			sf::FloatRect gameOverTextRect = gameOverText.getLocalBounds();
			pointsText.setOrigin(pointsTextRect.left + pointsTextRect.width / 2.0f, pointsTextRect.top + pointsTextRect.height / 2.0f);
			pointsText.setPosition(sf::Vector2f(1024 / 2.0f, (768 / 2.0f) + 40));
			gameOverText.setOrigin(gameOverTextRect.left + gameOverTextRect.width / 2.0f, gameOverTextRect.top + gameOverTextRect.height / 2.0f);
			gameOverText.setPosition(sf::Vector2f(1024 / 2.0f, (768 / 2.0f) - 20));
			pointsText.setCharacterSize(48);
			window->draw(gameOverText);

		}
		window->draw(pointsText);
		window->display();
	}
}
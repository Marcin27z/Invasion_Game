#include "playerhandler.h"
PlayerHandler::PlayerHandler()
{
	nopause = true;
	y = 640;
	for (int i = 0; i < 5; i++)
	{
		proj[i] = NULL;
	}
}
void PlayerHandler::destroyProj(Ship::Projectile **proj)
{
	delete(*proj);
	*proj = NULL;
}
int PlayerHandler::getAction(sf::RenderWindow* window)
{
	static int x;
	sf::Event event;
	static bool spacePressed;
	static bool escapePressed;
	if (window->pollEvent(event))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !escapePressed)
		{
			nopause = !nopause;
		}
		if (event.type == sf::Event::Closed) window->close();
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			spacePressed = false;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			escapePressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			x = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			x = -1;
		}
		else x = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !spacePressed)
		{
			for (int i = 0; i < player.getPlayerProjectile(); i++)
			{
				if (proj[i] == NULL)
				{
					proj[i] = player.shoot(-32);
					break;
				}
			}
			spacePressed = true;
		}
	}
	return x;
}
void PlayerHandler::update(int x, PowerUpHandler *powerUpHandler)
{
	if (x == 1 && player.getx() < MAX_RIGHT) player.move(1, 0);
	if (x == -1 && player.getx() > MAX_LEFT) player.move(-1, 0);
	for (int i = 0; i < 3; i++)
	{
		if (powerUpHandler->powerUp[i] != NULL)
		{
			if (sqrt(pow(player.getx() - powerUpHandler->powerUp[i]->getx(), 2) + pow(player.gety() +10 - powerUpHandler->powerUp[i]->gety(), 2)) < 20)
			{
				delete(powerUpHandler->powerUp[i]);
				powerUpHandler->powerUp[i] = NULL;
				powerUpHandler->powerUpEffect(i, &player);
			}
		}
	}
}
void PlayerHandler::updateProj(Enemy *enemy[ENEMY])
{
	const int enemyHitRadius = 28;
	// move player's projectiles
	for (int i = 0; i < player.getPlayerProjectile(); i++)
	{
		if (proj[i] != NULL)
		{
			proj[i]->move(-1.5);

			for (int j = 0; j < ENEMY; j++)
			{
				if (enemy[j] != NULL)
					if (sqrt(pow(proj[i]->gety() - enemy[j]->gety(), 2) + pow(proj[i]->getx() - enemy[j]->getx(), 2)) < enemyHitRadius)
					{
						destroyProj(&proj[i]);
						powerUpHandler.generatePowerUp(enemy[j]->getx(), enemy[j]->gety());
						delete(enemy[j]);
						enemy[j] = NULL;
						player.addPoints(10);
						if (player.getPoints() % 300 == 0 && player.getHp() < MAX_HP) player.addHp();
						break;
					}
			}
			if (proj[i] != NULL && proj[i]->gety() < 0)
			{
				delete(proj[i]);
				proj[i] = NULL;
			}
		}

	}
}
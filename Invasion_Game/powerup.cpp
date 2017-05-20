#include<cstdlib>
#include "powerup.h"
PowerUp::PowerUp(double x, double y)
{
	setx(x);
	sety(y);
}
double PowerUp::getx()
{
	return this->x;
}

double PowerUp::gety()
{
	return this->y;
}

void PowerUp::setx(double x)
{
	this->x = x;
}

void PowerUp::sety(double y)
{
	this->y = y;
}
double PowerUp::getId()
{
	return this->y;
}

void PowerUp::setId(int id)
{
	this->x = x;
}

void PowerUp::move(double x, double y)
{
	this->setx(this->getx() + x);
	this->sety(this->gety() + y);
}
void PowerUpHandler::activate(int i)
{
	this->active[i] = true;
}
void PowerUpHandler::disactivate(int i)
{
	this->active[i] = false;
}
bool PowerUpHandler::getState(int i)
{
	return this->active[i];
}
void PowerUpHandler::generatePowerUp(double x, double y)
{
	int r = rand() % 20;
	if ((r < 2) && powerUp[0] == NULL)
	{
		powerUp[0] = new PowerUp(x, y);
		powerUp[0]->setId(0);
	}
	else if ((r < 4) && powerUp[1] == NULL)
	{
		powerUp[1] = new PowerUp(x, y);
		powerUp[1]->setId(1);
	}
	else if ((r < 6) && powerUp[2] == NULL)
	{
		powerUp[2] = new PowerUp(x, y);
		powerUp[2]->setId(2);
	}
}

void PowerUpHandler::updatePowerUp()
{
	for (int i = 0; i < 3; i++)
	{
		if (powerUp[i] != NULL)
		{
			powerUp[i]->move(0, 0.1);
			if (powerUp[i]->gety() == 768)
			{
				delete (powerUp);
				powerUp[i] = NULL;
			}
		}
	}
}

void PowerUpHandler::powerUpEffect(int id, Player *player, float time)
{
	if (id == 0)
	{
		player->setPlayerProjectile(1);
	}
	if (id == 2) player->setPlayerProjectile(3);
	additionalTime[id] = sf::seconds(time);
	powerUpClock[id].restart();
	powerUpTime[id] = powerUpClock[id].getElapsedTime();
	this->activate(id);
}

void PowerUpHandler::powerUpEffectUpdate(Player *player)
{
	for (int i = 0; i < 3; i++)
	{
		powerUpTime[i] = powerUpClock[i].getElapsedTime();
		powerUpTime[i] += additionalTime[i];

		if ((powerUpTime[i].asSeconds() > 10) && this->getState(i))
		{
			player->setPlayerProjectile(2);
			this->disactivate(i);
			additionalTime[i] = sf::Time::Zero;

		}
	}
}

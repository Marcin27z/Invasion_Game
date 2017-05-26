#include<cstdlib>
#include "powerup.h"
PowerUp::PowerUp(double x, double y)
{
	setx(x);
	sety(y);
	//setId(id);
}
ThreeShots::ThreeShots(double x, double y)
	:PowerUp(x, y)
{
}
OneShot::OneShot(double x, double y)
	: PowerUp(x, y)
{
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
/*double PowerUp::getId()
{
	return this->y;
}*/

/*void PowerUp::setId(int id)
{
	this->x = x;
}*/

void PowerUp::move(double x, double y)
{
	this->setx(this->getx() + x);
	this->sety(this->gety() + y);
}
void PowerUp::activate()
{
	this->active = true;
}
void PowerUp::disactivate()
{
	this->active = false;
}
bool PowerUp::getState()
{
	return this->active;
}
void PowerUpHandler::generatePowerUp(double x, double y)
{
	int r = rand() % 20;
	if ((r < 2) && powerUp[0] == NULL)
	{
		powerUp[0] = new OneShot(x, y);
		//powerUp[0]->setId(0);
	}
	else if ((r < 4) && powerUp[1] == NULL)
	{
		powerUp[1] = new ThreeShots(x, y);
		//powerUp[1]->setId(1);
	}
	else if ((r < 6) && powerUp[2] == NULL)
	{
		powerUp[2] = new ThreeShots(x, y);
		//powerUp[2]->setId(2);
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

void ThreeShots::powerUpEffect(Player *player, float time)
{
	player->setPlayerProjectile(3);
	additionalTime = sf::seconds(time);
	powerUpClock.restart();
	powerUpTime = powerUpClock.getElapsedTime();
	this->activate();
}
void OneShot::powerUpEffect(Player *player, float time)
{
	player->setPlayerProjectile(1);
	additionalTime = sf::seconds(time);
	powerUpClock.restart();
	powerUpTime = powerUpClock.getElapsedTime();
	this->activate();
}

void PowerUpHandler::powerUpEffectUpdate(Player *player)
{
	for (int i = 0; i < 3; i++)
	{
		powerUpTime[i] = powerUpClock.getElapsedTime();
		powerUpTime[i] += additionalTime[i];

		if ((powerUpTime[i].asSeconds() > 10) && this->getState())
		{
			player->setPlayerProjectile(2);
			this->powerUp[i]->disactivate();
			powerUp[i]->additionalTime = sf::Time::Zero;

		}
	}
}

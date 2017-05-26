#ifndef __PLAYERHANDLER_H__
#define __PLAYERHANDLER_H__

#include "ship.h"
#include "powerup.h"
#include <SFML/Graphics.hpp>
class PlayerHandler
{
public:
	Player player;
	PowerUpHandler powerUpHandler;
	sf::Clock clock;
	sf::Time time;
	sf::Clock playerClock;
	sf::Time playerTime;
	Ship::Projectile *proj[5];
	int y;
	PlayerHandler();
	bool nopause;
	void destroyProj(Ship::Projectile **);
	int getAction(sf::RenderWindow*);
	void update(int, PowerUpHandler *);
	void updateProj(Enemy * [ENEMY]);

};

#endif
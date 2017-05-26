#ifndef __ENEMYHANDLER_H__
#define __ENEMYHANDLER_H__

#include "ship.h"
#include <SFML/Graphics.hpp>
#include<cmath>
class EnemyHandler
{
public:
	Enemy *enemy[ENEMY];
	Ship::Projectile *enemyProj[EPROJ];
	Ship::Projectile *enemyProjDiagonalLeft[EPROJ];
	Ship::Projectile *enemyProjDiagonalRight[EPROJ];
	sf::Clock enemyGenClock;
	sf::Time enemyGenTime;
	sf::Clock enemyChargeClock;
	sf::Time enemyChargeTime;
	//sf::Clock enemyC;
	//sf::Time enemyT;
	sf::Clock enemyProjClock;
	sf::Time enemyProjTime;
	int eOffsetX[ENEMY];
	int edx[ENEMY];
	EnemyHandler();
	void destroyProj(Ship::Projectile **proj);
	void destroyAllProjs();
	void enemyGen();
	void enemyCharge(Player *);
	void enemyUpdate(Player *);
	void enemyProjUpdate(Player *);
};

#endif
#include "powerup.h"
#include<cmath>
#define MAX_LEFT 38
#define MAX_RIGHT 988
class EnemyHandler
{
public:
	Enemy *enemy[ENEMY];
	Enemy2 *enemy2[ENEMY];
	Enemy3 *enemy3[ENEMY];
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
	int eOffsetX2[ENEMY];
	int edx2[ENEMY];
	int eOffsetX3[ENEMY];
	int edx3[ENEMY];
	EnemyHandler();
	void destroyProj(Ship::Projectile **proj);
	void destroyAllProjs();
	void enemyGen();
	void enemyCharge(Player *);
	void enemyUpdate(Player *);
	void enemyProjUpdate(Player *);
};
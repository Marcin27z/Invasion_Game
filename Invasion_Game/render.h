#include <SFML/Graphics.hpp>
#include "ship.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<sstream>
#define MAX_LEFT 38
#define MAX_RIGHT 988
#define MAX_UP 0
#define MAX_DOWN 660
#define PLAYER_DEF_X 512
#define PLAYER_DEF_Y 640
class PlayerHandler
{
public:
	Player player;
	sf::Clock clock;
	sf::Time time;
	sf::Clock playerClock;
	sf::Time playerTime;
	Ship::Projectile *proj[PPROJ];
	int y = 640;
	PlayerHandler();
	void destroyProj(Ship::Projectile **);
	int getAction(sf::RenderWindow*);
	void update(int);
	void updateProj(Enemy *[ENEMY]);
};
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
	sf::Clock enemyC;
	sf::Time enemyT;
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
class Render
{
public:
	std::string intToStr(int);
	sf::RenderWindow *window;
	PlayerHandler playerhandler;
	EnemyHandler enemyHandler;
	Render();
	int y;
	int opt;
	bool game;
	void center(sf::Text *, int = 0, int = 0);
	void setColor(sf::Color *, int , int , int );
	void setTextBox(sf::Text *, sf::Font *, std::string, int, sf::Color);
	void setSprite(sf::Sprite *, sf::Texture *, int = 0, int = 0, int = 1, int = 1, int = 0, int = 0, int = 0);
	void run();
};

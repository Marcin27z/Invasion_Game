#include <SFML/Graphics.hpp>
#include "ship.h"
class PowerUp
{
public:
	PowerUp(double, double);
	double getx();
	double gety();
	void setx(double);
	void sety(double);
	//double getId();
	//void setId(int);
	void move(double, double);

	virtual void powerUpEffect(Player *, float = 0.0) = 0;
private:
	double x;
	double y;
	//int id;
};
class ThreeShots
	:public PowerUp
{
public:
	ThreeShots(double, double);
	virtual void powerUpEffect(Player *, float = 0.0);
};
class OneShot
	:public PowerUp
{
public:
	virtual void powerUpEffect(Player *, float = 0.0);
	OneShot(double, double);
};
class PowerUpHandler
{
public:
	PowerUp *powerUp[3];
	//ThreeShots threeShots;
	//OneShot oneShot;
	sf::Clock powerUpClock[3];
	sf::Time powerUpTime[3];
	sf::Time additionalTime[3];
	void generatePowerUp(double, double);
	void updatePowerUp();
	//void powerUpEffect(int, Player *, float = 0.0);
	void powerUpEffectUpdate(Player *);
	void activate(int);
	void disactivate(int);
	bool getState(int);
private:
	bool active[3];
};
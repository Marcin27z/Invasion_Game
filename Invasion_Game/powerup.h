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
	double getId();
	void setId(int);
	void move(double, double);
private:
	double x;
	double y;
	int id;
	
};
class PowerUpHandler
{
public:
	PowerUp *powerUp[3];
	sf::Clock powerUpClock[3];
	sf::Time powerUpTime[3];
	sf::Time additionalTime[3];
	void generatePowerUp(double, double);
	void updatePowerUp();
	void powerUpEffect(int, Player *, float = 0.0);
	void powerUpEffectUpdate(Player * player);
	void activate(int);
	void disactivate(int);
	bool getState(int);
private:
	bool active[3];
};
#define EPROJ 10
#define ENEMY 10
#define MAX_HP 10
class Ship
{
private:
	double x;
	double y;
public:
	class Projectile
	{
	private:
		double y;
		double x;
	public:
		Projectile(double, double);
		double gety();
		void sety(double);
		double getx();
		void setx(double);
		void move(double, double = 0);
	};
	double getx();
	double gety();
	void setx(double);
	void sety(double);
	void move(double, double);
	void setPos(double, double);
	Projectile* shoot(int);
};
class Enemy
	: public Ship
{
	double rotation;
	double slope;
public:
	Enemy(double, double, double = 180, double = 0.0);
	void setRotation(double);
	double getRotation();
	void setSlope(double);
	double getSlope();
};
class Enemy1
	:public Enemy
{
public:
	Enemy1(double, double, double = 90, double = 0.0);
};
class Enemy2
	:public Enemy
{
public:
	Enemy2(double, double, double = 0, double = 0.0);
};
class Enemy3
	:public Enemy
{
public:
	Enemy3(double, double, double = 180, double = 0.0);
};
class Player
	: public Ship
{
private:
	int playerProjectile;
	int hp;
	int points;
public:
	void setHp(int);
	int getHp();
	void setPlayerProjectile(int);
	int getPlayerProjectile();
	void addHp();
	void takeHp();
	void setPoints(int);
	int getPoints();
	void addPoints(int);
};


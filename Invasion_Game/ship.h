#define PPROJ 3
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
		int y;
		int x;
	public:
		double gety();
		void sety(double);
		int getx();
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
class Player
	: public Ship
{
private:
	int hp;
	int points;
public:
	void setHp(int);
	int getHp();
	void addHp();
	void takeHp();
	void setPoints(int);
	int getPoints();
	void addPoints(int);
};


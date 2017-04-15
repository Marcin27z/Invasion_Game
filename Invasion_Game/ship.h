#define PPROJ 3
#define EPROJ 10
class Ship
{
private:
	int x;
	int y;
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
		void setx(int);
	};
	int getx();
	int gety();
	void setx(int);
	void sety(int);
	void move(int, int);
	void setpos(int, int);
	Projectile* shoot();
};
class Enemy
	: public Ship
{
	
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
	void setPoints(int);
	int getPoints();
};


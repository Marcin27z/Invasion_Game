#include "ship.h"
int Ship::getx()
{
	return this->x;
}
int Ship::gety()
{
	return this->y;
}
double Ship::Projectile::gety()
{
	return this->y;
}
int Ship::Projectile::getx()
{
	return this->x;
}
void Ship::setx(int x)
{
	this->x = x;
}
void Ship::sety(int y)
{
	this->y = y;
}
void Ship::Projectile::sety(double y)
{
	this->y = y;
}
void Ship::Projectile::setx(int x)
{
	this->x = x;
}
void Player::setHp(int hp)
{
	this->hp = hp;
}
int Player::getHp()
{
	return this->hp;
}
void Player::setPoints(int points)
{
	this->points = points;
}
int Player::getPoints()
{
	return this->points;
}
void Ship::move(int x, int y)
{
	setx(getx() + x);
	sety(gety() + y);
}
void Ship::setpos(int x, int y)
{
	setx(x);
	sety(y);
}
Ship::Projectile* Ship::shoot()
{
	Player::Projectile *p = new Player::Projectile();
	p->sety(this->gety() - 32);
	p->setx(this->getx());
	return p;
}


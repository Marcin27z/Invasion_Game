#include "ship.h"
double Ship::getx()
{
	return this->x;
}
double Ship::gety()
{
	return this->y;
}
Ship::Projectile::Projectile(double x, double y)
{
	this->setx(x);
	this->sety(y);
}
double Ship::Projectile::gety()
{
	return this->y;
}
double Ship::Projectile::getx()
{
	return this->x;
}
void Ship::setx(double x)
{
	this->x = x;
}
void Ship::sety(double y)
{
	this->y = y;
}
void Ship::Projectile::sety(double y)
{
	this->y = y;
}
void Ship::Projectile::setx(double x)
{
	this->x = x;
}
void Ship::Projectile::move(double y, double x)
{
	this->x += x;
	this->y += y;
}
void Player::setHp(int hp)
{
	this->hp = hp;
}
int Player::getHp()
{
	return this->hp;
}
void Player::setPlayerProjectile(int p)
{
	this->playerProjectile = p;
}
int Player::getPlayerProjectile()
{
	return this->playerProjectile;
}
void Player::addHp()
{
	this->setHp(this->getHp() + 1);
}
void Player::takeHp()
{
	this->setHp(this->getHp() - 1);
}
void Player::setPoints(int points)
{
	this->points = points;
}
int Player::getPoints()
{
	return this->points;
}
void Player::addPoints(int p)
{
	this->setPoints(this->getPoints() + p);
}
void Ship::move(double x, double y)
{
	setx(getx() + x);
	sety(gety() + y);
}
void Ship::setPos(double x, double y)
{
	setx(x);
	sety(y);
}
Enemy::Enemy(double x, double y, double rotation, double slope)
{
	this->setx(x);
	this->sety(y);
	this->setRotation(rotation);
	this->setSlope(slope);
}
Enemy1::Enemy1(double x, double y, double rotation, double slope)
	:Enemy(x, y, rotation, slope)
{

}
Enemy2::Enemy2(double x, double y, double rotation, double slope)
	:Enemy(x, y, rotation, slope)
{

}
Enemy3::Enemy3(double x, double y, double rotation, double slope)
	: Enemy(x, y, rotation, slope)
{
}
void Enemy::setRotation(double rotation)
{
	this->rotation = rotation;
}
double Enemy::getRotation()
{
	return this->rotation;
}
void Enemy::setSlope(double slope)
{
	this->slope = slope;
}
double Enemy::getSlope()
{
	return this->slope;
}
Ship::Projectile* Ship::shoot(int offset)
{
	Player::Projectile *p = new Player::Projectile(this->getx(), this->gety() - offset);
	//p->sety(this->gety() - offset);
	//p->setx(this->getx());
	return p;
}


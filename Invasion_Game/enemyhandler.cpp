#include"enemyhandler.h"
EnemyHandler::EnemyHandler()
{
	for (int i = 0; i < ENEMY; i++)
	{
		eOffsetX[i] = 0;
		edx[i] = 1;
		enemy[i] = NULL;
	}
	for (int i = 0; i < EPROJ; i++)
	{
		enemyProj[i] = NULL;
		enemyProjDiagonalLeft[i] = NULL;
		enemyProjDiagonalRight[i] = NULL;
	}
}
void EnemyHandler::destroyProj(Ship::Projectile **proj)
{
	delete(*proj);
	*proj = NULL;
}
void EnemyHandler::destroyAllProjs()
{
	for (int i = 0; i < EPROJ; i++)
	{
		if (enemyProj[i] != NULL) destroyProj(&enemyProj[i]);
		if (enemyProjDiagonalLeft[i] != NULL) destroyProj(&enemyProjDiagonalLeft[i]);
		if (enemyProjDiagonalRight[i] != NULL) destroyProj(&enemyProjDiagonalRight[i]);
	}
}
void EnemyHandler::enemyGen()
{
	int count = 0;
	int randx;
	int randy;
	const int enemyRadius = 24;
	enemyGenTime = enemyGenClock.getElapsedTime();
	if (enemyGenTime.asSeconds() > 1)
	{
		if (rand() % 10 > 6)
		{
			while (count != ENEMY)
			{
				randx = rand() % 900 + 30;
				randy = rand() % 200 + 40;
				for (int j = 0; j < ENEMY; j++)
				{
					if (enemy[j] != NULL)
					{
						if (abs(randx - enemy[j]->getx()) < 2 * enemyRadius && abs(randy - enemy[j]->gety()) < 2 * enemyRadius)
						{
							count = 0;
							break;

						}
					}
					if (enemy2[j] != NULL)
					{
						if (abs(randx - enemy2[j]->getx()) < 2 * enemyRadius && abs(randy - enemy2[j]->gety()) < 2 * enemyRadius)
						{
							count = 0;
							break;

						}
					}
					if (enemy3[j] != NULL)
					{
						if (abs(randx - enemy3[j]->getx()) < 2 * enemyRadius && abs(randy - enemy3[j]->gety()) < 2 * enemyRadius)
						{
							count = 0;
							break;

						}
					}
					count++;
				}
			}
			int type;
			type = rand() % 3;
			if (type == 0)
			{
				for (int i = 0; i < ENEMY; i++)
				{
					if (enemy[i] == NULL)
					{
						enemy[i] = new Enemy(randx, randy);
						break;
					}
				}
				
			}
			if (type == 0)
			{
				for (int i = 0; i < ENEMY; i++)
				{
					if (enemy2[i] == NULL)
					{
						enemy2[i] = new Enemy2(randx, randy);
						break;
					}
				}

			}
			if (type == 0)
			{
				for (int i = 0; i < ENEMY; i++)
				{
					if (enemy3[i] == NULL)
					{
						enemy3[i] = new Enemy3(randx, randy);
						break;
					}
				}

			}

			
			count = 0;
		}
	enemyGenClock.restart();
	}
}
void EnemyHandler::enemyCharge(Player *player)
{
	double slope;
	int e;
	int l = 0;
	enemyChargeTime = enemyChargeClock.getElapsedTime();
	if (enemyChargeTime.asSeconds() > 3)
	{
		if (rand() % 10 > 6)
		{
			while (l < 20)
			{
				e = rand() % 10;
				if (enemy[e] != NULL)
				{

					slope = (double(enemy[e]->getx() - player->getx()) / double(enemy[e]->gety() - player->gety()));
					enemy[e]->setRotation(180 - atan(slope)* (180.0 / 3.14));
					enemy[e]->setSlope(slope);
					break;
				}
				l++;
			}
		}
		l = 0;
		enemyChargeClock.restart();
	}
}
void EnemyHandler::enemyUpdate(Player *player)
{
	const int playerHitRadius = 28;
	enemyT = enemyC.getElapsedTime();
	if (enemyT.asMilliseconds() > 5)
	{
		//move enemy
		for (int i = 0; i < ENEMY; i++)
		{
			if (enemy[i] != NULL)
			{
				//double radius = 100;
				//static double angle = 0;
				if (enemy[i]->getSlope() != 0) enemy[i]->move(enemy[i]->getSlope() *1.5, 1.5);
				else enemy[i]->move(edx[i] * 1, 0);
				//else enemy[i]->setPos(200 + (radius * cos(angle * 3.1415 / 180)), 200 + (radius * sin(angle * 3.14 / 180)));
				//angle = angle + 1;
				eOffsetX[i] += edx[i];
				if (((eOffsetX[i] == 100) || (eOffsetX[i] == -100) || (enemy[i]->getx() - MAX_LEFT < 2) || (enemy[i]->getx() - MAX_RIGHT > 2)) && (enemy[i]->getSlope() == 0.0)) edx[i] = edx[i] * -1;
				else
				{
					for (int j = 0; j < ENEMY; j++)
					{
						if (enemy[j] != NULL && enemy[j] != enemy[i])
						{
							if (abs(enemy[i]->getx() - enemy[j]->getx()) < 64 && abs(enemy[i]->gety() - enemy[j]->gety()) < 64)
							{
								edx[i] = edx[i] * -1;
								break;
							}
						}
					}
				}
				if (enemy[i]->gety() - 400 > 0 && enemy[i]->gety() - 400 < 2)
				{
					for (int j = 0; j < EPROJ; j++)
					{
						if (enemyProjDiagonalLeft[j] == NULL && enemyProjDiagonalLeft[j] == NULL && enemyProj[j] == NULL)
						{
							enemyProjDiagonalLeft[j] = enemy[i]->shoot(100);
							enemyProjDiagonalRight[j] = enemy[i]->shoot(100);
							enemyProj[j] = enemy[i]->shoot(100);
							break;
						}
					}
				}
				if (enemy[i]->gety() - 760 > 2)
				{
					delete(enemy[i]);
					enemy[i] = NULL;
				}
				else if (sqrt(pow(enemy[i]->gety() - player->gety(), 2) + pow(enemy[i]->getx() - player->getx(), 2)) < playerHitRadius)
				{
					delete(enemy[i]);
					enemy[i] = NULL;
					player->takeHp();
				}
			}
		}
		enemyC.restart();
	}
}
void EnemyHandler::enemyProjUpdate(Player *player)
{
	const int playerHitRadius = 32;
	enemyProjTime = enemyProjClock.getElapsedTime();
	if (enemyProjTime.asMilliseconds() > 1)
	{
		for (int i = 0; i < EPROJ; i++)
		{
			if (enemyProjDiagonalLeft[i] != NULL)
			{
				enemyProjDiagonalLeft[i]->move(1, -1);
				if (sqrt(pow(enemyProjDiagonalLeft[i]->gety() - player->gety(), 2) + pow(enemyProjDiagonalLeft[i]->getx() - player->getx(), 2)) < playerHitRadius)
				{
					destroyProj(&enemyProjDiagonalLeft[i]);
					player->takeHp();
				}
				else if (abs(enemyProjDiagonalLeft[i]->gety() - 768) < 1)
				{
					destroyProj(&enemyProjDiagonalLeft[i]);
				}
			}
			if (enemyProjDiagonalRight[i] != NULL)
			{
				enemyProjDiagonalRight[i]->move(1, 1);
				if (sqrt(pow(enemyProjDiagonalRight[i]->gety() - player->gety(), 2) + pow(enemyProjDiagonalRight[i]->getx() - player->getx(), 2)) < playerHitRadius)
				{
					destroyProj(&enemyProjDiagonalRight[i]);
					player->takeHp();
				}
				else if (abs(enemyProjDiagonalRight[i]->gety() - 768) < 1)
				{
					destroyProj(&enemyProjDiagonalRight[i]);
				}
			}
			if (enemyProj[i] != NULL)
			{
				enemyProj[i]->move(1);
				if (sqrt(pow(enemyProj[i]->gety() - player->gety(), 2) + pow(enemyProj[i]->getx() - player->getx(), 2)) < playerHitRadius)
				{
					destroyProj(&enemyProj[i]);
					player->takeHp();
				}
				else if (abs(enemyProj[i]->gety() - 768) < 1)
				{
					destroyProj(&enemyProj[i]);
				}

			}
			enemyProjClock.restart();
		}
	}
}
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include "render.h"
#define MAX_LEFT 38
#define MAX_RIGHT 988
#define MAX_UP 0
#define MAX_DOWN 660
#define PLAYER_DEF_X 512
#define PLAYER_DEF_Y 640
Player player;
Enemy *enemy[10];
Player::Projectile *proj[PPROJ];
Enemy::Projectile *enemyProj[EPROJ];
Enemy::Projectile *enemyProjDiagonalLeft[EPROJ];
Enemy::Projectile *enemyProjDiagonalRight[EPROJ];
int speedx;
int opt;
bool game;
int main()
{
	time_t t;
	srand(time(&t));
	// init player hp
	player.setHp(3);
	// init keyboard bools
	bool spacePressed = false;
	bool downPressed = false;
	bool upPressed = false;
	// create window and disactive
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Invasion!!!");
	window.setActive(false);
	// start render thread
	sf::Thread thread(&renderingThread, &window);
	thread.launch();
	// launch menu loop
	int optMax = 2;
	while (window.isOpen())
	{
		sf::Event event;
		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !downPressed)
			{
				downPressed = true;
				if (opt < optMax - 1) opt++;
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				downPressed = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !upPressed)
			{
				upPressed = true;
				if (opt > 0) opt--;
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				upPressed = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				if (opt == 0)
				{
					game = true;
					break;
				}
				if (opt == 1) window.close();
			}
		}
	}
	//set player starting position
	//enemy[0] = new Enemy();
	//enemy[0]->setpos(100, 100);
	player.setPos(PLAYER_DEF_X, PLAYER_DEF_Y);
	// init clocks
	sf::Clock playerClock;
	sf::Time playerTime;
	sf::Clock enemyClock;
	sf::Time enemyTime;
	sf::Clock clock;
	sf::Time time;
	sf::Clock enemyGenClock;
	sf::Time enemyGenTime;
	sf::Clock enemyChargeClock;
	sf::Time enemyChargeTime;
	sf::Clock enemyC;
	sf::Time enemyT;
	//start game loop
	int x = 0;
	int edx[ENEMY];
	int eOffsetX[ENEMY];
	for (int i = 0; i < ENEMY; i++)
	{
		edx[i] = 1;
		eOffsetX[i] = 0;
	}
	int dy;
	int e;
	int l;
	double slope;
	int randx;
	int randy;
	int count = 0;
	sf::Event event;
	while (window.isOpen())
	{
		enemyGenTime = enemyGenClock.getElapsedTime();
		enemyChargeTime = enemyChargeClock.getElapsedTime();
		enemyT = enemyC.getElapsedTime();
		if (enemyGenTime.asSeconds() > 1)
		{
			if (rand() % 10 > 6)
			{
				for (int i = 0; i < ENEMY; i++)
				{
					if (enemy[i] == NULL)
					{
						while (count != ENEMY)
						{
							randx = rand() % 900 + 30;
							randy = rand() % 200 + 40;
							for (int j = 0; j < ENEMY; j++)
							{
								if (enemy[j] != NULL)
								{
									if (abs(randx - enemy[j]->getx()) < 64 && abs(randy - enemy[j]->gety()) < 64)
									{
										count = 0;
										break;
										
									}
								}
								count++;
							}
						}
						enemy[i] = new Enemy(randx, randy);
						count = 0;
						break;
					}
				}
			}
			enemyGenClock.restart();
		}
		if (enemyChargeTime.asSeconds() > 3)
		{
			if (rand() % 10 > 6)
			{
				while (l < 20)
				{
					e = rand() % 10;
					if (enemy[e] != NULL)
					{
						slope = (double(enemy[e]->getx() - player.getx()) / double(enemy[e]->gety() - player.gety()));
						//remainder(slope, 2.0 * 3.14);
						std::cout << "Rotate " << e << " enemy " << atan(slope) * (180.0 / 3.14) << std::endl;
						std::cout << enemy[e]->getx() << " " << player.getx() << " " << enemy[e]->gety() << " " << player.gety() << " " << slope << std::endl;
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
		playerTime = playerClock.getElapsedTime();
		enemyTime = enemyClock.getElapsedTime();
		time = clock.getElapsedTime();
		//handle keyboards events
		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				x = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				x = -1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !spacePressed)
			{
				for (int i = 0; i < PPROJ; i++)
				{
					if (proj[i] == NULL)
					{
						proj[i] = player.shoot(-32);
						//enemyProj[i] = enemy[0]->shoot();///////////////////////////
						//enemyProjDiagonalLeft[i] = enemy[0]->shoot();
						//enemyProjDiagonalRight[i] = enemy[0]->shoot();
						break;
					}
				}
				spacePressed = true;
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) spacePressed = false;
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) x = 0;
			
		}
		if (time.asMilliseconds() > 1)
		{
			//move player
			if(x == 1 && player.getx() < MAX_RIGHT) player.move(1, 0);
			if(x == -1 && player.getx() > MAX_LEFT) player.move(-1, 0);
			
			clock.restart();
		}
		if (enemyT.asMilliseconds() > 5)
		{
			//move enemy
			for (int i = 0; i < ENEMY; i++)
			{
				if (enemy[i] != NULL)
				{
					if (enemy[i]->getSlope() != 0) enemy[i]->move(enemy[i]->getSlope() *1.5, 1.5);
					else enemy[i]->move(edx[i] * 1, 0);
					eOffsetX[i] += edx[i];
					if (((eOffsetX[i] == 100) || (eOffsetX [i]== -100) || (enemy[i]->getx() - MAX_LEFT < 2) || (enemy[i]->getx() - MAX_RIGHT > 2)) && (enemy[i]->getSlope() == 0.0)) edx[i] = edx[i] * -1;
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
					if (enemy[i]->gety() - 760 > 1)
					{
						delete(enemy[i]);
						enemy[i] = NULL;
					}
					else if (enemy[i]->gety() - player.gety() > 10 && enemy[i]->getx() - player.getx() < 32 && enemy[i]->getx() - player.getx() > -32)
					{
						delete(enemy[i]);
						enemy[i] = NULL;
						if (player.getHp() != 0) player.setHp(player.getHp() - 1);
					}
				}
			}
			enemyC.restart();
		}
		if (playerTime.asMilliseconds() > 1)
		{
			// move player's projectiles
			for (int i = 0; i < PPROJ; i++)
			{
				if (proj[i] != NULL)
				{

					proj[i]->sety(proj[i]->gety() - 2);
					


					for (int j = 0; j < ENEMY; j++)
					{
						if (enemy[j] != NULL)
							if (proj[i]->gety() - enemy[j]->gety() < 16 && (proj[i]->getx() > enemy[j]->getx() - 32 && (proj[i]->getx() < enemy[j]->getx() + 32)))
							{
								delete(proj[i]);
								proj[i] = NULL;
								delete(enemy[j]);
								enemy[j] = NULL;
								player.setPoints(player.getPoints() + 10);
								if (player.getPoints() % 300 == 0 && player.getHp() < MAX_HP) player.setHp(player.getHp() + 1);
								break;
							}
					}
					if (proj[i] != NULL && proj[i]->gety() == 0)
					{
						delete(proj[i]);
						proj[i] = NULL;
					}
				}

			}
			playerClock.restart();
		}
		// move enemy's projectiles
		for (int i = 0; i < EPROJ; i++)
		{
			if (enemyTime.asMilliseconds() > 1)
			{
				if (enemyProjDiagonalLeft[i] != NULL)
				{
					enemyProjDiagonalLeft[i]->setx(enemyProjDiagonalLeft[i]->getx() - 1);
					enemyProjDiagonalLeft[i]->sety(enemyProjDiagonalLeft[i]->gety() + 1);
					if (enemyProjDiagonalLeft[i]->gety() == (player.gety() + 64) && (enemyProjDiagonalLeft[i]->getx() > player.getx() - 64 && (enemyProjDiagonalLeft[i]->getx() < player.getx() + 64)))
					{
						delete(enemyProjDiagonalLeft[i]);
						enemyProjDiagonalLeft[i] = NULL;
						if (player.getHp() != 0) player.setHp(player.getHp() - 1);
					}
					else if (enemyProjDiagonalLeft[i]->gety() == 768)
					{
						delete(enemyProjDiagonalLeft[i]);
						enemyProjDiagonalLeft[i] = NULL;
					}
				}
				if (enemyProjDiagonalRight[i] != NULL)
				{
					enemyProjDiagonalRight[i]->setx(enemyProjDiagonalRight[i]->getx() + 1);
					enemyProjDiagonalRight[i]->sety(enemyProjDiagonalRight[i]->gety() + 1);
					if (enemyProjDiagonalRight[i]->gety() == (player.gety() + 64) && (enemyProjDiagonalRight[i]->getx() > player.getx() - 32 && (enemyProjDiagonalRight[i]->getx() < player.getx() + 32)))
					{
						delete(enemyProjDiagonalRight[i]);
						enemyProjDiagonalRight[i] = NULL;
						if (player.getHp() != 0) player.setHp(player.getHp() - 1);
					}
					else if (enemyProjDiagonalRight[i]->gety() == 768)
					{
						delete(enemyProjDiagonalRight[i]);
						enemyProjDiagonalRight[i] = NULL;
					}
				}
				if (enemyProj[i] != NULL)
				{
					enemyProj[i]->sety(enemyProj[i]->gety() + 1);
					if (enemyProj[i]->gety() == (player.gety() +32) && (enemyProj[i]->getx() > player.getx() - 32 && (enemyProj[i]->getx() < player.getx() + 32)))
					{
						delete(enemyProj[i]);
						enemyProj[i] = NULL;
						if (player.getHp() != 0) player.setHp(player.getHp() - 1);
					}
					else if (enemyProj[i]->gety() == 768)
					{
						delete(enemyProj[i]);
						enemyProj[i] = NULL;
					}

				}
				enemyClock.restart();	
			}

		}
		if (player.getHp() == 0)
		{
			game = false;
			for (int i = 0; i < EPROJ; i++)
			{
				if (enemyProj[i] != NULL)
				{
					delete(enemyProj[i]);
					enemyProj[i] = NULL;
				}
				if (enemyProjDiagonalLeft[i] != NULL)
				{
					delete(enemyProjDiagonalLeft[i]);
					enemyProjDiagonalLeft[i] = NULL;
				}
				if (enemyProjDiagonalRight[i] != NULL)
				{
					delete(enemyProjDiagonalRight[i]);
					enemyProjDiagonalRight[i] = NULL;
				}
			}
			for (int i = 0; i < PPROJ; i++)
			{
				if (proj[i] != NULL)
				{
					delete(proj[i]);
					proj[i] = NULL;
				}
			}
			for (int i = 0; i < 10; i++)
			{
				if (enemy[i] != NULL)
				{
					delete(enemy[i]);
					enemy[i] = NULL;
				}
			}
			for (int i = 0; i < ENEMY; i++)
			{
				edx[i] = 1;
				eOffsetX[i] = 0;
			}
			while (window.isOpen())
			{
				sf::Event event;
				if (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !downPressed)
					{
						downPressed = true;
						if (opt < optMax - 1) opt++;
					}
					if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					{
						downPressed = false;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !upPressed)
					{
						upPressed = true;
						if (opt > 0) opt--;
					}
					if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					{
						upPressed = false;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
					{
						if (opt == 0)
						{
							player.setHp(3);
							player.setPoints(0);
							player.setPos(PLAYER_DEF_X, PLAYER_DEF_Y);
							game = true;
							break;
						}
						if (opt == 1) window.close();
					}
				}
			}
		}

	}

	return 0;
}
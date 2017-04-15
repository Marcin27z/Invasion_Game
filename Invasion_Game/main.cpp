#include<iostream>
#include "render.h"
#define MAX_LEFT 38
#define MAX_RIGHT 988
#define MAX_UP 0
#define MAX_DOWN 660
Player player;
Enemy *enemy[10];
Player::Projectile *proj[PPROJ];
Enemy::Projectile *enemyProj[EPROJ];
Enemy::Projectile *enemyProjDiagonalLeft[EPROJ];
Enemy::Projectile *enemyProjDiagonalRight[EPROJ];
int speedx;
int main()
{
	player.setHp(3);
	bool spacePressed = false;
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Invasion!!!");
	window.setActive(false);
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);
	enemy[0] = new Enemy();
	enemy[0]->setpos(100, 100);
	player.setpos(517, 660);
	////////////////
	sf::Thread thread(&renderingThread, &window);
	thread.launch();
	////////////////////
	sf::Clock playerClock;
	sf::Time playerTime;
	sf::Clock enemyClock;
	sf::Time enemyTime;
	sf::Clock clock;
	sf::Time time;
	int x = 0;
	while (window.isOpen())
	{
		
		sf::Event event;
		playerTime = playerClock.getElapsedTime();
		enemyTime = enemyClock.getElapsedTime();
		time = clock.getElapsedTime();
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
						proj[i] = player.shoot();
						proj[i]->sety(proj[i]->gety() + 64);
						enemyProj[i] = enemy[0]->shoot();
						enemyProjDiagonalLeft[i] = enemy[0]->shoot();
						enemyProjDiagonalRight[i] = enemy[0]->shoot();
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
			if(x == 1 && player.getx() < MAX_RIGHT) player.move(1, 0);
			if(x == -1 && player.getx() > MAX_LEFT) player.move(-1, 0);
			clock.restart();
		}
		for (int i = 0; i < PPROJ; i++)
		{
			if (proj[i] != NULL)
			{
				if (playerTime.asMilliseconds() > 1)
				{
					proj[i]->sety(proj[i]->gety() - 1);
					playerClock.restart();
				}

				for (int j = 0; j < 10; j++)
				{
					if(enemy[j] != NULL)
						if (proj[i]->gety() == (enemy[j]->gety() - 64) && (proj[i]->getx() > enemy[j]->getx() - 32 && (proj[i]->getx() < enemy[j]->getx() + 32)))
						{
							delete(proj[i]);
							proj[i] = NULL;
							delete(enemy[j]);
							enemy[j] = NULL;
							player.setPoints(player.getPoints() + 10);
							break;
						}
				}
				if (proj[i]!= NULL && proj[i]->gety() == 0)
				{
					delete(proj[i]);
					proj[i] = NULL;
				}
			}
		
		}
		for (int i = 0; i < EPROJ; i++)
		{
			if (enemyTime.asMilliseconds() > 1)
			{
				if (enemyProjDiagonalLeft[i] != NULL)
				{
					enemyProjDiagonalLeft[i]->setx(enemyProjDiagonalLeft[i]->getx() - 1);
					enemyProjDiagonalLeft[i]->sety(enemyProjDiagonalLeft[i]->gety() + 1);
					if (enemyProjDiagonalLeft[i]->gety() == (player.gety() - 16) && (enemyProjDiagonalLeft[i]->getx() > player.getx() - 32 && (enemyProjDiagonalLeft[i]->getx() < player.getx() + 32)))
					{
						delete(enemyProjDiagonalLeft[i]);
						enemyProjDiagonalLeft[i] = NULL;
						if (player.getHp() != 1) player.setHp(player.getHp() - 1);
					}
					else if (enemyProjDiagonalLeft[i]->gety() == 0)
					{
						delete(enemyProjDiagonalLeft[i]);
						enemyProjDiagonalLeft[i] = NULL;
					}
				}
				if (enemyProjDiagonalRight[i] != NULL)
				{
					enemyProjDiagonalRight[i]->setx(enemyProjDiagonalRight[i]->getx() + 1);
					enemyProjDiagonalRight[i]->sety(enemyProjDiagonalRight[i]->gety() + 1);
					if (enemyProjDiagonalRight[i]->gety() == (player.gety() - 16) && (enemyProjDiagonalRight[i]->getx() > player.getx() - 32 && (enemyProjDiagonalRight[i]->getx() < player.getx() + 32)))
					{
						delete(enemyProjDiagonalRight[i]);
						enemyProjDiagonalRight[i] = NULL;
						if (player.getHp() != 1) player.setHp(player.getHp() - 1);
					}
					else if (enemyProjDiagonalRight[i]->gety() == 0)
					{
						delete(enemyProjDiagonalRight[i]);
						enemyProjDiagonalRight[i] = NULL;
					}
				}
				if (enemyProj[i] != NULL)
				{
					enemyProj[i]->sety(enemyProj[i]->gety() + 1);
					if (enemyProj[i]->gety() == (player.gety() - 16) && (enemyProj[i]->getx() > player.getx() - 32 && (enemyProj[i]->getx() < player.getx() + 32)))
					{
						delete(enemyProj[i]);
						enemyProj[i] = NULL;
						if (player.getHp() != 1) player.setHp(player.getHp() - 1);
					}
					else if (enemyProj[i]->gety() == 0)
					{
						delete(enemyProj[i]);
						enemyProj[i] = NULL;
					}

				}
				enemyClock.restart();	
			}

		}

	}

	return 0;
}
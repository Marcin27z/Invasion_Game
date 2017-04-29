#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<sstream>
#include "ship.h"
#include <SFML/Graphics.hpp>
#define MAX_LEFT 38
#define MAX_RIGHT 988
#define MAX_UP 0
#define MAX_DOWN 660
#define PLAYER_DEF_X 512
#define PLAYER_DEF_Y 640
void choice(sf::RenderWindow* window, int *opt, bool *game)
{
	const int optMax = 2;
	bool downPressed = false;
	bool upPressed = false;
	while (window->isOpen())
	{
		sf::Event event;
		if (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !downPressed)
			{
				downPressed = true;
				if (*opt < optMax - 1) *opt++;
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				downPressed = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !upPressed)
			{
				upPressed = true;
				if (*opt > 0) *opt--;
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				upPressed = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				if (*opt == 0)
				{
					*game = true;
					break;
				}
				if (*opt == 1) window->close();
			}
		}
	}
}
class PlayerHandler
{
public:
	Player player;
	sf::Clock clock;
	sf::Time time;
	sf::Clock playerClock;
	sf::Time playerTime;
	Ship::Projectile *proj[PPROJ];
	int y = 640;
	void destroyProj(Ship::Projectile **proj)
	{
		delete(*proj);
		*proj = NULL;
	}
	int getAction(sf::RenderWindow* window)
	{
		int x;
		sf::Event event;
		bool spacePressed = false;
		if (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
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
						break;
					}
				}
				spacePressed = true;
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) spacePressed = false;
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) x = 0;

		}
		return x;
	}
	void update(int x)
	{
		//playerTime = playerClock.getElapsedTime();
		//time = clock.getElapsedTime();
		//if (time.asMilliseconds() > 1)
		//{
			//move player
			if (x == 1 && player.getx() < MAX_RIGHT) player.move(10, 0);
			if (x == -1 && player.getx() > MAX_LEFT) player.move(-10, 0);
			//clock.restart();
		//}
	}
	void updateProj(Enemy *enemy[ENEMY])
	{
		if (playerTime.asMilliseconds() > 1)
		{
			// move player's projectiles
			for (int i = 0; i < PPROJ; i++)
			{
				if (proj[i] != NULL)
				{
					proj[i]->move(-20);
					for (int j = 0; j < ENEMY; j++)
					{
						if (enemy[j] != NULL)
							if (proj[i]->gety() - enemy[j]->gety() < 16 && (proj[i]->getx() > enemy[j]->getx() - 32 && (proj[i]->getx() < enemy[j]->getx() + 32)))
							{
								destroyProj(&proj[i]);
								delete(enemy[j]);
								enemy[j] = NULL;
								player.addPoints(10);
								if (player.getPoints() % 300 == 0 && player.getHp() < MAX_HP) player.addHp();
								break;
							}
					}
					if (proj[i] != NULL && proj[i]->gety() < 0)
					{
						delete(proj[i]);
						proj[i] = NULL;
					}
				}

			}
			playerClock.restart();
		}
	}
};
void destroyProj(Ship::Projectile **proj)
{
	delete(*proj);
	*proj = NULL;
}
/*void destroyAllProjs()
{
	for (int i = 0; i < EPROJ; i++)
	{
		if (enemyProj[i] != NULL) destroyProj(&enemyProj[i]);
		if (enemyProjDiagonalLeft[i] != NULL) destroyProj(&enemyProjDiagonalLeft[i]);
		if (enemyProjDiagonalRight[i] != NULL) destroyProj(&enemyProjDiagonalRight[i]);
	}
}*/
class EnemyHandler
{
public:
	Enemy *enemy[ENEMY];
	Ship::Projectile *enemyProj[EPROJ];
	Ship::Projectile *enemyProjDiagonalLeft[EPROJ];
	Ship::Projectile *enemyProjDiagonalRight[EPROJ];
	sf::Clock enemyGenClock;
	sf::Time enemyGenTime;
	sf::Clock enemyChargeClock;
	sf::Time enemyChargeTime;
	sf::Clock enemyC;
	sf::Time enemyT;
	sf::Clock enemyProjClock;
	sf::Time enemyProjTime;
	int eOffsetX[ENEMY];
	int edx[ENEMY];
	void init()
	{
		for (int i = 0; i < ENEMY; i++)
		{
			eOffsetX[i] = 0;
			edx[ENEMY] = 0;
		}
	}
	void destroyProj(Ship::Projectile **proj)
	{
		delete(*proj);
		*proj = NULL;
	}
	void destroyAllProjs()
	{
		for (int i = 0; i < EPROJ; i++)
		{
			if(enemyProj[i] != NULL) destroyProj(&enemyProj[i]);
			if(enemyProjDiagonalLeft[i] != NULL) destroyProj(&enemyProjDiagonalLeft[i]);
			if(enemyProjDiagonalRight[i] != NULL) destroyProj(&enemyProjDiagonalRight[i]);
		}
	}
	void enemyGen()
	{
		int count = 0;
		int randx;
		int randy;
		enemyGenTime = enemyGenClock.getElapsedTime();
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
	}
	void enemyCharge(Player *player)
	{
		int slope;
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
	void enemyUpdate(Player *player)
	{
		enemyT = enemyC.getElapsedTime();
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
					if (enemy[i]->gety() - 760 > 1)
					{
						delete(enemy[i]);
						enemy[i] = NULL;
					}
					else if (enemy[i]->gety() - player->gety() > 10 && enemy[i]->getx() - player->getx() < 32 && enemy[i]->getx() - player->getx() > -32)
					{
						delete(enemy[i]);
						enemy[i] = NULL;
						player->addHp();
					}
				}
			}
			enemyC.restart();
		}
	}
	void enemyProjUpdate(Player *player)
	{
		enemyProjTime = enemyProjClock.getElapsedTime();
		if (enemyProjTime.asMilliseconds() > 1)
		{
			for (int i = 0; i < EPROJ; i++)
			{
				if (enemyProjDiagonalLeft[i] != NULL)
				{
					enemyProjDiagonalLeft[i]->move(1, -1);
					if (enemyProjDiagonalLeft[i]->gety() == (player->gety() + 64) && (enemyProjDiagonalLeft[i]->getx() > player->getx() - 64 && (enemyProjDiagonalLeft[i]->getx() < player->getx() + 64)))
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
					if (enemyProjDiagonalRight[i]->gety() == (player->gety() + 64) && (enemyProjDiagonalRight[i]->getx() > player->getx() - 32 && (enemyProjDiagonalRight[i]->getx() < player->getx() + 32)))
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
					if (enemyProj[i]->gety() == (player->gety() + 32) && (enemyProj[i]->getx() > player->getx() - 32 && (enemyProj[i]->getx() < player->getx() + 32)))
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
};
std::string intToStr(int s)
{
	std::stringstream ss;
	ss << s;
	return ss.str();
}
class Render
{
public:
	sf::RenderWindow *window;
	PlayerHandler playerhandler;
	EnemyHandler enemyHandler;
	Player player;
	Enemy *enemy[ENEMY];
	Ship::Projectile *enemyProj[EPROJ];
	Ship::Projectile *enemyProjDiagonalLeft[EPROJ];
	Ship::Projectile *enemyProjDiagonalRight[EPROJ];
	Ship::Projectile *proj[PPROJ];
	int y = 640;
	int opt = 0;
	bool game = false;
	void center(sf::Text *text, int offsetY = 0, int offsetX = 0)
	{
		sf::FloatRect  TextRect = text->getLocalBounds();
		text->setOrigin(TextRect.left + TextRect.width / 2.0f, TextRect.top + TextRect.height / 2.0f);
		text->setPosition(sf::Vector2f((1024 / 2.0f) + offsetX, (768 / 2.0f) + offsetY));
	}
	
	void setColor(sf::Color *color, int r, int g, int b)
	{
		sf::Color col(r, g, b);
		color = &col;
	}
	void setTextBox(sf::Text *text, sf::Font *font, std::string s, int size, sf::Color color)
	{
		text->setFont(*font);
		text->setString(s);
		text->setCharacterSize(size);
		text->setFillColor(color);
	}
	void setSprite(sf::Sprite *sprite, sf::Texture *texture, int originX = 0, int originY = 0, int scaleX = 1, int scaleY = 1, int positionX = 0, int positionY = 0, int rotation = 0)
	{
		sprite->setTexture(*texture);
		sprite->setScale(scaleX, scaleY);
		sprite->setOrigin(originX, originY);
		sprite->setPosition(positionX, positionY);
		sprite->setRotation(rotation);
	}
	void run()
	{
		sf::Font font;
		font.loadFromFile("nasalization-rg.ttf");
		sf::Color color(65, 105, 255);
		sf::Color selectedColor(200, 100, 100);
		sf::Text menu;
		sf::Text play;
		sf::Text exit;
		setTextBox(&menu, &font, "MENU", 64, color);
		setTextBox(&play, &font, "Play", 32, color);
		setTextBox(&exit, &font, "Exit", 32, color);
		sf::Texture backgroundTexture;
		backgroundTexture.loadFromFile("Space.gif");
		sf::Sprite background;
		setSprite(&background, &backgroundTexture, 0, 0, 3, 3);
		center(&menu, -60);
		center(&play);
		center(&exit, 40);
		while (!game)
		{
			if (opt == 0) play.setFillColor(selectedColor);
			else  play.setFillColor(color);
			if (opt == 1) exit.setFillColor(selectedColor);
			else  exit.setFillColor(color);
			window->clear();
			window->draw(background);
			window->draw(menu);
			window->draw(play);
			window->draw(exit);
			window->display();
		}
		std::string points;
		sf::Text playAgain;
		sf::Text pointsText;
		sf::Text gameOverText;
		setTextBox(&playAgain, &font, "Play again", 32, color);
		setTextBox(&pointsText, &font, "Points:", 24, color);
		setTextBox(&gameOverText, &font, "game Over", 64, color);
		center(&playAgain, 100);
		center(&gameOverText, -60);
		center(&exit, 140);
		sf::Texture playerShipTexture;
		playerShipTexture.loadFromFile("Statek.png");
		sf::Texture projectileTexture;
		projectileTexture.loadFromFile("projectile.png");
		sf::Texture enemyShipTexture;
		enemyShipTexture.loadFromFile("Statek.png");
		sf::Sprite hpSprite[MAX_HP];
		for (int i = 0; i < MAX_HP; i++) setSprite(&hpSprite[i], &playerShipTexture, 8, 8, 1, 1, 10 + (32 * i), 740);
		sf::Sprite playerShip;
		setSprite(&playerShip, &playerShipTexture, 16, -16, 2, 2, playerhandler.player.getx(), playerhandler.player.gety());
		sf::Sprite enemyShip[ENEMY];
		for (int i = 0; i < ENEMY; i++) setSprite(&enemyShip[i], &enemyShipTexture, 16, 16, 2, 2, 0, 0, 180);
		sf::Sprite projectile[PPROJ];
		for (int i = 0; i < PPROJ; i++) setSprite(&projectile[i], &projectileTexture, 8, -8);
		sf::Sprite enemyProjectile[EPROJ];
		sf::Sprite enemyProjectileDiagonalLeft[EPROJ];
		sf::Sprite enemyProjectileDiagonalRight[EPROJ];
		for (int i = 0; i < EPROJ; i++)
		{
			setSprite(&enemyProjectile[i], &projectileTexture, 8, -8);
			setSprite(&enemyProjectileDiagonalLeft[i], &projectileTexture, 8, 8, 1, 1, 0, 0, 45);
			setSprite(&enemyProjectileDiagonalRight[i], &projectileTexture, 8, -8, 1, 1, 0, 0, -45);
		}
		while (window->isOpen())
		{
			window->clear();
			window->draw(background);
			if (player.getHp() != 0) {
				playerShip.setPosition(player.getx(), y);
				for (int i = 0; i < PPROJ; i++)
				{
					if (playerhandler.proj[i] != NULL)
					{
						projectile[i].setPosition(playerhandler.proj[i]->getx(), playerhandler.proj[i]->gety());
						window->draw(projectile[i]);
					}
				}
				for (int i = 0; i < EPROJ; i++)
				{
					if (enemyHandler.enemyProj[i] != NULL)
					{
						enemyProjectile[i].setPosition(enemyHandler.enemyProj[i]->getx(), enemyHandler.enemyProj[i]->gety());
						window->draw(enemyProjectile[i]);
					}
				}
				for (int i = 0; i < EPROJ; i++)
				{
					if (enemyHandler.enemyProjDiagonalLeft[i] != NULL)
					{
						enemyProjectileDiagonalLeft[i].setPosition(enemyHandler.enemyProjDiagonalLeft[i]->getx(), enemyHandler.enemyProjDiagonalLeft[i]->gety());
						window->draw(enemyProjectileDiagonalLeft[i]);
					}
				}
				for (int i = 0; i < EPROJ; i++)
				{
					if (enemyHandler.enemyProjDiagonalRight[i] != NULL)
					{
						enemyProjectileDiagonalRight[i].setPosition(enemyHandler.enemyProjDiagonalRight[i]->getx(), enemyHandler.enemyProjDiagonalRight[i]->gety());
						window->draw(enemyProjectileDiagonalRight[i]);
					}
				}
				for (int i = 0; i < ENEMY; i++)
				{
					if (enemyHandler.enemy[i] != NULL)
					{
						enemyShip[i].setRotation(enemyHandler.enemy[i]->getRotation());
						enemyShip[i].setPosition(enemyHandler.enemy[i]->getx(), enemyHandler.enemy[i]->gety());
						window->draw(enemyShip[i]);
					}
				}
				for (int i = 0; i < playerhandler.player.getHp(); i++)
				{
					window->draw(hpSprite[i]);
				}
				points = intToStr(playerhandler.player.getPoints());
				pointsText.setString("Points " + points);
				window->draw(playerShip);
			}
			else
			{
				pointsText.setCharacterSize(48);
				/*pointsTextRect = pointsText.getLocalBounds();
				pointsText.setOrigin(pointsTextRect.left + pointsTextRect.width / 2.0f, pointsTextRect.top + pointsTextRect.height / 2.0f);
				pointsText.setPosition(sf::Vector2f(1024 / 2.0f, (768 / 2.0f)));*/
				center(&pointsText);
				while (!game)
				{
					if (opt == 0) playAgain.setFillColor(selectedColor);
					else  playAgain.setFillColor(color);
					if (opt == 1) exit.setFillColor(selectedColor);
					else  exit.setFillColor(color);
					window->clear();
					window->draw(background);
					window->draw(gameOverText);
					window->draw(pointsText);
					window->draw(playAgain);
					window->draw(exit);
					window->display();
				}
				pointsText.setCharacterSize(24);
				pointsText.setOrigin(0, 0);
				pointsText.setPosition(0, 0);
			}
			window->draw(pointsText);
			window->display();
		}
	}
};
int main()
{
	time_t t;
	srand(time(&t));
	//create data class
	Render render;
	render.playerhandler.player.setHp(3);
	render.enemyHandler.init();
	// create window and disactive
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Invasion!!!");
	window.setActive(false);
	render.window = &window;
	// start render thread
	sf::Thread thread(&Render::run, &render);
	thread.launch();
	// launch menu loop
	choice(render.window, &render.opt, &render.game);
	//set player starting position
	//enemy[0] = new Enemy();
	//enemy[0]->setpos(100, 100);
	render.playerhandler.player.setPos(PLAYER_DEF_X, PLAYER_DEF_Y);
	// init clocks
	sf::Time gameTime;
	sf::Clock gameClock;
	
	while (window.isOpen())
	{
		gameTime = gameClock.getElapsedTime();
		if (gameTime.asMilliseconds() > 33)
		{
			render.enemyHandler.enemyGen();
			render.enemyHandler.enemyCharge(&render.playerhandler.player);
			render.playerhandler.update(render.playerhandler.getAction(render.window));
			render.enemyHandler.enemyUpdate(&render.playerhandler.player);
			render.enemyHandler.enemyProjUpdate(&render.playerhandler.player);
			render.playerhandler.updateProj(render.enemyHandler.enemy);
			gameClock.restart();
		}
		
		if (render.playerhandler.player.getHp() == 0)
		{
			render.game = false;
			render.enemyHandler.destroyAllProjs();
			for (int i = 0; i < PPROJ; i++)
			{
				if (render.playerhandler.proj[i] != NULL)
				{
					delete(render.playerhandler.proj[i]);
					render.playerhandler.proj[i] = NULL;
				}
			}
			for (int i = 0; i < 10; i++)
			{
				if (render.enemyHandler.enemy[i] != NULL)
				{
					delete(render.enemyHandler.enemy[i]);
					render.enemyHandler.enemy[i] = NULL;
				}
			}
			for (int i = 0; i < ENEMY; i++)
			{
				render.enemyHandler.edx[i] = 1;
				render.enemyHandler.eOffsetX[i] = 0;
			}
			choice(render.window, &render.opt, &render.game);
		}

	}

	return 0;
}
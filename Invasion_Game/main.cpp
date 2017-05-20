#include "jsonhandler.h"
void jsonf()
{
	std::ofstream jsono("game1.json");
	int x = 200;
	int y = 200;
	json j = { {"x0",x},{"y0",y} };
	jsono << j;
	jsono.close();
	json data;
}
void json_load(Render* render)
{
	std::ifstream json_in("game1.json");
	json data;
	json_in >> data;
	std::string enemyx = "enemyx ";
	std::string enemyy = "enemyy ";
	std::string enemyRotation = "enemyRotation ";
	std::string enemySlope = "enemySlope ";
	std::string enemyType = "enemyType ";
	for (int i = 0; i < 10; i++)
	{
		enemyx[enemyx.size() - 1] = char(i + 48);
		enemyy[enemyy.size() - 1] = char(i + 48);
		enemyRotation[enemyRotation.size() - 1] = char(i + 48);
		enemySlope[enemySlope.size() - 1] = char(i + 48);
		enemyType[enemyType.size() - 1] = char(i + 48);
		if (data.find(enemyx) != data.end() && data.find(enemyy) != data.end() && data.find(enemyRotation) != data.end() && data.find(enemySlope) != data.end()
			&& data.find(enemyType) != data.end()) render->enemyHandler.enemy[0] =
			new Enemy(data.at(enemyx).get<int>(), data.at(enemyy).get<int>(), data.at(enemyRotation).get<int>(), data.at(enemySlope).get<int>());;
	}
	json_in.close();
}
void save(sf::RenderWindow* window, bool *game)
{
	std::cout << "save";
	*game = true;
}
void load(sf::RenderWindow* window, bool *game)
{
	std::cout << "load";
	*game = true;
}
void exit(sf::RenderWindow* window, bool *game)
{
	window->close();
}
void play(sf::RenderWindow* window, bool *game)
{
	*game = true;
}
void loadLevel(sf::RenderWindow* window, bool *game)
{
	std::cout << "load level";
	*game = true;
}
void choice(sf::RenderWindow* window, int optMax, int *opt, bool *game, void(*f1)(sf::RenderWindow*, bool *) = NULL, void(*f2)(sf::RenderWindow*, bool *) = NULL, void(*f3)(sf::RenderWindow*, bool *) = NULL, void(*f4)(sf::RenderWindow*, bool *) = NULL)
{
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
				if (*opt < optMax - 1) *opt += 1;
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				downPressed = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !upPressed)
			{
				upPressed = true;
				if (*opt > 0) *opt -= 1;
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				upPressed = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				if (*opt == 0)
				{
					//*game = true;
					f1(window, game);
				}
				if (*opt == 1)
				{
					f2(window, game);
				}
				if (*opt == 2)
				{
					f3(window, game);
				}
				if (*opt == 3)
				{
					f4(window, game);
				}
				*opt = 0;
				break;
			}
		}
	}
}
int main()
{
	jsonf();
	time_t t;
	srand(time(&t));
	const int player_def_x = 512;
	const int player_def_y = 640;
	//create data class
	Render render;
	json_load(&render);
	render.playerhandler.player.setHp(3);
	render.playerhandler.player.setPlayerProjectile(2);
	// create window and disactive
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Invasion!!!");
	window.setActive(false);
	render.window = &window;
	// start render thread
	sf::Thread thread(&Render::run, &render);
	thread.launch();
	// launch menu loop
	choice(render.window, 3, &render.opt, &render.game, &play, &load, &exit);
	//set player starting position
	render.playerhandler.player.setPos(player_def_x, player_def_y);
	// init clocks
	sf::Time gameTime;
	sf::Clock gameClock;
	
	while (window.isOpen())
	{
		gameTime = gameClock.getElapsedTime();
		if (gameTime.asMilliseconds() > 1)
		{
			render.enemyHandler.enemyGen(); //generate enemy
			render.enemyHandler.enemyCharge(&render.playerhandler.player); //make enemy charge at player
			render.playerhandler.update(render.playerhandler.getAction(render.window), &render.playerhandler.powerUpHandler); //update player position
			render.enemyHandler.enemyUpdate(&render.playerhandler.player); //update enemy position
			render.enemyHandler.enemyProjUpdate(&render.playerhandler.player); //update enemys' projectiles
			render.playerhandler.updateProj(render.enemyHandler.enemy); //update players projectiles
			render.playerhandler.powerUpHandler.updatePowerUp();
			render.playerhandler.powerUpHandler.powerUpEffectUpdate(&render.playerhandler.player);
			gameClock.restart();
		}
		
		if (render.playerhandler.player.getHp() == 0)
		{
			render.game = false;
			render.enemyHandler.destroyAllProjs();
			for (int i = 0; i < 5; i++)
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
			choice(render.window, 2, &render.opt, &render.game, &play, &exit);
			if (render.game)
			{
				render.playerhandler.player.setHp(3);
				render.playerhandler.player.setPoints(0);
				render.playerhandler.player.setPos(player_def_x, player_def_y);
			}
		}
		if (!render.playerhandler.nopause)
		{
			choice(render.window, 4, &render.opt, &render.playerhandler.nopause, &play, &save, &load, &exit);
		}

	}

	return 0;
}
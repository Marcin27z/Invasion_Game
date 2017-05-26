#include "jsonhandler.h"
void jsonf()
{
	std::ofstream jsono("game.json");
	int x = 200;
	int y = 200;
	/*json j = { {"enemyx0",x},{"enemyy0",y},{"enemyRotation0",180},{"enemySlope0",0}, {"enemyType0", 0},
				{ "enemyx1",x + 100 },{ "enemyy1",y + 100 },{ "enemyRotation1",180 },{ "enemySlope1",0 },{ "enemyType1", 0 },
					{ "enemyx2",x + 150 },{ "enemyy2",y + 200 },{ "enemyRotation2",180 },{ "enemySlope2",0 },{ "enemyType2", 0 } ,
					{ "enemyx3",x + 200 },{ "enemyy3",y + 100 },{ "enemyRotation3",180 },{ "enemySlope3",0 },{ "enemyType3", 0  },
					{ "enemyx4",x + 250 },{ "enemyy4",y + 200 },{ "enemyRotation4",180 },{ "enemySlope4",0 },{ "enemyType4", 0 }  };*/
	json j;
	j["enemy"] = { {"id", 1},{"x", 100},{"y", 100} };
	jsono << j;
	jsono.close();
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
void save(Render &render, JsonHandler &jsonHandler)
{
	std::cout << "save";
	jsonHandler.save(render);
	render.game = true;
}
void load(Render &render, JsonHandler &jsonHandler)
{
	std::cout << "load";
	jsonHandler.load(render);
	render.game = true;
}
void exit(Render &render, JsonHandler &jsonHandler)
{
	render.window->close();
}
void play(Render &render, JsonHandler &jsonHandler)
{
	render.game = true;
}
void unpause(Render &render, JsonHandler &jsonHandler)
{
	render.playerhandler.nopause = true;
}
void loadLevel(Render &render, JsonHandler &jsonHandler)
{
	std::cout << "load level";
	jsonHandler.loadLevel(render);
	render.game = true;
}
void choice(Render &render, JsonHandler &jsonHandler, int optMax, void(*f1)(Render &, JsonHandler &) = NULL, void(*f2)(Render &, JsonHandler &) = NULL,
	void(*f3)(Render &, JsonHandler &) = NULL, void(*f4)(Render &, JsonHandler &) = NULL)
{
	bool downPressed = false;
	bool upPressed = false;
	while (render.window->isOpen())
	{
		sf::Event event;
		if (render.window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				render.window->close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !downPressed)
			{
				downPressed = true;
				if (render.opt < optMax - 1) render.opt += 1;
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				downPressed = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !upPressed)
			{
				upPressed = true;
				if (render.opt > 0) render.opt -= 1;
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				upPressed = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				if (render.opt == 0)
				{
					//*game = true;
					f1(render, jsonHandler);
				}
				if (render.opt == 1)
				{
					f2(render, jsonHandler);
				}
				if (render.opt == 2)
				{
					f3(render, jsonHandler);
				}
				if (render.opt == 3)
				{
					f4(render, jsonHandler);
				}
				render.opt = 0;
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
	JsonHandler jsonHandler;
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
	//set player starting position
	render.playerhandler.player.setPos(player_def_x, player_def_y);
	// launch menu loop
	choice(render, jsonHandler, 4, &play, &load, &loadLevel, &exit);
	
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
			render.playerhandler.powerUpHandler.updatePowerUp(); //update state of powerup
			render.playerhandler.powerUpHandler.powerUpEffectUpdate(&render.playerhandler.player); //update effect of powerup
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
			for (int i = 0; i < 3; i++)
			{
				if (render.playerhandler.powerUpHandler.powerUp[i] != NULL)
				{
					delete(render.playerhandler.powerUpHandler.powerUp[i]);
					render.playerhandler.powerUpHandler.powerUp[i] == NULL;
					render.playerhandler.powerUpHandler.disactivate(i);
				}
			}
			choice(render, jsonHandler, 2, &play, &exit);
			if (render.game)
			{
				render.playerhandler.player.setHp(3);
				render.playerhandler.player.setPoints(0);
				render.playerhandler.player.setPos(player_def_x, player_def_y);
			}
		}
		if (!render.playerhandler.nopause)
		{
			choice(render, jsonHandler, 4, &unpause, &save, &load, &exit);
		}

	}

	return 0;
}
#include "render.h"
void choice(sf::RenderWindow* window, int *opt, bool *game)
{
	int optMax = 2;
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
					*game = true;
					break;
				}
				if (*opt == 1) window->close();
			}
		}
	}
}
int main()
{
	time_t t;
	srand(time(&t));
	const int player_def_x = 512;
	const int player_def_y = 640;
	//create data class
	Render render;
	render.playerhandler.player.setHp(3);
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
			render.playerhandler.update(render.playerhandler.getAction(render.window)); //update player position
			render.enemyHandler.enemyUpdate(&render.playerhandler.player); //update enemy position
			render.enemyHandler.enemyProjUpdate(&render.playerhandler.player); //update enemys' projectiles
			render.playerhandler.updateProj(render.enemyHandler.enemy); //update players projectiles
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
			if (render.game)
			{
				render.playerhandler.player.setHp(3);
				render.playerhandler.player.setPoints(0);
				render.playerhandler.player.setPos(player_def_x, player_def_y);
			}
		}

	}

	return 0;
}
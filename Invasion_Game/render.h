#ifndef __RENDER_H__
#define __RENDER_H__

#include "playerhandler.h"
#include "enemyhandler.h"

#include<iostream>
#include<ctime>
#include<sstream>
#include <SFML/Graphics.hpp>
class Render
{
public:
	sf::Font font;
	std::string intToStr(int);
	sf::RenderWindow *window;
	PlayerHandler playerhandler;
	EnemyHandler enemyHandler;
	Render();
	int y;
	int opt;
	bool game;
	void center(sf::Text *, int = 0, int = 0);
	void setColor(sf::Color *, int , int , int );
	void setTextBox(sf::Text *, sf::Font *, std::string, int, sf::Color);
	void setSprite(sf::Sprite *, sf::Texture *, int = 0, int = 0, int = 1, int = 1, int = 0, int = 0, int = 0);
	void run();
};

#endif
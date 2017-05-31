#ifndef __JSONHANDLER_H__
#define __JSONHANDLER_H__

#include "jsonhandler.h"
void JsonHandler::load(Render& render, std::string name)
{
	std::ifstream json_in;
	try {
		json_in.open(name);
	}
	catch (const std::ifstream::failure& e)
	{
		return;
	}
	int j = 0;
	while (json_in)
	{
		try {
			json_in >> data;
		}
		catch(json::parse_error &e){
			break;
		}
		std::cout << j << data << "\n";
		j++;
		for (int i = 0; i < 10; i++)
		{
			enemyx[enemyx.size() - 1] = char(i + 48);
			enemyy[enemyy.size() - 1] = char(i + 48);
			enemyRotation[enemyRotation.size() - 1] = char(i + 48);
			enemySlope[enemySlope.size() - 1] = char(i + 48);
			enemyType[enemyType.size() - 1] = char(i + 48);
			enemySpeedx[enemySpeedx.size() - 1] = char(i + 48);
			if (data.find(enemyx) != data.end() && data.find(enemyy) != data.end() && data.find(enemyRotation) != data.end() && data.find(enemySlope) != data.end()
				&& data.find(enemyType) != data.end() && data.find(enemySpeedx) != data.end())
			{
				if (data.at(enemyType).get<int>() == 1)
					render.enemyHandler.enemy[i] =
					new Enemy1(data.at(enemyx).get<double>(), data.at(enemyy).get<double>(), data.at(enemySpeedx).get<double>(), data.at(enemyRotation).get<double>(), data.at(enemySlope).get<double>());
				else if (data.at(enemyType).get<int>() == 2)
					render.enemyHandler.enemy[i] =
					new Enemy2(data.at(enemyx).get<double>(), data.at(enemyy).get<double>(), data.at(enemySpeedx).get<double>(), data.at(enemyRotation).get<double>(), data.at(enemySlope).get<double>());
				else if (data.at(enemyType).get<int>() == 3)
					render.enemyHandler.enemy[i] =
					new Enemy3(data.at(enemyx).get<double>(), data.at(enemyy).get<double>(), data.at(enemySpeedx).get<double>(), data.at(enemyRotation).get<double>(), data.at(enemySlope).get<double>());
			}
		}
		for (int i = 0; i < 10; i++)
		{
			projx[projx.size() - 1] = char(i + 48);
			projy[projy.size() - 1] = char(i + 48);
			diagleftprojx[diagleftprojx.size() - 1] = char(i + 48);
			diagleftprojy[diagleftprojy.size() - 1] = char(i + 48);
			diagrightprojx[diagrightprojx.size() - 1] = char(i + 48);
			diagrightprojy[diagrightprojy.size() - 1] = char(i + 48);
			if (data.find(projx) != data.end() && data.find(projy) != data.end()) render.enemyHandler.enemyProj[i] = new Ship::Projectile(data.at(projx).get<double>(), data.at(projy).get<double>());
			if (data.find(diagleftprojx) != data.end() && data.find(diagleftprojy) != data.end()) render.enemyHandler.enemyProjDiagonalLeft[i] = new Ship::Projectile(data.at(diagleftprojx).get<double>(), data.at(diagleftprojy).get<double>());
			if (data.find(diagrightprojx) != data.end() && data.find(diagrightprojy) != data.end()) render.enemyHandler.enemyProjDiagonalRight[i] = new Ship::Projectile(data.at(diagrightprojx).get<double>(), data.at(diagrightprojy).get<double>());
		}
		if (data.find("playerHp") != data.end())
		{
			render.playerhandler.player.setHp(data.at("playerHp").get<int>());
		}
		if (data.find("playerPoints") != data.end())
		{
			render.playerhandler.player.setPoints(data.at("playerPoints").get<int>());
		}
		if (data.find("playerx") != data.end() && data.find("playery") != data.end())
		{
			render.playerhandler.player.setPos(data.at("playerx").get<double>(), data.at("playery").get<double>());
		}
		if (data.find("playerSpeedx") != data.end())
		{
			render.playerhandler.player.setSpeedx(data.at("playerSpeedx").get<double>());
		}
		for (int i = 0; i < 3; i++)
		{
			playerprojx[playerprojx.size() - 1] = char(i + 48);
			playerprojy[playerprojy.size() - 1] = char(i + 48);
			if (data.find(playerprojx) != data.end() && data.find(playerprojy) != data.end()) render.playerhandler.proj[i] = new Ship::Projectile(data.at(playerprojx).get<double>(), data.at(playerprojy).get<double>());
		}

		for (int i = 0; i < 3; i++)
		{
			powerupx[powerupx.size() - 1] = char(i + 48);
			powerupy[powerupy.size() - 1] = char(i + 48);
			poweruphandleractive[poweruphandleractive.size() - 1] = char(i + 48);
			powerupid[powerupid.size() - 1] = char(i + 48);
			additionalTime[additionalTime.size() - 1] = char(i + 48);
			if (data.find(powerupx) != data.end() && data.find(powerupy) != data.end() && data.find(poweruphandleractive) != data.end() && data.find(powerupid) != data.end() && data.find(additionalTime) != data.end())
			{
				render.playerhandler.powerUpHandler.powerUp[i] = new PowerUp(data.at(powerupx).get<double>(), data.at(powerupy).get<double>(), data.at(powerupid).get<double>());
				render.playerhandler.powerUpHandler.additionalTime[i] = sf::seconds(data.at(additionalTime).get<float>());
				if(data.at(poweruphandleractive).get<bool>()) render.playerhandler.powerUpHandler.activate(i);
				else render.playerhandler.powerUpHandler.disactivate(i);
			}
		}
		
	}
	json_in.close();
}
void JsonHandler::loadLevel(Render& render, std::string name)
{
	std::ifstream json_in(name);
	json_in >> data;
	for (int i = 0; i < 10; i++)
	{
		enemyx[enemyx.size() - 1] = char(i + 48);
		enemyy[enemyy.size() - 1] = char(i + 48);
		enemyRotation[enemyRotation.size() - 1] = char(i + 48);
		enemySlope[enemySlope.size() - 1] = char(i + 48);
		enemyType[enemyType.size() - 1] = char(i + 48);
		enemySpeedx[enemySpeedx.size() - 1] = char(i + 48);
		if (data.find(enemyx) != data.end() && data.find(enemyy) != data.end() && data.find(enemyRotation) != data.end() && data.find(enemySlope) != data.end()
			&& data.find(enemyType) != data.end())
		{
			if (data.at(enemyType).get<int>() == 1)
				render.enemyHandler.enemy[i] =
				new Enemy1(data.at(enemyx).get<double>(), data.at(enemyy).get<double>(), data.at(enemySpeedx).get<double>(), data.at(enemyRotation).get<double>(), data.at(enemySlope).get<double>());
			else if (data.at(enemyType).get<int>() == 2)
				render.enemyHandler.enemy[i] =
				new Enemy2(data.at(enemyx).get<double>(), data.at(enemyy).get<double>(), data.at(enemySpeedx).get<double>(), data.at(enemyRotation).get<double>(), data.at(enemySlope).get<double>());
			else if (data.at(enemyType).get<int>() == 3)
				render.enemyHandler.enemy[i] =
				new Enemy3(data.at(enemyx).get<double>(), data.at(enemyy).get<double>(), data.at(enemySpeedx).get<double>(), data.at(enemyRotation).get<double>(), data.at(enemySlope).get<double>());
		}
	}
	json_in.close();
}
void JsonHandler::save(Render& render, std::string name)
{
	std::ofstream json_out(name);
	json enemy[10];
	for (int i = 0; i < 10; i++)
	{
		enemyx[enemyx.size() - 1] = char(i + 48);
		enemyy[enemyy.size() - 1] = char(i + 48);
		enemyRotation[enemyRotation.size() - 1] = char(i + 48);
		enemySlope[enemySlope.size() - 1] = char(i + 48);
		enemyType[enemyType.size() - 1] = char(i + 48);
		enemySpeedx[enemySpeedx.size() - 1] = char(i + 48);
		if (render.enemyHandler.enemy[i] != NULL)
		{
			enemy[i][enemyx] = render.enemyHandler.enemy[i]->getx();
			enemy[i][enemyy] = render.enemyHandler.enemy[i]->gety();
			enemy[i][enemyRotation] = render.enemyHandler.enemy[i]->getRotation();
			enemy[i][enemySlope] = render.enemyHandler.enemy[i]->getSlope();
			enemy[i][enemyType] = render.enemyHandler.enemy[i]->getType();
			enemy[i][enemySpeedx] = render.enemyHandler.enemy[i]->getSpeedx();
			json_out << enemy[i];
		}

	}
	json enemyProj[10];
	json enemyProjDiagLeft[10];
	json enemyProjDiagRight[10];
	for (int i = 0; i < 10; i++)
	{
		projx[projx.size() - 1] = char(i + 48);
		projy[projy.size() - 1] = char(i + 48);
		diagleftprojx[diagleftprojx.size() - 1] = char(i + 48);
		diagleftprojy[diagleftprojy.size() - 1] = char(i + 48);
		diagrightprojx[diagrightprojx.size() - 1] = char(i + 48);
		diagrightprojy[diagrightprojy.size() - 1] = char(i + 48);
		if (render.enemyHandler.enemyProj[i] != NULL)
		{
			enemyProj[i][projx] = render.enemyHandler.enemyProj[i]->getx();
			enemyProj[i][projy] = render.enemyHandler.enemyProj[i]->gety();
			json_out << enemyProj[i];

		}
		if (render.enemyHandler.enemyProjDiagonalLeft[i] != NULL)
		{
			enemyProj[i][diagleftprojx] = render.enemyHandler.enemyProjDiagonalLeft[i]->getx();
			enemyProj[i][diagleftprojy] = render.enemyHandler.enemyProjDiagonalLeft[i]->gety();
			json_out << enemyProjDiagLeft[i];
		}
		if (render.enemyHandler.enemyProjDiagonalRight[i] != NULL)
		{
			enemyProj[i][diagrightprojx] = render.enemyHandler.enemyProjDiagonalRight[i]->getx();
			enemyProj[i][diagrightprojy] = render.enemyHandler.enemyProjDiagonalRight[i]->gety();
			json_out << enemyProjDiagRight[i];
		}
	}
	json plProj[3];
	for (int i = 0; i < 3; i++)
	{
		playerprojx[playerprojx.size() - 1] = char(i + 48);
		playerprojy[playerprojy.size() - 1] = char(i + 48);
		if (render.playerhandler.proj[i] != NULL)
		{
			plProj[i][playerprojx] = render.playerhandler.proj[i]->getx();
			plProj[i][playerprojy] = render.playerhandler.proj[i]->gety();
			json_out << plProj[i];
		}
	}
	json powerUp[3];
	for (int i = 0; i < 3; i++)
	{
		powerupx[powerupx.size() - 1] = char(i + 48);
		powerupy[powerupy.size() - 1] = char(i + 48);
		poweruphandleractive[poweruphandleractive.size() - 1] = char(i + 48);
		powerupid[powerupid.size() - 1] = char(i + 48);
		additionalTime[additionalTime.size() - 1] = char(i + 48);
		if (render.playerhandler.powerUpHandler.powerUp[i] != NULL)
		{
			powerUp[i][powerupx] = render.playerhandler.powerUpHandler.powerUp[i]->getx();
			powerUp[i][powerupy] = render.playerhandler.powerUpHandler.powerUp[i]->gety();
			powerUp[i][powerupid] = render.playerhandler.powerUpHandler.powerUp[i]->getId();
			powerUp[i][poweruphandleractive] = render.playerhandler.powerUpHandler.getState(i);
			powerUp[i][additionalTime] = render.playerhandler.powerUpHandler.additionalTime[i].asSeconds();
			json_out << powerUp[i];
		}
		
	}
	json player;
	player["playerHp"] = render.playerhandler.player.getHp();
	player["playerx"] = render.playerhandler.player.getx();
	player["playery"] = render.playerhandler.player.gety();
	player["playerPoints"] = render.playerhandler.player.getPoints();
	player["playerSpeedx"] = render.playerhandler.player.getSpeedx();
	json_out << player;
	json_out.close();
}

#endif
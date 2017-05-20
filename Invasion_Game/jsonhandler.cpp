#include "jsonhandler.h"

void JsonHandler::load(Render *render)
{
	std::ifstream json_in("game.json");
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
			&& data.find(enemyType) != data.end()) render->enemyHandler.enemy[i] =
			new Enemy(data.at(enemyx).get<int>(), data.at(enemyy).get<int>(), data.at(enemyRotation).get<int>(), data.at(enemySlope).get<int>());;
	}
	std::string projx = "projx ";
	std::string projy = "projy ";
	std::string diagleftprojx = "diagleftprojx ";
	std::string diagleftprojy = "diagleftprojy ";
	std::string diagrightprojx = "diagrightprojx ";
	std::string diagrightprojy = "diagrightprojy ";
	for (int i = 0; i < 10; i++)
	{
		projx[projx.size() - 1] = char(i + 48);
		projy[projy.size() - 1] = char(i + 48);
		diagleftprojx[diagleftprojx.size() - 1] = char(i + 48);
		diagleftprojy[diagleftprojy.size() - 1] = char(i + 48);
		diagrightprojx[diagrightprojx.size() - 1] = char(i + 48);
		diagrightprojy[diagrightprojy.size() - 1] = char(i + 48);
		if (data.find(projx) != data.end() && data.find(projy) != data.end()) render->enemyHandler.enemyProj[i] = new Ship::Projectile(data.at(projx).get<int>(), data.at(projy).get<int>());
		if (data.find(diagleftprojx) != data.end() && data.find(diagleftprojy) != data.end()) render->enemyHandler.enemyProjDiagonalLeft[i] = new Ship::Projectile(data.at(diagleftprojx).get<int>(), data.at(diagleftprojy).get<int>());
		if (data.find(diagrightprojx) != data.end() && data.find(diagrightprojy) != data.end()) render->enemyHandler.enemyProjDiagonalRight[i] = new Ship::Projectile(data.at(diagrightprojx).get<int>(), data.at(diagrightprojy).get<int>());
	}
	render->playerhandler.player.setHp(data.at("playerHp").get<int>());
	render->playerhandler.player.setPoints(data.at("playerPoints").get<int>());
	render->playerhandler.player.setPos(data.at("playerx").get<int>(), data.at("playery").get<int>());
	std::string powerupx = "powerupx ";
	std::string powerupy = "powerupy ";
	std::string poweruphandleractive = "powerupactive ";
	std::string powerupid = "powerupactive ";
	json_in.close();
}
void JsonHandler::loadLevel(Render *render)
{
	std::ifstream json_in("game.json");
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
			&& data.find(enemyType) != data.end()) render->enemyHandler.enemy[i] =
			new Enemy(data.at(enemyx).get<int>(), data.at(enemyy).get<int>(), data.at(enemyRotation).get<int>(), data.at(enemySlope).get<int>());;
	}
	json_in.close();
}
void JsonHandler::save(Render *render)
{
}

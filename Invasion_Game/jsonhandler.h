#ifndef __RENDER_H_INCLUDED__
#define __RENDER_H_INCLUDED__
#include "json-develop\src\json.hpp"
#include <fstream>
#include "render.h"
using json = nlohmann::json;
class JsonHandler
{
private:
	json data;
public:
	std::string enemyx = "enemyx ";
	std::string enemyy = "enemyy ";
	std::string enemyRotation = "enemyRotation ";
	std::string enemySlope = "enemySlope ";
	std::string enemyType = "enemyType ";
	std::string enemySpeedx = "enemySpeedx ";
	std::string projx = "projx ";
	std::string projy = "projy ";
	std::string diagleftprojx = "diagleftprojx ";
	std::string diagleftprojy = "diagleftprojy ";
	std::string diagrightprojx = "diagrightprojx ";
	std::string diagrightprojy = "diagrightprojy ";
	std::string playerprojx = "playerprojx ";
	std::string playerprojy = "playerprojy ";
	std::string powerupx = "powerupx ";
	std::string powerupy = "powerupy ";
	std::string poweruphandleractive = "powerupactive ";
	std::string powerupid = "powerupid ";
	std::string additionalTime = "additionalTime ";
	void load(Render&, std::string = "game1.json");
	void loadLevel(Render&, std::string = "game.json");
	void save(Render&, std::string = "game1.json");
};
#endif // !__RENDER_H_INCLUDED__
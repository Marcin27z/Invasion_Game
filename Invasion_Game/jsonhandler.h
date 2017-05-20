#include "json-develop\src\json.hpp"
#include <fstream>
#include "render.h"
using json = nlohmann::json;
class JsonHandler
{
private:
	json data;
public:
	void load(Render *);
	void loadLevel(Render * render);
	void save(Render *);
};
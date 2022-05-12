#ifndef GAME_H
#define GAME_H


#include "Includes.h"
#include "HUD.h"


class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::Event ev;

	sf::Clock dtClock;
	float dt;

	HUD* miniview;
	sf::VertexArray vertices;

	//===Keybind (Map)===//
	std::map<std::string, int> supportedKeys;
	std::map<std::string, int> keyBinds;
	std::map<std::string, bool> keyBindPressed;
	//---Keybind (Map)---//

	//===MOUSE POSITION===//
	sf::Vector2i mosPosWindow;
	sf::Vector2f mosPosView;
	//---MOUSE POSITION---//

	//===PRIVATE FUNCTIONS===//
	void initWindow();
	void initSupportedKeys();
	void initKeyBinds();
	//---PRIVATE FUNCTIONS---//
public:
	//===CONSTRUCTORS||DESTRUCTORS===//
	Game();
	virtual ~Game();
	//---CONSTRUCTORS||DESTRUCTORS---//


	//===PUBLIC FUNCTIONS===//
	void endApplication();

	//===UPDATE===//
	void updateDeltaTime();
	void updateEvents();
	void updateMousePostions();

	void update();
	//---UPDATE---//

	//===RENDER===//
	void render();
	//---RENDER--//

	//===CORE===//
	void run();
	//---CORE---//
	//---PUBLIC FUNCTIONS---//
};

#endif

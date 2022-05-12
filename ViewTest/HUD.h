#ifndef HUD_H
#define HUD_H

#include "Includes.h"

class HUD
{
private:
	sf::View view;
	sf::VertexArray vertices;
	sf::RenderWindow* window;
public:
	HUD();
	HUD(sf::RenderWindow* window);
	virtual ~HUD();



	void render(sf::RenderTarget* target);
};

#endif


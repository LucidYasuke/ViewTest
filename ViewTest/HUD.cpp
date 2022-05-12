#include "HUD.h"

HUD::HUD()
{
}

HUD::HUD(sf::RenderWindow* window)
{
	this->window = window;

	this->view = window->getDefaultView();

	sf::Vector2f scale;
	scale.x = window->getDefaultView().getSize().x / 1280.f;
	scale.y = window->getDefaultView().getSize().y / 720.f;

	this->vertices = sf::VertexArray(sf::Quads, 4);

	this->vertices[0].position = sf::Vector2f(0, 0);
	this->vertices[1].position = sf::Vector2f(1280.f * scale.x, 0);
	this->vertices[2].position = sf::Vector2f(1280.f * scale.x, 720.f * scale.y);
	this->vertices[3].position = sf::Vector2f(0, 720.f * scale.y);

	// Default color white
	this->vertices[0].color = sf::Color::Red;
	this->vertices[1].color = sf::Color::Blue;
	this->vertices[2].color = sf::Color::Green;
	this->vertices[3].color = sf::Color::Yellow;



	float x = ((1280.f - (1280.f * .4f)) * scale.x) / (1280.f * scale.x);
	float y = ((720.f - (720.f * .5f)) * scale.y) / (720.f * scale.y);
	this->view.setViewport(sf::FloatRect(x, y, .4f, .5f));
}

HUD::~HUD()
{
}

void HUD::render(sf::RenderTarget* target)
{
	target->setView(this->view);

	target->draw(this->vertices);

	target->setView(this->window->getDefaultView());
}

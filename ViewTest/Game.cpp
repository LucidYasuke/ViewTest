#include "Game.h"

//===PRIVATE FUNCTIONS===//
void Game::initWindow()
{
    std::ifstream ifs("Config/window.ini");

    std::string title = "None";
    sf::VideoMode window_bounds(1280, 720);
    unsigned frame_limit = 120;
    bool vertical_sync_enabled = false;

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> frame_limit;
        ifs >> vertical_sync_enabled;
    }

    ifs.close();

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Default, settings);
    this->window->setFramerateLimit(frame_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);


}

void Game::initSupportedKeys()
{
    std::ifstream ifs("Config/supportedKeys.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        int keyValue = 0;

        while (ifs >> key >> keyValue)
        {
            this->supportedKeys[key] = keyValue;
        }
    }
    ifs.close();
}

void Game::initKeyBinds()
{
    std::ifstream ifs("Config/keyBinds.ini");

    if (ifs.is_open())
    {
        std::string keyOne = "";
        std::string keyTwo = "";

        while (ifs >> keyOne >> keyTwo)
        {
            this->keyBinds[keyOne] = this->supportedKeys.at(keyTwo);
        }
    }
    ifs.close();

    for (auto i : this->keyBinds)
    {
        this->keyBindPressed[i.first] = false;
    }
}

//---PRIVATE FUNCTIONS---//


//===CONSTRUCTORS||DESTRUCTORS===//
Game::Game()
{
    this->initWindow();
    this->initSupportedKeys();
    this->initKeyBinds();

    this->miniview = new HUD(this->window);

    sf::Vector2f scale;
    scale.x = this->window->getDefaultView().getSize().x / 1280.f;
    scale.y = this->window->getDefaultView().getSize().y / 720.f;

    this->vertices = sf::VertexArray(sf::Quads, 4);

    this->vertices[0].position = sf::Vector2f(0, 0);
    this->vertices[1].position = sf::Vector2f(1280.f * scale.x, 0);
    this->vertices[2].position = sf::Vector2f(1280.f * scale.x, 720.f * scale.y);
    this->vertices[3].position = sf::Vector2f(0, 720.f * scale.y);

    // Default color white
    this->vertices[0].color = sf::Color::Green;
    this->vertices[1].color = sf::Color::Yellow;
    this->vertices[2].color = sf::Color::Red;
    this->vertices[3].color = sf::Color::Blue;

}

Game::~Game()
{
    delete this->window;
}
//---CONSTRUCTORS||DESTRUCTORS---//


//===PUBLIC FUNCTIONS===//
//===REGULAR===//
void Game::endApplication()
{

}
//---REGULAR---//

//===UPDATE===//
void Game::updateDeltaTime()
{
    /*Updates Delta Time variable with time it takes to update and render one frame*/
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateEvents()
{
    //Event Polling
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            for (auto i : this->keyBinds)
            {
                if (ev.key.code == sf::Keyboard::Key(this->keyBinds[i.first]))
                {
                    this->keyBindPressed[i.first] = true;
                    break;
                }
            }
            break;
        case sf::Event::KeyReleased:
            for (auto i : this->keyBinds)
            {
                if (ev.key.code == sf::Keyboard::Key(this->keyBinds[i.first]))
                {
                    this->keyBindPressed[i.first] = false;
                    break;
                }
            }
            break;
        default:
            break;
        }
    }
}

void Game::updateMousePostions()
{
    /*
    @ return void

    Updates the mosue pos
    -Mouse position relative to window (Vector2i)
    */
    this->mosPosWindow = sf::Mouse::getPosition(*this->window);
    this->mosPosView = this->window->mapPixelToCoords(this->mosPosWindow);
}


void Game::update()
{
    this->updateEvents();
    this->updateMousePostions();
}
//---UPDATE--//

//===RENDER===//
void Game::render()
{
    this->window->clear();

    this->window->draw(this->vertices);
    this->miniview->render(this->window);


    this->window->display();
}
//---RENDER---//

//===CORE===//
void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDeltaTime();
        this->update();
        this->render();
    }
}
//---CORE---//
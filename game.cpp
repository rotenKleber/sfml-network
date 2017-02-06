#include "game.hpp"

Game::Game():
	window(sf::VideoMode(640, 480), "Blocky Mans"),
	square(sf::Vector2f(32, 32))
{
	// Capping frame rate (prevents computer from making squealing sound)
	window.setFramerateLimit(60);

	txPlayer.loadFromFile("friend.png");
	txDirt.loadFromFile("dirt.png");
		
	// Setting the font up
	if(!font.loadFromFile("oswald/Oswald-Regular.ttf"))
	{
		printf("Font not loaded\n");
	}
	
	// Generating map
	generateMap(20, 15);
	
	// Create player
	srand (time(NULL));
	std::string name;
	
	for (int i = 0; i < rand() % 8 + 2; i++)
	{
		char c = 'a';
		switch(rand() % 4)
		{
		case 0:
			c = 'b';
		break;
		case 1:
			c = 'c';
		break;
		case 2:
			c = 'e';
		break;
		case 3:
			c = 'f';
		break;
		}
		name += c;
	}
	
	player = new Unit(name);
}

void Game::generateMap(int w, int h)
{
	for(int x = 0; x < w; x++)
	{
		for(int y = 0; y < h; y++)
		{
			map[x][y] = Game::dirt;
		}
	}
}

void Game::processEvents(sf::Event& event)
{
	// Going through events
	while(window.pollEvent(event))
	{
		switch(event.type)
		{
			
			case sf::Event::Closed:
				window.close();
			break;
			
			case sf::Event::KeyPressed:
				switch(event.key.code)
				{
				case sf::Keyboard::W:
					moveUnit(player, 0, -1);
				break;
				case sf::Keyboard::S:
					moveUnit(player, 0, 1);
				break;
				case sf::Keyboard::A:
					moveUnit(player, -1, 0);
				break;
				case sf::Keyboard::D:
					moveUnit(player, 1, 0);
				break;
				}
			break;
		}
	}
} 

void Game::moveUnit(Unit* unit, int x, int y)
{
	unit->setPosition(unit->getX() + x, unit->getY() + y);
}

Game::~Game()
{
	delete player;
}

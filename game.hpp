#ifndef GAME_H_
#define GAME_H_

#include "unit.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <unordered_map>

class Unit;

/*
 * Game base class, holds all necessary game objects and
 * handels the multplayer connections
 * 
 * Both server and client game classes inherit from this
 */
class Game
{
public:
	Game();
	virtual ~Game();
	virtual void loop() = 0;
	virtual void loopMenu() = 0;

protected:
	enum tile {dirt};
	
	Unit* player;
		
	tile map[20][15];
	
	void generateMap(int w, int h);
	void processEvents(sf::Event& event);
	void moveUnit(Unit* unit, int x, int y);

	sf::RenderWindow window;
	sf::Font font;
	
	sf::Texture txPlayer;
	sf::Texture txDirt;
	sf::RectangleShape square;
	
	int m_port;

};

#endif

#ifndef GAMESERVER_H_
#define GAMESERVER_H_

#include "game.hpp"

/*
 * Game base class, holds all necessary game objects and
 * handels the multplayer connections
 * 
 * Is the server child, and as such handels all operations
 */
class GameServer : public Game
{
public:
	GameServer();
	~GameServer();
	
	void loop();
	void loopMenu();
	
	void moveUnit(std::string name, int x, int y);
	
private:
	void setupServer();
	
	std::unordered_map<std::string, Unit*> players;

	std::list<sf::Socket*> clients;
	sf::SocketSelector selector;
	sf::TcpListener listener;


};

#endif

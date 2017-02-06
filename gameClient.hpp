#ifndef GAMECLIENT_H_
#define GAMECLIENT_H_

#include "game.hpp"

/*
 * Game base class, holds all necessary game objects and
 * handels the multplayer connections
 * 
 * Is the client child, and as such must ask server for map and monster info
 */
class GameClient : public Game
{
public:
	GameClient();
	~GameClient();
	void loop();
	void loopMenu();

private:
	void connect();

	std::string m_ip;
	sf::TcpSocket server;
	sf::UdpSocket udpServer;


};

#endif

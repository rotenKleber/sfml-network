#include "gameServer.hpp"

GameServer::GameServer():
	Game()
{
	players[player->getName()] = player;
}


GameServer::~GameServer() 
{
	// Free memory from clients
	for(auto it = clients.begin(); it != clients.end(); it++)
	{
		delete (*it);
	}
	
	// Free memory from players
	for(auto it = players.begin(); it != players.end(); it++)
	{
		delete it->second;
	}
}

void GameServer::setupServer()
{
	// Bind the listener to a port
	if(listener.listen(m_port) != sf::Socket::Done)
	{
		printf("Could not bind server to port %i\n", m_port);
	}
	
	// Add the listener to the selector
	selector.add(listener);
	
	printf("Server set up with port# %i\n", m_port);
}

void GameServer::loop()
{
	setupServer();
	
	while(window.isOpen())
	{
		sf::Event event;
		
		// Send events to move player and what not
		processEvents(event);
		
		// Looking for new connections
		if(selector.wait(sf::milliseconds(1)))
		{
			// Check for connections
			if(selector.isReady(listener))
			{
				sf::TcpSocket* client = new sf::TcpSocket;
				
				if (listener.accept(*client) == sf::Socket::Done)
				{
					printf("New connection from '%s'\n", client->getRemoteAddress().toString().c_str());
					sf::IpAddress sender = client->getRemoteAddress();
					client->setBlocking(false);
					
					// Add new client to the clients list						
					clients.push_back(client);
					
					short unsigned int port = (short unsigned int) m_port;
					
					// Add the player
					sf::Packet packet;
					client->receive(packet);
					
					std::string name;
					packet >> name;
					
					Unit* player = new Unit(name);
					players[name] = player;
					
					printf("players: %i\n", (int)players.size());
					
				}
				else
				{
					// Error, we won't get a new connection, delete the socket
					printf("Failed connection\n");
					delete client;
				}
			}
		}
		
		for(auto it = clients.begin(); it != clients.end(); it++)
		{
			sf::TcpSocket& client = *(static_cast<sf::TcpSocket*>(*it));
			// The client has sent some data, we can receive it
			{
				sf::Packet packet;
				if (client.receive(packet) == sf::Socket::Done)
				{
					// Receiving position of player
					std::string name;
					int x, y;
					packet >> name >> x >> y;
					
					// Updating player
					players[name]->setPosition(x, y);
				}
			}
			
			// Sending player data back
			{
				sf::Packet packet;
				int n = players.size();
				packet << n;
				
				for(auto it = players.begin(); it != players.end(); it++) 
				{
					packet << it->second->getName();
					packet << it->second->getX();
					packet << it->second->getY();
				}
				
				client.send(packet);
			}
		}
		
		// Resetting screen
		window.clear();
		
		// Drawing players
		
		for(auto it = players.begin(); it != players.end(); it++) {			
			// Player text
			sf::Text playerText;
			playerText.setFont(font);
			playerText.setCharacterSize(12);
			playerText.setColor(sf::Color::Green);
			playerText.setString(it->second->getName());
			playerText.setPosition(it->second->getX() * 32, it->second->getY() * 32 - 16);
			
			square.setPosition(it->second->getX() * 32, it->second->getY() * 32);
			square.setTexture(&txPlayer);
			window.draw(square);
			
			window.draw(playerText);
		}
		
        window.display();
	}
}

void GameServer::loopMenu()
{
	bool running = true;
	std::string port;
	
	// Bool to take away backspace character when added
	bool toDeleteBackspace = false;
	
	while(window.isOpen() && running)
	{
		if(toDeleteBackspace)
		{
			toDeleteBackspace = false;
			
			if(port.size() > 0)
				port.pop_back();
		}
		
		sf::Event event;

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
					case sf::Keyboard::BackSpace:
						if(port.size() > 0)
							port.pop_back();
						
						toDeleteBackspace = true;
					break;
					
					case sf::Keyboard::Return:
						// Escape menu
						running = false;
					break;
					}
				
				break;
				
				case sf::Event::TextEntered:
					char key = '.';
					
					if(event.text.unicode < 64) {
						key = static_cast<char>(event.text.unicode);
						port.push_back(key);
					}
				break;
			}
		}
		
		// Game text
		sf::Text gameText;
		gameText.setFont(font);
		gameText.setCharacterSize(36);
		gameText.setColor(sf::Color::Green);
		gameText.setString("Blocky Mans: Server");
		gameText.setPosition(192, 0);
		
		// Label text
		sf::Text label;
		label.setFont(font);
		label.setCharacterSize(24);
		label.setColor(sf::Color::White);
		label.setString("Port: ");
		label.setPosition(16, 64);
		
		// Label text2
		sf::Text label2;
		label2.setFont(font);
		label2.setCharacterSize(24);
		label2.setColor(sf::Color::White);
		label2.setString("(Enter)");
		label2.setPosition(224, 400);
		
		// Port text
		sf::Text textPort;
		textPort.setFont(font);
		textPort.setCharacterSize(24);
		textPort.setColor(sf::Color::Red);
		textPort.setString(port);
		textPort.setPosition(64, 64);
		
		// Resetting screen
		window.clear();
		
		window.draw(label);
		window.draw(label2);
		window.draw(gameText);
		window.draw(textPort);
        
        window.display();
	}
	
	m_port = std::stoi(port, nullptr);
}

#include "gameClient.hpp"

GameClient::GameClient():
	Game()
{
}


GameClient::~GameClient() 
{
}

void GameClient::loop()
{
	connect();
	
	while(window.isOpen())
	{
		sf::Event event;
		
		// Send events to move player and what not
		processEvents(event);
		
		{
			sf::Packet packet;
			std::string name = player->getName();
			int x = player->getX();
			int y = player->getY();
			packet << name << x << y;
			server.send(packet);
		}
		
		
		// Resetting screen
		window.clear();
		
		// Receiving player data
		{
			sf::Packet packet;
			if(server.receive(packet) == sf::Socket::Done)
			{
				int n;
				packet >> n;
				
				for(int i = 0; i < n; i++)
				{
					std::string name;
					int x;
					int y;
					packet >> name >> x >> y;
					
					// Player text
					sf::Text playerText;
					playerText.setFont(font);
					playerText.setCharacterSize(12);
					playerText.setColor(sf::Color::Green);
					playerText.setString(name);
					playerText.setPosition(x * 32, y * 32 - 16);
					
					square.setPosition(x * 32, y * 32);
					square.setTexture(&txPlayer);
					window.draw(square);
					
					window.draw(playerText);
				}
			}
		}
		
        window.display();
	}
}

void GameClient::connect()
{
	sf::Socket::Status status = server.connect(m_ip, m_port);
	if (status != sf::Socket::Done)
	{
		printf("Could not connect!\n");
		// Go back to menu
		loopMenu();
	}
	else
	{		
		printf("Connected to %s on port %i\n", m_ip.c_str(), m_port);
		
		sf::Packet packet;
		packet << player->getName();
		
		server.send(packet);
	}
}

void GameClient::loopMenu()
{
	bool running = true;
	std::string port;
	std::string ip;
	
	// Whether user is entering port or ip (false = port)
	bool mode = false;
	
	std::string *str = &port;
	std::string emptyString;
	
	// Bool to take away backspace character when added
	bool toDeleteBackspace = false;
	
	while(window.isOpen() && running)
	{
		if(toDeleteBackspace)
		{
			toDeleteBackspace = false;
			
			if(str->size() > 0)
				str->pop_back();
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
						if(str->size() > 0)
							str->pop_back();
						
						toDeleteBackspace = true;
					break;
					
					case sf::Keyboard::Return:
						// Escape menu
						if(!mode)
						{
							mode = true;
							toDeleteBackspace = true;
							str = &ip;
						}
						else
						{	
							// Setting str to an empty, useless string rather than nullptr, because it is accessed even after running = false
							str = &emptyString;
							running = false;
						}
					break;
					}
				
				break;
				
				case sf::Event::TextEntered:
					char key = '.';
					
					if(event.text.unicode < 64) {
						key = static_cast<char>(event.text.unicode);
						str->push_back(key);
					}
				break;
			}
		}
		
		// Game text
		sf::Text gameText;
		gameText.setFont(font);
		gameText.setCharacterSize(36);
		gameText.setColor(sf::Color::Green);
		gameText.setString("Blocky Mans: Client");
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
		
		// Label text3
		sf::Text label3;
		label3.setFont(font);
		label3.setCharacterSize(24);
		label3.setColor(sf::Color::White);
		label3.setString("IP: ");
		label3.setPosition(16, 96);
		
		// Port text
		sf::Text textPort;
		textPort.setFont(font);
		textPort.setCharacterSize(24);
		textPort.setColor(sf::Color::Red);
		textPort.setString(port);
		textPort.setPosition(64, 64);
		
		// IP text
		sf::Text textIP;
		textIP.setFont(font);
		textIP.setCharacterSize(24);
		textIP.setColor(sf::Color::Red);
		textIP.setString(ip);
		textIP.setPosition(64, 96);
		
		// Resetting screen
		window.clear();
		
		window.draw(label);
		window.draw(label2);
		window.draw(label3);
		window.draw(gameText);
		window.draw(textPort);
		window.draw(textIP);
        
        window.display();
	}
	
	m_port = std::stoi(port, nullptr);
	m_ip = ip;
}

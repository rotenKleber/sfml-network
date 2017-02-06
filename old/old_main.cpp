#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <stdio.h>
#include <string>

int main()
{
	char choice;
	int port;
	std::cout << "(C)lient / (S)erver: ";
	std::cin >> choice;
	
	std::cout << "\nEnter Port: ";
	std::cin >> port;
	std::cout << std::endl;
	
	sf::RenderWindow window(sf::VideoMode(400, 400), "Networker");
	window.setFramerateLimit(60); // Capping frame rate (prevents computer from making squealing sound)
	
	sf::SocketSelector selector;
	
	sf::TcpSocket socket;
	
	if(choice == 'c' || choice == 'C')
	{
		// Client
		
		std::string ip;
		
		std::cout << "Enter IP: ";
		std::cin >> ip;
		
		std::cout << std::endl;
		
		sf::Socket::Status status = socket.connect(ip, port);
		if (status != sf::Socket::Done)
		{
			std::cout << "Connection failed.\n";
		}
		
		selector.add(socket);
	
	} else {		
		// Server
		
		sf::TcpListener listener;

		// bind the listener to a port
		if (listener.listen(port) != sf::Socket::Done)
		{
			std::cout << "Binding failed.\n";
		}

		std::cout << "Waiting for connection...\n";

		// accept a new connection
		if (listener.accept(socket) != sf::Socket::Done)
		{
			std::cout << "Client connection failed.\n";
		}
		
		std::cout << "Connected\n";
		
		selector.add(socket);
		
	}
	
	// Stop the socket from blocking
	socket.setBlocking(false);
	
	// Set up graphics and font
	sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);
	
	sf::Font font;
	if (!font.loadFromFile("oswald/Oswald-Regular.ttf"))
	{
		printf("Font not loaded\n");
	}
	
	// Main loop
	std::string message;
	
	while (window.isOpen())
	{			
		sf::Event event;

		// while there are pending events...
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
				break;

				case sf::Event::TextEntered:
					char key;
					if (event.text.unicode < 128)
						key = static_cast<char>(event.text.unicode);
					
					std::string msg;
					msg += key;
					
					// Sending packet
					sf::Packet sendPacket;
					sendPacket << msg;
					socket.send(sendPacket);
				break;
			}
		}
		
		// Checking to see if packages are available
		std::string msgReceived;
		sf::Packet receivePacket;
		
		socket.receive(receivePacket);
		
		receivePacket >> msgReceived;
		message += msgReceived;
		
		// Drawing text
		sf::Text text;
		text.setFont(font);
		text.setString(message);

		text.setCharacterSize(24);
		text.setColor(sf::Color::Red);

		// Resetting screen
		window.clear();
		window.draw(text);
        //window.draw(shape);
        window.display();
	}
		
	std::cout << "Terminating.\n";
	
    return 0;
}

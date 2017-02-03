//#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
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
	
	if(choice == 'c' || choice == 'C') {
		// Client
		
		std::string ip;
		
		std::cout << "Enter IP: ";
		std::cin >> ip;
		
		std::cout << std::endl;
		
		sf::TcpSocket socket;
		sf::Socket::Status status = socket.connect(ip, port);
		if (status != sf::Socket::Done)
		{
			std::cout << "Connection failed.\n";
		}
		
		// Setting up socket selector
		
		sf::SocketSelector selector;
		selector.add(socket);
		
		// Main loop
		
		std::string msg;
		
		while(msg != "exit") {			
			std::cout << ">>> ";
			std::cin >> msg;
			std::cout << std::endl;
			
			// Checking to see if packages are available
			if (selector.isReady(socket))
			{
				std::string msgReceived;
				sf::Packet receivePacket;
				
				socket.receive(receivePacket);
				
				receivePacket >> msgReceived;
				std::cout << msgReceived << std::endl;
			}
			
			// Sending packet
			sf::Packet sendPacket;
			sendPacket << msg;
			socket.send(sendPacket);
		}
		
		std::cout << "Terminating.\n";
	
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
		sf::TcpSocket client;
		if (listener.accept(client) != sf::Socket::Done)
		{
			std::cout << "Client connection failed.\n";
		}
		
		// Setting up socket selector
		
		sf::SocketSelector selector;
		selector.add(client);
		
		// Main loop
		
		std::string msg;
		
		while(msg != "exit") {			
			std::cout << ">>> ";
			std::cin >> msg;
			std::cout << std::endl;
			
			// Checking to see if packages are available
			if (selector.isReady(client))
			{
				std::string msgReceived;
				sf::Packet receivePacket;
				
				client.receive(receivePacket);
				
				receivePacket >> msgReceived;
				std::cout << msgReceived << std::endl;
			}
			
			// Sending packet
			sf::Packet sendPacket;
			sendPacket << msg;
			client.send(sendPacket);
		}
		
		std::cout << "Terminating.\n";
	}
    return 0;
}


	/*
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
	
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
	*/

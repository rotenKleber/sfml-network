//#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

int main()
{
	char choice;
	int port;
	std::cout << "(C)onnect / (H)ost: ";
	std::cin >> choice;
	
	std::cout << "\nEnter Port: ";
	std::cin >> port;
	std::cout << std::endl;
	
	if(choice == 'h' || choice == 'H') {
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
		
		sf::TcpListener listener;

		// bind the listener to a port
		if (listener.listen(port) != sf::Socket::Done)
		{
			std::cout << "Binding failed.\n";
		}

		// accept a new connection
		sf::TcpSocket client;
		if (listener.accept(client) != sf::Socket::Done)
		{
			std::cout << "Client connection failed.\n";
		}
		
		std::cout << "Sending package.\n";
		
		std::string message = "Hello";
		sf::Packet sendPacket;
		sendPacket << message;
		
		socket.send(sendPacket);
		
		std::cout << "Package sent.\n";
		
		std::string messageReceived;
		sf::Packet receivePacket;
		
		socket.receive(receivePacket);
		
		receivePacket >> messageReceived;
		std::cout << "Package received: " << messageReceived << std::endl;
		
		std::cout << "Terminating.\n";
	} else {		
		sf::TcpListener listener;

		// bind the listener to a port
		if (listener.listen(port) != sf::Socket::Done)
		{
			std::cout << "Binding failed.\n";
		}

		// accept a new connection
		sf::TcpSocket client;
		if (listener.accept(client) != sf::Socket::Done)
		{
			std::cout << "Client connection failed.\n";
		}
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

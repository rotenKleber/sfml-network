#include "gameServer.hpp"
#include "gameClient.hpp"
#include <stdio.h>

int main(int argc, char* argv[])
{	
	if(argc > 1) {
		GameServer server;
		server.loopMenu();
		server.loop();
	}
	else
	{
		GameClient client;
		client.loopMenu();
		client.loop();
	}
	
	return 0;
}

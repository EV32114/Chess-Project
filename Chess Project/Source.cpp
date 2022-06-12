#pragma comment (lib, "ws2_32.lib")

#include <iostream>
#include <thread>
#include "Board.h"
#include "WSAInitializer.h"
#include <WinSock2.h>
#include "HandleGame.h"
#include <string>
#include "Server.h"

#define PORT_ADDRESS 3000


int main()
{
	WSAInitializer wsaInit;
	srand(time_t(NULL));
	Server server;
	server.serve(PORT_ADDRESS);
	SOCKET ESPSocket = server.acceptClient();
	SOCKET imageSocket = server.acceptClient();
	SOCKET AISocket = server.acceptClient();
	Board* board = new Board(INIT_STR);

	HandleGame::startGame(board, &imageSocket, &AISocket, &ESPSocket);
	closesocket(imageSocket);
	closesocket(AISocket);
	closesocket(ESPSocket);
	return 0;
}

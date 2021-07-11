#include <iostream>
#include <thread>
#include "Board.h"
#include "WSAInitializer.h"
#include <WinSock2.h>
#include "HandleGame.h"
#include <string>

#define PORT_ADDRESS 3000

void bindAndListen(SOCKET& m_socket)
{
	struct sockaddr_in sa { 0 };
	sa.sin_port = htons(PORT_ADDRESS);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;

	if (bind(m_socket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - bind");
	}

	if (listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - listen");
	}
	std::cout << "Listening on port " << PORT_ADDRESS << std::endl;
}

int main()
{
	WSAInitializer wsaInit;
	srand(time_t(NULL));
	SOCKET m_socket;
	Board* board = new Board(INIT_STR);
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
	try
	{
		bindAndListen(m_socket);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Something bad happened here... " << e.what() << std::endl;
	}
	SOCKET client_socket = accept(m_socket, NULL, NULL);

	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);
	HandleGame::startGame(board, &client_socket);
	closesocket(m_socket);
	return 0;
}

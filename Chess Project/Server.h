#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <string>


class Server
{
public:
	Server();
	~Server();
	void serve(int port);
	SOCKET acceptClient();
	static void sendMsg(SOCKET clientSocket, std::string msg);
	static std::string recvMsg(SOCKET clientSocket);

private:
	// void clientHandler(SOCKET clientSocket);

	SOCKET _serverSocket;
};

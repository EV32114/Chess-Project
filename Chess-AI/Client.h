#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <string>
#include <vector>

class Client
{
public:
	SOCKET _clientSocket;
	Client();
	~Client();
	void connectToServer(std::string serverIP, int port);
	// void startConversation();
	void sendMsg(SOCKET clientSocket, std::string msg);
	std::string recvMsg(SOCKET clientSocket);
};

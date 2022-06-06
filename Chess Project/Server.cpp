#include "Server.h"
#include <exception>
#include <iostream>
#include <string>
#include <thread>

Server::Server()
{

	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Server::~Server()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(_serverSocket);
	}
	catch (...) {}
}

void Server::serve(int port)
{

	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << port << std::endl;

	/*while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		std::cout << "Waiting for client connection request" << std::endl;
		acceptClient();
	}*/
}


SOCKET Server::acceptClient()
{

	// this accepts the client and create a specific socket from server to this client
	// the process will not continue until a client connects to the server
	SOCKET client_socket = accept(_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Server and client can speak" << std::endl;
	// the function that handle the conversation with the client
	return client_socket;
}

void Server::sendMsg(SOCKET clientSocket, std::string msg)
{
	send(clientSocket, msg.c_str(), msg.size(), 0);
}

std::string Server::recvMsg(SOCKET clientSocket)
{
	std::vector<char> buffer(5000);
	int result = recv(clientSocket, buffer.data(), buffer.size(), 0);
	if (result != -1) {
		buffer.resize(result);
	}
	else {
		throw std::runtime_error("communication failed");
	}
	return std::string(buffer.begin(), buffer.end());
}

/*
void Server::clientHandler(SOCKET clientSocket)
{
	try
	{
		std::string s = "Welcome! What is your name (4 bytes)? ";
		send(clientSocket, s.c_str(), s.size(), 0);  // last parameter: flag. for us will be 0.

		char m[5];
		recv(clientSocket, m, 4, 0);
		m[4] = 0;
		std::cout << "Client name is: " << m << std::endl;

		s = "Bye";
		send(clientSocket, s.c_str(), s.size(), 0);

		// Closing the socket (in the level of the TCP protocol)
		closesocket(clientSocket);
	}
	catch (const std::exception& e)
	{
		closesocket(clientSocket);
	}
}
*/
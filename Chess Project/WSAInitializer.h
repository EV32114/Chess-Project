#pragma once

#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib,"WS2_32")


class WSAInitializer
{
public:
	WSAInitializer();
	~WSAInitializer();
};


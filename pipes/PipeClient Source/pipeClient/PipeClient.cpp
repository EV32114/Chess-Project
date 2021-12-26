// PipeClient.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include <string>
#include <io.h>
#include <fcntl.h>
#include "CPipeClient.h"

int _tmain(int argc, _TCHAR* argv[])
{
    _setmode(_fileno(stdout), _O_U8TEXT);
    std::wcout << _T("---------------------Pipe Client--------------------") << std::endl;
    std::wstring sPipeName(PIPENAME);
    CPipeClient* pClient = new CPipeClient(sPipeName);
    ::WaitForSingleObject(pClient->GetThreadHandle(), INFINITE);
    delete pClient;
    pClient = NULL;
    return 0;
}


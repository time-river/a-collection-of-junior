#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <IPHlpApi.h>
#include <iostream>
#include <strsafe.h>
#include <list>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define MAX_THREADS 20

struct Thread {
	HANDLE handler;
	SOCKET ClientSocket;
	DWORD  identifier;
};

DWORD WINAPI client(LPVOID lpParam);
void ErrorHandler(LPTSTR lpszFunction);
DWORD WINAPI CloseHandler(LPVOID lpParam);
bool HandlerRemove(const struct Thread &thread);
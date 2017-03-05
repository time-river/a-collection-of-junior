#include "stdafx.h"

using namespace std;

int users;
list<struct Thread> threads;

int __cdecl main(int argc, char* argv[]){
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;
	HANDLE closeHandler;
	DWORD  dwCloseHandler;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	// Validate teh parameters
	if (argc != 2){
		cerr << "Usage: " << argv[0] << " [server port]" << endl;
		return 1;
	}

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0){
		cerr << "WSAStartup failed with error: " << iResult << endl;
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, argv[1], &hints, &result);
	if (iResult != 0){
		cerr << "getaddrinfo failed with error: " << iResult << endl;
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET){
		cerr << "socket failed with error: " << WSAGetLastError() << endl;
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR){
		cerr << "bind failed with error: " << WSAGetLastError() << endl;
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR){
		cerr << "accept failed with error: " << WSAGetLastError() << endl;
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	closeHandler = CreateThread(
		NULL,
		0,
		CloseHandler,
		(LPVOID)NULL,
		0,
		&dwCloseHandler);
	if (closeHandler == NULL){
		ErrorHandler(TEXT("CreateThread"));
		ExitProcess(3);
	}

	// Accept a client socket
	while (true){
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET){
			cerr << "accept failed failed with error: " << WSAGetLastError() << endl;
			closesocket(ClientSocket);
			continue;
		}

		users++;
		cout << "Currently users: " << users << endl;

		if (threads.size() == MAX_THREADS){
			cerr << "Max client. Confuse service." << endl;
			closesocket(ClientSocket);
			continue;
		}

		// Generate unique data for each  thread to work with.
		struct Thread thread;
		thread.ClientSocket = ClientSocket;
		ClientSocket == INVALID_SOCKET;

		thread.handler = CreateThread(
			NULL,
			0,
			client,
			&thread.ClientSocket,
			0,
			&thread.identifier);
		// Check the return value for success.
		// If CreateThread fails, terminate execution. 
		// This will automatically clean up threads and memory. 
		if (thread.handler == NULL){
			ErrorHandler(TEXT("CreateThread"));
			ExitProcess(3);
		} // End of main thread creation

		threads.push_back(thread);
	}

	// No longer need server socket, clean up
	closesocket(ListenSocket);
	WSACleanup();

	return 0;
}
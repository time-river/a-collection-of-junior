#include "stdafx.h"

using namespace std;

int __cdecl main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	char sendbuf[DEFAULT_BUFLEN+1];
	char recvbuf[DEFAULT_BUFLEN+1];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;

	// Validate teh parameters
	if (argc != 3){
		cerr << "Usage: " << argv[0] << " [server name] [server port]" << endl;
		return 1;
	}

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0){
		cerr << "WSAStartup failed with error: " << iResult << endl;
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(argv[1], argv[2], &hints, &result);
	if (iResult != 0){
		cerr << "getaddrinfo failed with error: " << iResult << endl;
		WSACleanup();
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next){
		// Create a SOCKET for connectiong to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET){
			cerr << "socket failed with error: " << WSAGetLastError() << endl;
			WSACleanup();
			return 1;
		}

		// Connect to server
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR){
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET){
		cerr << "Unable to connect to server!" << endl;
		WSACleanup();
		return 1;
	}

	// Send an initial buffer
	sprintf_s(sendbuf, "Message from client: process ID -- %d, thread ID -- %d", GetCurrentProcessId(),GetCurrentThreadId());
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR){
		cerr << "send failed with error: " << WSAGetLastError() << endl;
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	// shutdown the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR){
		cerr << "shutdown failed with error: " << WSAGetLastError() << endl;
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	// Receive until the peer closes the connection
	do{
		ZeroMemory(recvbuf, sizeof(recvbuf));
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
			cout << recvbuf << endl;
		else if (iResult == 0)
			cout << "Connection closed.\n" << endl;
		else
			cerr << "recv failed with error: " << WSAGetLastError() << endl;
	} while (iResult > 0);

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();
	return 0;
}


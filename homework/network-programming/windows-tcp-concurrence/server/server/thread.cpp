#include "stdafx.h"

using namespace std;

DWORD WINAPI client(LPVOID lpParam){
	SOCKET ClientSocket = *(SOCKET *)lpParam;
	char recvbuf[DEFAULT_BUFLEN+1];
	int  recvbuflen = DEFAULT_BUFLEN;
	int iResult;
	extern int users;

	// Receive until the peer shuts down the connection
	do{
		ZeroMemory(recvbuf, sizeof(recvbuf));
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0){
			cout << recvbuf << endl;

			// Send message to the sender
			sprintf_s(recvbuf, "Message from server, process ID -- %d, thread ID -- %d: Hello, %d users. \n", GetCurrentProcessId(), GetCurrentThreadId(), users);
			iResult = send(ClientSocket, recvbuf, strlen(recvbuf), 0);
			if (iResult == SOCKET_ERROR){
				cerr << "send failed with error: " << WSAGetLastError() << endl;
				closesocket(ClientSocket);
				return -1;
			}
		}
		else if (iResult < 0){
			cerr << "recv failed with error: " << WSAGetLastError() << endl;
			closesocket(ClientSocket);
			return -1;
		}
		else
			cout << "Close connecting..." << endl;
	} while (iResult > 0);

	// shutdown the connection since we're down
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR){
		cerr << "shutdown failed with error: " << WSAGetLastError() << endl;
		closesocket(ClientSocket);
		return -1;
	}

	// close client socket
	closesocket(ClientSocket);
	users--;
	cout << "One user left. Currently users: " << users << endl;

	return 0;
}

void ErrorHandler(LPTSTR lpszFunction){
	// Retrieve the system error message for the last-error code.
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message.
	// Display the error message.

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	// Free error-handling buffer allocations.

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}

DWORD WINAPI CloseHandler(LPVOID lpParam){
	extern list<struct Thread> threads;
	list<struct Thread>::const_iterator thread;

	while (true){
		if (!threads.empty()){
			threads.remove_if(HandlerRemove);
		}
		Sleep(250);
	}

	return 0;
}

bool HandlerRemove(const struct Thread &thread){
	DWORD result;

	result = WaitForSingleObject(thread.handler, 0);
	if (result == WAIT_OBJECT_0){
		CloseHandle(thread.handler);
		cout << "close handler..." << endl;
		return true;
	}
	else
		return false;
}
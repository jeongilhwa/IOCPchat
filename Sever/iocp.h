#pragma once
#include "pch.h"
typedef struct Overlap   // buffer info
{
	OVERLAPPED overlapped;
	WSABUF wsaBuf;
	char buffer[BUF_SIZE];
	INT rwMode;    // READ or WRITE
}*P_overlap;

class Server
{
private:
	WSADATA    wsaData;
	HANDLE hcp;
	SYSTEM_INFO sysInfo;
	//오버랩과 메세지버퍼정보
	P_overlap ioInfo;
//	LPPER_HANDLE_DATA handleInfo;
	SOCKET hServSock;
	SOCKADDR_IN servAdr;
	
	DWORD recvBytes, flags = 0;
	User *user;

public:

	static vector<User*>userlist;
	

	Server() {}
	void AcceptEx();
	void ReadySock();
	
	
};

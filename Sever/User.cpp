#include "pch.h"

void User::ClientGet(SOCKET client_sock,SOCKADDR_IN client_addr)
{

	this->user_sock = client_sock;
	this->clntAdr = client_addr;
}

SOCKET User::UserSock()
{
	return SOCKET(user_sock);
}

void User::UserInfo()
{
	cout << user_sock << endl;
}

void User::PrintIp()
{
	inet_ntop(AF_INET, &clntAdr.sin_addr, ip, INET_ADDRSTRLEN);
	cout << ip << endl;
}

void User::Getname(char name)
{
	username[NAME_SIZE] = name;

}

void User::Printname()
{
	cout << username << endl;
}

void User::Printsock()
{
	cout << user_sock << endl;
}

void User::LogoutCount()
{
	++logout_count;
}


void User::LogInCount()
{
	++login_count;
}

//
//
//void User::WSASendevent(P_overlap *iolnfo)
//{
//	std::vector<User*>::iterator iter;
//	for (iter = Server::userlist.begin(); iter != Server::userlist.end(); ++iter)
//	{
//		P_overlap ioInfo;
//		ioInfo = (P_overlap)malloc(sizeof(Overlap));
//		memset(&(ioInfo->overlapped), 0x00, sizeof(OVERLAPPED));
//		int len = strlen(message);
//		ioInfo->wsaBuf.len = len;
//		strcpy(ioInfo->buffer, message);
//		ioInfo->wsaBuf.buf = ioInfo->buffer;
//		ioInfo->rwMode = WRITE;
//		if (bytesTrans == 0)
//		{
//			closesocket(sock);
//			//free(handleInfo);
//			delete[] user;
//			free(ioInfo);
//			continue;
//		}
//
//		if (WSASend((*iter)->UserSock(), &(ioInfo->wsaBuf), 1, &bytesTrans, 0, &(ioInfo->overlapped), NULL) == SOCKET_ERROR)
//		{
//			if (WSAGetLastError() != WSA_IO_PENDING)
//				ErrorHandling("WSASend() error");
//		}
//	}
//	
//}
//void User::Userclose()
//{
//	//erase_lock.lock();
//	std::vector<User*>::iterator iter;
//	for (iter = Server::userlist.begin(); iter != Server::userlist.end(); ++iter) {
//		if ((*iter)->UserSock() == sock) {
//			cout << "Logout >> " << "IP :";
//			(*iter)->PrintIp();
//			cout << ", " << "Sock :";
//			(*iter)->UserSock();
//			cout << ", " << "name :";
//			(*iter)->Printname();
//			cout << endl;
//			Server::userlist.erase(iter);
//			std::cout << ++logout_count << '\n';
//			break;
//		}
//	}
//}
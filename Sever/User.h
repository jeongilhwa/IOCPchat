#pragma once
#include"pch.h"

class User
{
private:

	SOCKET user_sock;
	SOCKADDR_IN clntAdr;
	  
	CHAR ip[22];

public:
	CHAR username[NAME_SIZE];
	User() {
		this->login_count = 0;
		this->logout_count = 0;
	}
	
	void ClientGet(SOCKET client_sock,SOCKADDR_IN client_Addr);
	SOCKET UserSock();
	void UserInfo();
	void PrintIp();
	void Printname();
	void Printsock();
	void Getname(char name);
	
	
	void LogoutCount();
	
	void LogInCount();
	
	
	int login_count ;
	int logout_count ;
/*
	void Userclose();*/

	//void WSASendevent(P_overlap *iolnfo);

	
	

};

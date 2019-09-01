#include"pch.h"
int main()
{

	Server server;



	server.ReadySock();
	server.AcceptEx();
	
	return 0;
}
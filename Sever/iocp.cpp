
#include"pch.h"
vector<User*> Server::userlist = vector<User*>();

std::mutex push_lock;
std::mutex sock_lock;

unsigned __stdcall ThreadMain(void * CompletionPortIO);
//void ErrorHandling(const char *message);
//P_overlap DataReset(P_overlap ioInfo);

void Server::ReadySock()
{
	cout << "IOCP 채팅 SERVER!!" << endl;
	// winsock start
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup Error");

	hcp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	GetSystemInfo(&sysInfo);

	// main thread와 연결된 thread 생성
	for (unsigned int i = 0; i < sysInfo.dwNumberOfProcessors; i++)
		_beginthreadex(NULL, 0, ThreadMain, (LPVOID)hcp, 0, NULL);

	// socket 설정
	hServSock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(PORT_NUM);

	// bind and listen q
	bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr));
	
	listen(hServSock, CLIENT_SIZE);

}
void Server::AcceptEx()
{
	while (1)
	{
		sock_lock.lock();

		SOCKET hClntSock;
		SOCKADDR_IN clntAdr;
		int addrLen = sizeof(clntAdr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &addrLen);

		sock_lock.unlock();
		
		User *user = new User;      
		user->ClientGet(hClntSock,clntAdr);
		
		user->LogInCount();
		
		cout << user->login_count << '\n';
		printf("New Client Access : " );
		user->PrintIp();
		//memcpy(&(user->clntAdr), &clntAdr, addrLen);

		// 소켓 입출력 포트에 accept을 통해서 return 된 클라이언트 정보를 묶는다.
		CreateIoCompletionPort((HANDLE)hClntSock, hcp, (DWORD)user, 0);
		
	
		// 클라이언트가 가지게 될 data 초기화
		P_overlap ioInfo = (P_overlap)malloc(sizeof(Overlap));
		memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
		ioInfo->wsaBuf.len = BUF_SIZE;
		ioInfo->wsaBuf.buf = ioInfo->buffer;
		memset(ioInfo->buffer, 0x00, BUF_SIZE);
		ioInfo->rwMode = READ;
		
		// name 받기
		recv(user->UserSock(),user->username, NAME_SIZE, 0);
		//user->Getname((char)Name);
		
		push_lock.lock();
		userlist.push_back(user);
		push_lock.unlock();;

		// 비동기 입출력 시작
		WSARecv(user->UserSock(), &(ioInfo->wsaBuf), 1, &recvBytes, &flags, &(ioInfo->overlapped), NULL);
	}

}


void ErrorHandling(const char *message)
{
	perror(message);
	exit(1);
}





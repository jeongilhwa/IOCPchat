// Client.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"


unsigned WINAPI SendMsg(void* arg);//쓰레드 전송함수
unsigned WINAPI RecvMsg(void* arg);//쓰레드 수신함수
void ErrorHandling(const char* msg);


int main(int argc, char* argv[]) {
	WSADATA wsaData;
	SOCKET sock;
	SOCKADDR_IN serverAddr;
	HANDLE sendThread, recvThread;
	/*if (argc != 4) {
		printf("Usage : %s <IP> <port> <name>\n", argv[0]);
		exit(1);
	}*/
	cout << "connect........\n";
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)// 윈도우 소켓을 사용한다고 운영체제에 알림
		ErrorHandling("WSAStartup() error!");
	cout << "이름을 입력하세요";
	cin >> name;
	cout << endl;
	//scanf("%s",name);
	sock = socket(PF_INET, SOCK_STREAM, 0);//소켓을 하나 생성한다.
	
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("192.168.0.67");
	serverAddr.sin_port = htons(3800);

	if (connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)//서버에 접속한다.
		ErrorHandling("connect() error");

	// 접속에 성공하면 이 줄 아래가 실행된다.
	std::cout << "Connect Success!\n";
	std::cout << "Sending client's name\n";
	send(sock, name, sizeof(name), 0);
	std::cout << "Success!\n";

	sendThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&sock, 0, NULL);//메시지 전송용 쓰레드가 실행된다.
	recvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&sock, 0, NULL);//메시지 수신용 쓰레드가 실행된다.

	WaitForSingleObject(sendThread, INFINITE);//전송용 쓰레드가 중지될때까지 기다린다./
	WaitForSingleObject(recvThread, INFINITE);//수신용 쓰레드가 중지될때까지 기다린다.
	//클라이언트가 종료를 시도한다면 이줄 아래가 실행된다.
	closesocket(sock);//소켓을 종료한다.
	WSACleanup();//윈도우 소켓 사용중지를 운영체제에 알린다.
	std::cout << "Client exit\n";
	return 0;
}

unsigned WINAPI SendMsg(void* arg) {//전송용 쓰레드함수
	SOCKET sock = *((SOCKET*)arg);//서버용 소켓을 전달한다.
	char msg[BUF_SIZE];
	while (1) {//반복
		fgets(msg, BUF_SIZE, stdin);//입력을 받는다.
		if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n")) {//q를 입력하면 종료한다.
			closesocket(sock);
			send(sock, "", 0, 0);
			exit(0);
		}
		send(sock, msg, strlen(msg), 0);//nameMsg를 서버에게 전송한다.
	}
	return 0;
}

unsigned WINAPI RecvMsg(void* arg) {
	SOCKET sock = *((SOCKET*)arg);//서버용 소켓을 전달한다.
	char msg[NAME_SIZE + BUF_SIZE];
	int strLen;
	while (1) {//반복
		strLen = recv(sock, msg, NAME_SIZE + BUF_SIZE - 1, 0);//서버로부터 메시지를 수신한다.
		if (strLen == -1)
			return -1;
		msg[strLen] = 0;//문자열의 끝을 알리기 위해 설정
		std::cout << ">>" << msg << '\n';
	}
	return 0;
}

void ErrorHandling(const char* msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}




// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.

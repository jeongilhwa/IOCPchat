
#include "pch.h"
std::mutex erase_lock;
unsigned __stdcall ThreadMain(void * pComPort)
{
	HANDLE hComPort = (HANDLE)pComPort;
	SOCKET sock;
	DWORD bytesTrans;
	//LPPER_HANDLE_DATA handleInfo;
	User *user;
	P_overlap ioInfo;
	int flags = 0;
	CHAR message[BUF_SIZE];

	while (1)
	{
		// 비동기 입출력 완료를 기다린다.
		GetQueuedCompletionStatus(hComPort, &bytesTrans, (LPDWORD)&user, (LPOVERLAPPED*)&ioInfo, INFINITE);
		// 클라이언트의 socket을 가져온다.
		sock = user->UserSock();


		// 첫 시작은 읽기 상태
		if (ioInfo->rwMode == READ)
		{
			puts("\nmessage received!");
			if (bytesTrans == 0)
			{
				erase_lock.lock();
				std::vector<User*>::iterator iter;
				for (iter = Server::userlist.begin(); iter != Server::userlist.end(); ++iter) {
					if ((*iter)->UserSock() == sock) {
						cout << "Logout >> " << "IP :";
						(*iter)->PrintIp();
						cout << ", " << "Sock :";
						(*iter)->Printsock();
						cout << ", " << "name :";
						(*iter)->Printname();
						cout << endl;
						Server::userlist.erase(iter);
						user->LogoutCount();
						//cout <<user->logout_count << '\n';
						break;
					}
				}
				closesocket(sock);
				delete[] user;
				//free(handleInfo);
				free(ioInfo);
				erase_lock.unlock();
				continue;
			}
			memcpy(message, ioInfo->wsaBuf.buf, BUF_SIZE);
			message[bytesTrans] = '\0';            // 문자열의 끝에 \0을 추가한다 (쓰레기 버퍼 방지)

			/* name 나누기
			char *ptr = strtok(message, "]");    // [] => ']'기준으로 나눈다.
			strcpy_s(handleInfo->name, ptr + 1);    // ]으로 나눈 name
			ptr = strtok(NULL, "]");            // ]으로 다시 나눈 message
			strcpy_s(message, ptr);                // message와 name이 나누어진다.
			*/
			user->Printname();
			printf("Sock[%d] : %s\n", sock, message);

			// 클라이언트가 가진 데이터 구조체의 정보를 바꾼다.
			// 이젠 서버가 쓰기를 행함


			free(ioInfo);
			std::vector<User*>::iterator iter;
			for (iter = Server::userlist.begin(); iter != Server::userlist.end(); ++iter)
			{
				ioInfo = (P_overlap)malloc(sizeof(Overlap));
				memset(&(ioInfo->overlapped), 0x00, sizeof(OVERLAPPED));
				int len = strlen(message);
				ioInfo->wsaBuf.len = len;
				strcpy(ioInfo->buffer, message);
				ioInfo->wsaBuf.buf = ioInfo->buffer;
				ioInfo->rwMode = WRITE;
				if (bytesTrans == 0)
				{
					closesocket(sock);
					//free(handleInfo);
					delete[] user;
					free(ioInfo);
					continue;
				}

				if (WSASend((*iter)->UserSock(), &(ioInfo->wsaBuf), 1, &bytesTrans, 0, &(ioInfo->overlapped), NULL) == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSA_IO_PENDING)
						ErrorHandling("WSASend() error");
				}
			}
			// 데이터 구조체 초기화, 쓰기 -> 읽기 모드로 변경

			/*ioInfo = (P_overlap)malloc(sizeof(Overlap));
			memset(&(ioInfo->overlapped), 0x00, sizeof(OVERLAPPED));
			ioInfo->wsaBuf.len = BUF_SIZE;
			ioInfo->wsaBuf.buf = ioInfo->buffer;*/
			ioInfo = (P_overlap)malloc(sizeof(Overlap));
			memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
			ioInfo->wsaBuf.len = BUF_SIZE;
			ioInfo->wsaBuf.buf = ioInfo->buffer;
			ioInfo->rwMode = READ;

			// 읽기 시작
			if (WSARecv(sock, &(ioInfo->wsaBuf), 1, &bytesTrans, (LPDWORD)&flags, &(ioInfo->overlapped), NULL) == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSA_IO_PENDING)
					ErrorHandling("WSASend() error");
			}
		}
		// 쓰기 상태
		else {
			cout << "Message Sent!\n";
			free(ioInfo);
		}
	}
	return 0;
}
// 일반적으로 이 파일을 무시하지만 미리 컴파일된 헤더를 사용하는 경우 유지합니다.

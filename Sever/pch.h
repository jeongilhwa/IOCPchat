
#ifndef PCH_H


#pragma comment(lib, "ws2_32.lib")
#pragma warning (disable : 4996)

#include <iostream>
#include <stdlib.h>
#include <process.h>
#include <winsock2.h>
#include <windows.h>
#include <vector>
#include <Ws2tcpip.h> //inet_pton 
#include <mutex>

#include "overlapped.h"
#include "iocp.h"
#include "User.h"


#define BUF_SIZE 1024
#define NAME_SIZE 20
#define READ 3
#define WRITE 5
#define CLIENT_SIZE 3000
#define PORT_NUM  3800

using std::cout;
using std::endl;
using std::vector;
void ErrorHandling(const char *message);





#define PCH_H

// TODO: 여기에 미리 컴파일하려는 헤더 추가

#endif //PCH_H

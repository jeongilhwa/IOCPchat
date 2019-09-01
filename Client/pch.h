
#ifndef PCH_H

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <process.h>

// vs warning and winsock error 
#pragma comment(lib, "ws2_32.lib")
#pragma warning (disable : 4996)
#define BUF_SIZE 1024
#define NAME_SIZE 20

using std::cout;
using std::cin;
using std::endl;

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];




#define PCH_H

#endif //PCH_H

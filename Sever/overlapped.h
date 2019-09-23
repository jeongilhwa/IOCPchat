#pragma once
#include"pch.h"
typedef struct Overlap   // buffer info
{
	OVERLAPPED overlapped;
	WSABUF wsaBuf;
	char buffer[BUF_SIZE];
	INT rwMode;    // READ or WRITE
}*P_overlap;


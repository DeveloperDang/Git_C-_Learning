#pragma once
#include "Public.h"
#include <stdlib.h>
//#pragma comment(lib, "Ws2_32.lib")
const int BUFFERSIZE = 1024;


class FileSocket {
public:
	FileSocket();
	~FileSocket();
	int MyRequest(unsigned char *SrcBuffer, int SrcLen, unsigned char *DstBuffer, int DstLen);

protected:

private:
	SOCKET m_sock;
	char m_sndBuffer[BUFFERSIZE];
	char m_rcvBuffer[BUFFERSIZE];
};
#include "FileSocket.h"
//#include "Public.h"
#include <iostream>
using namespace std;

FileSocket::FileSocket()
{
	m_sock = 0;
	memset(m_sndBuffer, 0x00, sizeof(m_sndBuffer));
	memset(m_rcvBuffer, 0x00, sizeof(m_rcvBuffer));
}

FileSocket::~FileSocket()
{

}

int FileSocket::MyRequest(unsigned char *SrcBuffer, int SrcLen, unsigned char *DstBuffer, int DstLen)
{
	int len = 0;
	//建立客户端socket
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	//服务器地址
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(SERVER_IP.c_str());
	inet_pton(AF_INET, SERVER_IP.c_str(), (void*)&addrSrv.sin_addr.S_un.S_addr);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(SERVER_PORT);

	connect(m_sock, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	Log(LOGFILE, LOG_MODE, __FILE__, __LINE__, GetCurrentThreadId(), "start sending....") ;
	strncpy(m_sndBuffer, (const char *)SrcBuffer, SrcLen);
	
	len = send(m_sock, m_sndBuffer, SrcLen, 0);
	if (len < 0)
	{
		Log(LOGFILE, LOG_MODE, __FILE__, __LINE__, GetCurrentThreadId(), "发往服务器报文失败，错误码为:%d", len);
	}

	len = recv(m_sock, m_rcvBuffer, strlen(m_rcvBuffer), 0);
	if (len < 0)
	{
		Log(LOGFILE, LOG_MODE, __FILE__, __LINE__, GetCurrentThreadId(), "收取服务器报文失败，错误码为:%d", len);
	}

	Log(LOGFILE, LOG_MODE, __FILE__, __LINE__, GetCurrentThreadId(), "收取服务器报文为:%s", m_rcvBuffer);
	return 0;
}
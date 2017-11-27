#include "AmHttpSocket.h"
#include "Public.h"
#include "FileSocket.h"
#include <fstream>
#include <iostream>


static DWORD WINAPI ThreadFunc(LPVOID param)
{
	localMSg *msg = (localMSg*)param;
	AmHttpSocket h;
	FileSocket fs;
	TCHAR *page = 0;
	string pathName = STOCK_FILEPATH + msg->filename + ".txt";
	ofstream f(pathName, ios::app);
	f << "     " << "��Ʊ����" << "  " << "���տ��̼�" << "  " << "�������̼�" << "  " << "��ǰ�۸�" << "  "
		<< "������߼�" << "  " << "������ͼ�" << "  " << "�����" << "  " << "������" << "  "
		<< "�ɽ��Ĺ�Ʊ��" << "  " << "�ɽ����" << "  " << "��һ" << "  " << "��һ" << "  "
		<< "���" << "  " << "���" << "  " << "����" << "  " << "����" << "  "
		<< "����" << "  " << "����" << "  " << "����" << "  " << "����" << "  "
		<< "��һ" << "  " << "��һ" << "  " << "����" << "  " << "����" << "  "
		<< "����" << "  " << "����" << "  " << "����" << "  " << "����" << "  "
		<< "����" << "  " << "����" << "  " << "����" << "  " << "ʱ��" << "  " << "\n";
	while (1)
	{
		page = h.GetPage((msg->sendmsg).c_str());
		if (!page) {
			Log(LOGFILE, LOG_MODE, __FILE__, __LINE__, GetCurrentThreadId(), "�̻߳�ȡ����ʧ�ܣ����ͱ���Ϊ��%s", msg->sendmsg);
			break;
		}
		vector<string> info;
		vector<string>::iterator it;
		//���յ����ص���־
		string rcvMsg = (std::string)page;
		fs.MyRequest((unsigned char *)rcvMsg.c_str(), rcvMsg.length(),NULL,0);


		h.ProcMsg(rcvMsg);
		info = h.split(rcvMsg, ",");
		for (it = info.begin(); it != info.end(); ++it)
		{
			f << "     " << *it;
		}
		f << "\n";
		page = 0;
		Sleep(300000);
	}
	f.close();
	delete msg;
	return 0;
}


int CALLBACK WinMain(
	_In_  HINSTANCE hInstance,
	_In_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,
	_In_  int nCmdShow
)
{
	AmHttpSocket h;
	TCHAR *head = 0, *page = 0;
	vector<string> info;
	vector<string>::iterator it;

	DWORD dwThreadID[2048];
	HANDLE handleFirst[2048];
	memset(dwThreadID, 0x00, sizeof(dwThreadID));
	int count = 0;
	vector<string>::iterator iter = STOCK_SH.begin();
	for (; iter != STOCK_SH.end(); ++iter)
	{
		localMSg *sendmsg = new localMSg;
		sendmsg->filename = "sh" + *iter;
		sendmsg->sendmsg = SENDFORMAT + "sh" + *iter;
		handleFirst[count] = CreateThread(NULL, 0, ThreadFunc, sendmsg, 0, &(dwThreadID[count]));
		if (!handleFirst[count])
		{
			Log(LOGFILE, LOG_MODE, __FILE__, __LINE__, 0,"�̴߳���ʧ�ܣ�");
		}
		count++;
	}
	Log(LOGFILE, LOG_MODE, __FILE__, __LINE__, GetCurrentThreadId(), "�����̴߳����ɹ���");
	count = 0;
	for (vector<string>::iterator it = STOCK_SH.begin(); it != STOCK_SH.end(); ++it)
	{
		WaitForSingleObject(handleFirst[count], INFINITE);//�ȴ��̷߳���
		CloseHandle(handleFirst[count]);//���Ĭ��ֵ2 �����1���̺߳���ִ������ͷ���Դ��
		count++;
	}

	Log(LOGFILE, LOG_MODE, __FILE__, __LINE__, GetCurrentThreadId(), "�����̻߳ع�ɹ���");
	return 0;
}

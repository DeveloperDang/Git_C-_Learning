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
	f << "     " << "股票名字" << "  " << "今日开盘价" << "  " << "昨日收盘价" << "  " << "当前价格" << "  "
		<< "今日最高价" << "  " << "今日最低价" << "  " << "竞买价" << "  " << "竞卖价" << "  "
		<< "成交的股票数" << "  " << "成交金额" << "  " << "买一" << "  " << "买一" << "  "
		<< "买二" << "  " << "买二" << "  " << "买三" << "  " << "买三" << "  "
		<< "买四" << "  " << "买四" << "  " << "买五" << "  " << "买五" << "  "
		<< "卖一" << "  " << "卖一" << "  " << "卖二" << "  " << "卖二" << "  "
		<< "卖三" << "  " << "卖三" << "  " << "卖四" << "  " << "卖四" << "  "
		<< "卖五" << "  " << "卖五" << "  " << "日期" << "  " << "时间" << "  " << "\n";
	while (1)
	{
		page = h.GetPage((msg->sendmsg).c_str());
		if (!page) {
			Log(LOGFILE, LOG_MODE, __FILE__, __LINE__, GetCurrentThreadId(), "线程获取报文失败，发送报文为：%s", msg->sendmsg);
			break;
		}
		vector<string> info;
		vector<string>::iterator it;
		//接收到返回的日志
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
			Log(LOGFILE, LOG_MODE, __FILE__, __LINE__, 0,"线程创建失败！");
		}
		count++;
	}
	Log(LOGFILE, LOG_MODE, __FILE__, __LINE__, GetCurrentThreadId(), "所有线程创建成功！");
	count = 0;
	for (vector<string>::iterator it = STOCK_SH.begin(); it != STOCK_SH.end(); ++it)
	{
		WaitForSingleObject(handleFirst[count], INFINITE);//等待线程返回
		CloseHandle(handleFirst[count]);//句柄默认值2 这里减1，线程函数执行完后释放资源。
		count++;
	}

	Log(LOGFILE, LOG_MODE, __FILE__, __LINE__, GetCurrentThreadId(), "所有线程回归成功！");
	return 0;
}

#pragma once

#include <tchar.h>
#include <windows.h>
#include <wininet.h>
#include <string>
#include <vector>

using namespace std;
#pragma comment( lib, "Wininet.lib" ) 


class AmHttpSocket {
public:
	AmHttpSocket();
	~AmHttpSocket();
	int GetPageStatusCode(); //get the HTTP statuscode for the last received page
	TCHAR* GetHeaders(const TCHAR *url); //return a pointer th the headers from an url
	char* GetPage(const TCHAR *url, bool Post = false, const char *PostData = NULL, int PostDataLength = -1);
	//get a page, if post is false, HTTP GET is used othervise HTTP POST is used. 
	//if PostDataLength is -1 the data must be NULL terminated...

	std::vector<std::string> split(const std::string &s, const std::string &seperator);
	int ProcMsg(string &orginalStr);
protected:
	bool PostUrl(const TCHAR *url, const char *PostData, int PostDataLength = -1);
	//open a page using http post
	TCHAR* GetHeaderLine(TCHAR *s); //get a specific line from the headers
	bool OpenUrl(const TCHAR *url); //open a page using http get
	HINTERNET hIO, hIS, hCO;
	char *ReceivedData; //the internal databuffer
	TCHAR *Headers; //the internal headerbuffer
	int LastError; //internal statuscode...
private:


};
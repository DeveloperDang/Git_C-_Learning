
#include "AmHttpSocket.h"
#include "Public.h"


#define AgentName _T("Nimo Software HTTP Retriever 1.0")

//case insensitive search functions...
#ifdef UNICODE
#define _tcsustr wcsustr
#else
#define _tcsustr strustr
#endif
char* strustr(char *source, char *s);
wchar_t* wcsustr(wchar_t *source, wchar_t *s);

char* strustr(char *source, char *s)
{
	//make an uppercase copy af source and s
	char *csource = _strdup(source);
	char *cs = _strdup(s);
	_strupr(csource);
	_strupr(cs);
	//find cs in csource...
	char *result = strstr(csource, cs);
	if (result != NULL)
	{
		//cs is somewhere in csource
		int pos = result - csource;
		result = source;
		result += pos;
	}
	//clean up
	free(csource);
	free(cs);
	return result;
}

wchar_t* wcsustr(wchar_t *source, wchar_t *s)
{
	//make an uppercase copy af source and s
	wchar_t *csource = _wcsdup(source);
	wchar_t *cs = _wcsdup(s);
	_wcsupr(csource);
	_wcsupr(cs);
	//find cs in csource...
	wchar_t *result = wcsstr(csource, cs);
	if (result != NULL)
	{
		//cs is somewhere in csource
		int pos = result - csource;
		result = source;
		result += pos;
	}
	//clean up
	free(csource);
	free(cs);
	return result;
}
int Log(char *sLogName, int nLogMode, char * sFileName, int nLine, DWORD threadID, char *sFmt, ...);


AmHttpSocket::AmHttpSocket()
{
	hIO = NULL;
	hIS = NULL;
	hCO = NULL;
	ReceivedData = NULL;
	Headers = NULL;
	LastError = 0;
	hIO = InternetOpen(AgentName, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
}

AmHttpSocket::~AmHttpSocket()
{
	if (ReceivedData != NULL) free(ReceivedData);
	if (Headers != NULL) free(Headers);
	if (hIO != NULL) InternetCloseHandle(hIO);
	if (hIS != NULL) InternetCloseHandle(hIS);
	if (hCO != NULL) InternetCloseHandle(hCO);
}
//
bool AmHttpSocket::OpenUrl(const TCHAR *url)
{
	if (hIS != NULL) InternetCloseHandle(hIS);
	hIS = InternetOpenUrl(hIO, url, NULL, 0, HTTP_QUERY_DATE, 0);
	if (hIS != NULL) return true;
	else
	{
		LastError = GetLastError();
		return false;
	}
}

bool AmHttpSocket::PostUrl(const TCHAR *url, const char *PostData, int PostDataLength)
{
	//check length of postdata
	if (PostDataLength == -1)
		PostDataLength = strlen(PostData);
	//some variable that we need...
	URL_COMPONENTS uc;
	//let's split the url...
	uc.dwStructSize = sizeof(uc);
	uc.lpszScheme = NULL;
	uc.dwSchemeLength = 0;
	uc.lpszHostName = NULL;
	uc.dwHostNameLength = 1;
	uc.nPort = 0;
	uc.lpszUserName = NULL;
	uc.dwUserNameLength = 0;
	uc.lpszPassword = NULL;
	uc.dwPasswordLength = 0;
	uc.lpszUrlPath = NULL;
	uc.dwUrlPathLength = 1;
	uc.lpszExtraInfo = NULL;
	uc.dwExtraInfoLength = 0;
	InternetCrackUrl(url, _tcslen(url), 0, &uc);
	//post the data...
	if (hCO != NULL) InternetCloseHandle(hCO);
	TCHAR *HostName = _tcsdup(uc.lpszHostName);
	HostName[uc.dwHostNameLength] = '\0';
	TCHAR *FileName = _tcsdup(uc.lpszUrlPath);
	FileName[uc.dwUrlPathLength] = '\0';
	if (hIS != NULL) InternetCloseHandle(hIS); //if open, close the handle to the connection
	DWORD flags;
	if (uc.nPort == 80)
	{
		//we are talking plain http
		flags = INTERNET_FLAG_NO_CACHE_WRITE;
	}
	else
	{
		//we are talking secure https
		flags = INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_SECURE |
			INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID;
	}
	TCHAR headers[] = _T("Content-Type: application/x-www-form-urlencoded"); //content type for post...
	TCHAR szAccept[] = _T("*/*"); //we accept everything...
	LPTSTR AcceptTypes[2] = { 0 };
	AcceptTypes[0] = szAccept;
	hCO = InternetConnect(hIO, HostName, uc.nPort, _T(""), _T(""), INTERNET_SERVICE_HTTP, INTERNET_FLAG_NO_CACHE_WRITE, 0);
	hIS = HttpOpenRequest(hCO, _T("POST"), FileName, NULL, NULL, (LPCTSTR*)AcceptTypes, flags, 0);
	if (!HttpSendRequest(hIS, headers, _tcslen(headers), (TCHAR*)PostData, PostDataLength))
	{
		LastError = GetLastError();
		free(HostName);
		free(FileName);
		return false;
	}
	free(HostName);
	free(FileName);
	return true;
}

TCHAR* AmHttpSocket::GetHeaders(const TCHAR *url)
{
	//did we get an url?
	if (url == NULL)
	{
		LastError = -1;
		return NULL;
	}
	//open the url...
	OpenUrl(url);
	//delete old headers...
	if (Headers != NULL) free(Headers);
	Headers = (TCHAR*)calloc(1, sizeof(TCHAR));
	//get the size headers
	DWORD d = 1, d2 = 0;
	int i = HttpQueryInfo(hIS, HTTP_QUERY_RAW_HEADERS, Headers, &d, &d2);
	//alloc some space for the headers
	Headers = (TCHAR*)realloc(Headers, d * sizeof(TCHAR));
	if (!HttpQueryInfo(hIS, HTTP_QUERY_RAW_HEADERS, Headers, &d, &d2)) return NULL;
	return Headers;
}
//
char* AmHttpSocket::GetPage(const TCHAR *url, bool Post, const char *PostData, int PostDataLength)
{
	//did we get an url?
	if (url == NULL)
	{
		LastError = -1;
		return NULL;
	}
	//get the page and store it in ReceivedData...
	if (Post)
	{
		//use http post...
		if (!PostUrl(url, PostData, PostDataLength)) return NULL;
	}
	else
	{
		//use http get
		if (!OpenUrl(url)) return NULL;
	}
	const int rdsize = 8192;
	char mr[rdsize];
	DWORD rd;
	int curpos = 0;
	if (ReceivedData != NULL) free(ReceivedData);
	ReceivedData = (char*)calloc(rdsize + 1, sizeof(char));
	while (InternetReadFile(hIS, mr, rdsize - 1, &rd))
	{
		if (rd == 0) break;
		mr[rd] = '\0';
		curpos += rd;
		ReceivedData[curpos] = '\0';
		strcat(ReceivedData, mr);
		ReceivedData = (char*)realloc(ReceivedData, curpos + rdsize);
	}
	return ReceivedData;
}

TCHAR* AmHttpSocket::GetHeaderLine(TCHAR *s)
{
	//find a line in the headers that contains s, and return a pointer to the line...
	if (Headers == NULL) return NULL;
	TCHAR *ts = Headers;
	if (_tcsustr(ts, s) != NULL) return ts;
	while (1)
	{
		if (*ts == '\0' && ts[1] == '\0') break;
		if (*ts == '\0')
		{
			ts++;
			if (_tcsustr(ts, s) != NULL) return ts;
		}
		else ts++;
	}
	return NULL;
}

int AmHttpSocket::GetPageStatusCode()
{
	//get the correct header line
	TCHAR *s = GetHeaderLine(_T("http"));
	if (s == NULL) return 0; //no headers
							 //find the 3 digit code...
	if (_tcslen(s) < 3) return 0; //some error,  the string is too short...
	while (!(isdigit(s[0]) && isdigit(s[1]) && isdigit(s[2])))
	{
		if (s[3] == '\0') return 0; //we have reached the end of the string, without finding the number...
		s++;
	}
	//make a copy of s, and return the code
	TCHAR *code = _tcsdup(s);
	code[3] = '\0'; //remove all text after the 3 digit response code
	int result = _ttoi(code);
	free(code);
	return result;
}


std::vector<std::string> AmHttpSocket::split(const string &s, const string &seperator) {
	vector<string> result;
	typedef string::size_type string_size;
	string_size i = 0;

	while (i != s.size()) {
		//找到字符串中首个不等于分隔符的字母；
		int flag = 0;
		while (i != s.size() && flag == 0) {
			flag = 1;
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[i] == seperator[x]) {
					++i;
					flag = 0;
					break;
				}
		}

		//找到又一个分隔符，将两个分隔符之间的字符串取出；
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0) {
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[j] == seperator[x]) {
					flag = 1;
					break;
				}
			if (flag == 0)
				++j;
		}
		if (i != j) {
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}

int AmHttpSocket::ProcMsg(string &orginalStr)
{
	size_t len = orginalStr.length();
	size_t pos = orginalStr.find("=", 0);
	string msg = orginalStr.substr(pos+2, len - pos - 6);
	Log(LOGFILE, LOG_MODE, __FILE__, __LINE__, GetCurrentThreadId(), "原始报文为:%s", orginalStr.c_str());
	Log(LOGFILE, LOG_MODE, __FILE__, __LINE__, GetCurrentThreadId(), "当前报文为:%s", msg.c_str());

	orginalStr = msg;
	return 0;

}

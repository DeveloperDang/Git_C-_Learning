#include "Public.h"
#include <atlbase.h>
#include <limits.h>
#include <time.h>


/*日志文件*/
int Log(char *sLogName, int nLogMode, char * sFileName, int nLine, DWORD threadID, char *sFmt, ...)
{
	FILE	*fp;
	time_t	lTime;
	char	sLogTime[128];
	char	acBakFileName[128];
	struct tm	*tTmLocal;
	va_list	ap;
	struct stat	statbuf;
	int iRet;

	lTime = time(NULL);
	tTmLocal = localtime(&lTime);
	strftime(sLogTime, sizeof(sLogTime), "%Y-%m-%d %H:%M:%S", tTmLocal);
	iRet = stat(sLogName, &statbuf);
	if (iRet == 0 && statbuf.st_size >= 1024 * 1024 * 10)
	{
		memset(acBakFileName, 0, sizeof(acBakFileName));
		strcpy(acBakFileName, sLogName);
		strcat(acBakFileName, ".");
		strftime(acBakFileName + strlen(acBakFileName), sizeof(sLogTime), "%Y%m%d%H%M%S", tTmLocal);
		iRet = rename(sLogName, acBakFileName);
		if (iRet<0)
			return errno;
	}

	fp = fopen(sLogName, "a+");
	if (fp == NULL)
		return (errno);
	fprintf(fp, "[%s][%-20.20s][%04d][%d]", sLogTime, sFileName, nLine, threadID);
	va_start(ap, sFmt);
	vfprintf(fp, sFmt, ap);
	va_end(ap);
	fprintf(fp, "\n");
	fflush(fp);
	fclose(fp);
	return (0);
}

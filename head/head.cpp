//**********************************************************
//
//	Module Name:
//		head.cpp
//
//	Description:
//		Adds header to the file.
//
//	Author:
//		Suraj K
//
//	History:
//		Date: 08 Aug, 2015
//		Comment: Created.
//
//**********************************************************

#include "head.h"
#include "../include/cmnmcros.h"
#include "../include/log.h"

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char *g_pszLogFileName = "head.log";

const char *pcszHeader = "\
//**********************************************************\n\
//\n\
//	Module Name:\n\
//		%s\n\
//\n\
//	Description:\n\
//		\n\
//\n\
//	Author:\n\
//		Suraj K\n\
//\n\
//	History:\n\
//		Date: %s\n\
//		Comment: Created.\n\
//\n\
//**********************************************************\n\n\
";


int
main(int argc, char* argv[])
{
	int iRet;
	int iLen;
	int iFdRead;
	time_t tNow;
	int iFdWrite;
	int iHeadSize;
	char szHeader[2048];
	char szFileChunk[2048];
	char szBackupFile[2048];
	const struct tm *pctmNow;

	INIT_LOGGER

	if (2 != argc)
	{
		LOG("Enter a file name to add the header");

		return EINVAL;
	}

	LOG("Opening file (%s)", argv[1])

	//
	//	Add header to the file.
	//
	iFdWrite = open(argv[1], O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if (-1 == iFdWrite)
	{
		LOG("open failed for %s", argv[1]);
		return errno;
	}

	tNow = time(NULL);
	pctmNow = localtime(&tNow);

	iRet = strftime(szBackupFile, ARRAY_SIZE(szBackupFile), "%d %b, %Y", pctmNow);
	if (0 == iRet)
	{
		LOG("strftime failed. errno %d", errno);
		return errno;
	}

	iRet = snprintf(szHeader, ARRAY_SIZE(szHeader), pcszHeader, argv[1], szBackupFile);
	if (iRet < 0 || ARRAY_SIZE(szHeader) <= iRet)
	{
		LOG("snprintf failed errno %d, iRet %d", errno, iRet);
		return errno;
	}

	iHeadSize = strlen(szHeader);

	//
	//	Check if the header is present.
	//
	iLen = read(iFdWrite, szFileChunk, 10);
	if (iLen < 0)
	{
		LOG("read failed. %d", iLen);

		close(iFdWrite);
		return errno;
	}

	if (
		szFileChunk[0] == '/'
	&& szFileChunk[1] == '/'
	&& szFileChunk[2]=='*'
	&& szFileChunk[3]=='*'
	)
	{
		//
		//	Header is already present.
		//
		LOG("Header already present");

		close(iFdWrite);
		return 0;
	}

	lseek(iFdWrite, 0, SEEK_SET);

	//
	//	Modifying the file.
	//	Take the backup of the file.
	//
	iRet = snprintf(szBackupFile, ARRAY_SIZE(szBackupFile), "%s.bak", argv[1]);
	if (iRet < 0)
	{
		LOG("snprintf for backup file failed");

		close(iFdWrite);
		return errno;
	}

	iRet = Backup(argv[1], szBackupFile);
	if (0 != iRet)
	{
		LOG("Backup failed from (%s) to (%s).", argv[1], szBackupFile);

		close(iFdWrite);
		return iRet;	
	}

	iFdRead = open(szBackupFile, O_RDONLY);
	if (-1 == iFdRead)
	{
		LOG("open failed for (%s).", szBackupFile);

		close(iFdWrite);
		return ENOENT;
	}

	iLen = write(iFdWrite, szHeader, iHeadSize);
	if (iLen != iHeadSize)
	{
		LOG("write failed.");

		close(iFdRead);
		close(iFdWrite);

		return errno;
	}

	do
	{
		iLen = read(iFdRead, szFileChunk, ARRAY_SIZE(szFileChunk));
		if (iLen < 0)
		{
			LOG("read failed in loop");

			Restore(szBackupFile, argv[1]);
			close(iFdRead);
			close(iFdWrite);

			return errno;
		}

		if (0 == iLen)
		{
			break;
		}

		iRet = write(iFdWrite, szFileChunk, iLen);
		if (iRet != iLen)
		{
			LOG("write failed in loop");
			Restore(szBackupFile, argv[1]);

			close(iFdRead);
			close(iFdWrite);

			return errno;
		}
	}	while(0 != iLen);

	//
	//	Delete backup file.
	//
	remove(szBackupFile);
	return 0;
}


int
Backup(
	const char *pcszFrom,
	const char *pcszTo
	)
{
	int iRet;
	char szBuffer[2048];

	if (NULL == pcszFrom || NULL == pcszTo)
	{
		return EINVAL;
	}

	//
	//	Prepare the system copy command.
	//
	iRet = snprintf(szBuffer, ARRAY_SIZE(szBuffer), "cp %s %s", pcszFrom, pcszTo);
	if (iRet < 0)
	{
		return EINVAL;
	}

	system(szBuffer);
	return 0;		
}


int
Restore(
	const char *pcszFrom,
	const char *pcszTo
	)
{
	int iRet;
	char szBuffer[2048];

	if (NULL == pcszFrom || NULL == pcszTo)
	{
		return EINVAL;
	}

	//
	//	Prepare the system move command.
	//
	iRet = snprintf(szBuffer, ARRAY_SIZE(szBuffer), "mv %s %s", pcszFrom, pcszTo);
	if (iRet < 0)
	{
		return errno;
	}

	system(szBuffer);
	return 0;
}

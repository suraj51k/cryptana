//**********************************************************
//	Author:	Suraj K
//
//	Module Name: log.cpp
//
//	Description: The looger module.
//
//	History:
//		Date: 8 Aug, 2015
//		Comment: Created.
//
//**********************************************************

///////////////////////////////////////////////////////////
//	H E A D E R S
//////////////////////////////////////////////////////////

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <errno.h>
#include "../include/log.h"
#include "../include/macros.h"


///////////////////////////////////////////////////////////
//	M A C R O S
//////////////////////////////////////////////////////////

#define MAX_BUFF_SIZE								2048
#define	ENABLE_LOGGER_LOG							0

extern char *g_pszLogFileName;


///////////////////////////////////////////////////////////
//	C L A S S  D E F I N I T I O N
//////////////////////////////////////////////////////////

CLogger::CLogger(
	char *pszFunName
	)
{
	int iFd;
	int iLen;
	char szMsg[MAX_BUFF_SIZE];

	iLen = strlen(pszFunName);
	m_pszFunName = (char*) malloc(iLen + 1);
	if (NULL == m_pszFunName)
	{
		throw;
	}

	strcpy(m_pszFunName, pszFunName);

	//
	//	Write to file.									
	//
	if (NULL != g_pszLogFileName)
	{
		iFd = open(g_pszLogFileName, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
		if (-1 == iFd)		
		{
			return;
		}

		snprintf(szMsg, ARRAY_SIZE(szMsg), "%s Enter\n", m_pszFunName);
		write(iFd, szMsg, strlen(szMsg));
		close(iFd);
	}
	else
	{
		printf("%s Enter.\n", m_pszFunName);
	}
}


CLogger::~CLogger()
{
	int iFd;
	char szMsg[MAX_BUFF_SIZE];

	#if ENABLE_LOGGER_LOG
	printf("destructing logger\n");
	#endif

	//
	//	Write to file.			
	//
	if (NULL != g_pszLogFileName)
	{
		#if ENABLE_LOGGER_LOG
		printf("Writing to file. (%s)\n", g_pszLogFileName);
		#endif

		iFd = open(g_pszLogFileName, O_WRONLY | O_APPEND | O_CREAT);
		if (-1 == iFd)		
		{
			#if ENABLE_LOGGER_LOG
			printf("Open failed. %d. Exit. \n", errno);
			#endif

			return;
		}

		snprintf(szMsg, ARRAY_SIZE(szMsg), "%s Exit\n", m_pszFunName);
		write(iFd, szMsg, strlen(szMsg));
		close(iFd);

		#if ENABLE_LOGGER_LOG
		printf("File closed.\n");
		#endif
	}
	else
	{
		printf("%s Exit.\n", m_pszFunName);
	}

	#if ENABLE_LOGGER_LOG
	log("freeing fun name\n");
	#endif

	free(m_pszFunName);

	#if ENABLE_LOGGER_LOG
	log("fun name freed. Exit.\n");
	#endif
}


void
CLogger::log(const char *pcszMsg, ...)
{
	int iFd;
	va_list ArgList;
	char szMsg[MAX_BUFF_SIZE];
	char szBuffer[MAX_BUFF_SIZE];

	memset(szBuffer, ARRAY_SIZE(szBuffer), 0);

	va_start(ArgList, pcszMsg);
	vsnprintf(szBuffer, ARRAY_SIZE(szBuffer), pcszMsg, ArgList);
	va_end(ArgList);

	//
	//	Write to file.									
	//
	if (NULL != g_pszLogFileName)
	{
		iFd = open(g_pszLogFileName, O_WRONLY | O_APPEND | O_CREAT);
		if (-1 == iFd)		
		{
			return;
		}

		snprintf(szMsg, ARRAY_SIZE(szMsg), "%s %s\n", m_pszFunName, szBuffer);
		write(iFd, szMsg, strlen(szMsg));
		close(iFd);
	}
	else
	{
		printf("%s %s\n", m_pszFunName, szBuffer);
	}
}

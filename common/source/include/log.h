//**********************************************************
//	Author:	Suraj K
//
//	Module Name: log.h
//
//	Description: The logger module.
//
//	History:
//		Date: 8 Aug, 2015
//		Comment: Created.
//
//**********************************************************

#ifndef _LOGGER_H
#define	_LOGGER_H

///////////////////////////////////////////////////////////
//	H E A D E R S
//////////////////////////////////////////////////////////

#include <stdio.h>


///////////////////////////////////////////////////////////
//	C L A S S  D E C L A R A T I O N
//////////////////////////////////////////////////////////

extern char *g_pszLogFileName;

class CLogger
{
public:
	CLogger(
		char *pszFunName
		);

	~CLogger(
		);

	void
	log(
		const char *,
		...
		);

private:
	char *m_pszFunName;

};

#endif	// _LOGGER_H

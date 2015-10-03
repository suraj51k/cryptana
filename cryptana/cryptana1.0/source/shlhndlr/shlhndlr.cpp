//**********************************************************
//
//	Module Name:
//		shlhndlr.cpp
//
//	Description:
//		Handels the shell activities.
//
//	Author:
//		Suraj K
//
//	History:
//		Date: 09 Aug, 2015
//		Comment: Created.
//
//**********************************************************

////////////////////////////////////////////////////////////
//	H E A D E R
////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "shlhndlr.h"
#include "../../../../common/source/include/macros.h"
#include "debug.h"


////////////////////////////////////////////////////////////
//	M A C R O S
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//	S T R U C T U R E S
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//	C L A S S  D E C L A R A T I O N
////////////////////////////////////////////////////////////

CShellHndler::CShellHndler(
	)
{
	m_pNodeInfo = NULL;
}

CShellHndler::~CShellHndler(
	)
{

}
	
int
StartShell(
	void *pParent
	)
{

}


//****************************************************
//
//	Function:
//		Register
//
//	Description:
//		This function registers the shell
//		commmands.
//
//	Parameters:
//		[IN] void *pParent
//		The parent to which this sub-list
//		should be attached.
//
//****************************************************
int
CShellHndler::Register(
	const REG_INFO *pcRegInfo
	)
{
	int iRet;	
	REG_INFO *pRegInfo;

	INIT_LOGGER(CShellHndler::Register)

	if (NULL == pRegInfo)
	{
		LOG("invalid param pRegInfo")
		return EINVAL;
	}

	try
	{
		pRegInfo = new REG_INFO;
	}
	catch(...)
	{
		iRet = errno;

		LOG("new failed for REG_INFO. errno:%d", errno)
		return iRet;
	}

	iRet = strlen(pRegInfo->pszCommand);
	pRegInfo->pszCommand = (char *) malloc(iRet);
	if (NULL == pRegInfo->pszCommand)
	{
		iRet = errno;

		delete pRegInfo;
		LOG("malloc failed, pszCommand")
		return iRet;
	}

	iRet = strlen(pRegInfo->pszHelpText);
	pRegInfo->pszHelpText = (char *) malloc(iRet);
	if (NULL == pRegInfo->pszHelpText)
	{
		iRet = errno;

		free(pRegInfo->pszCommand);
		delete pRegInfo;

		LOG("malloc failed, pszHelpText")
		return iRet;
	}

	if (NULL == m_pNodeInfo)
	{
		m_pNodeInfo = pRegInfo;
	}
	else
	{
		pRegInfo->pNext = m_pNodeInfo;
		m_pNodeInfo = pRegInfo; 
	}

	LOG("%s registered.", m_pNodeInfo->pszCommand);
	return 0;
}


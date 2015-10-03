//**********************************************************
//
//	Module Name:
//		shlhndlr.h
//
//	Description:
//		Handles the shell activities.
//
//	Author:
//		Suraj K
//
//	History:
//		Date: 09 Aug, 2015
//		Comment: Created.
//
//**********************************************************

#ifndef	_SHLHNDLR_H
#define	_SHLHNDLR_H

////////////////////////////////////////////////////////////
//	H E A D E R
////////////////////////////////////////////////////////////

#include <string>

using namespace std;


////////////////////////////////////////////////////////////
//	S T R U C T U R E S
////////////////////////////////////////////////////////////

typedef int (*PFN_SHELL_CALLBACK)(int iCount, ...);

typedef struct _structREG_INFO
{
	char					*pszCommand;
	char					*pszHelpText;
	PFN_SHELL_CALLBACK		pfnCallBack;
	struct _structREG_INFO	*pNext;

}	REG_INFO, *P_REG_INFO;


////////////////////////////////////////////////////////////
//	M A C R O S
////////////////////////////////////////////////////////////

class CShellHndler
{
public:

	CShellHndler(
		);

	~CShellHndler(
		);
	
	int
	StartShell(
		void *pParent
		);

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
	Register(
		const REG_INFO *pcRegInfo
		);

private:
	REG_INFO *m_pNodeInfo;

	int
	AcceptAndExecute(
		);

	int
	DisplayHelpText(
		);

};

#endif // _SHLHNDLR_H


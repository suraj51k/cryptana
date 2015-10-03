//**********************************************************
//
//	Module Name:
//		filetype.cpp
//
//	Description:
//		This module tries to identify the type of file
//		based on the signatures.
//
//	Author:
//		Suraj K
//
//	History:
//		Date: 23 Aug, 2015
//		Comment: Created.
//
//**********************************************************

////////////////////////////////////////////////////////////
//	H E A D E R S.
////////////////////////////////////////////////////////////

#include <errno.h>
#include "filetype.h"
#include "../../../../../common/source/include/log.h"
#include "../debug.h"


////////////////////////////////////////////////////////////
//	M A C R O S.
////////////////////////////////////////////////////////////

#define	ERROR_FILE_TYPE_NOT_FOUND					9000

////////////////////////////////////////////////////////////
//	C L A S S  D E F I N I T I O N S
////////////////////////////////////////////////////////////

CFileType::CFileType(
	)
{
}


CFileType::~CFileType(
	)
{
}


int
CFileType::ApplyAlgorithm(
	const unsigned char *pcuchBuffer,
	unsigned int uiBuffer,
	void *pvParam
	)
{
	INIT_LOGGER(CFileType::ApplyAlgorithm)

	if (NULL == pcuchBuffer || NULL == pvParam)
	{
		LOG("Invalid params.")
		return EINVAL;
	}

	//
	//	Read the file contents if filename is specified.
	//

	//
	//	Load the signatures.
	//

	//
	//	Apply Signatures.
	//
	
	LOG("Exit.")
	return 0;
}


int
Write(
	const char *pcszFileName
	)
{

}


int
Write(
	unsigned char *puchBuff,
	unsigned int *puicbBuff
	)
{

}


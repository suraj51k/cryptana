//**********************************************************
//
//	Module Name:
//		base64.cpp
//
//	Description:
//		Contains function to check if file/content
//		is base 64 encoded.
//
//	Author:
//		Suraj K
//
//	History:
//		Date: 19 Sep, 2015
//		Comment: Created.
//
//**********************************************************

////////////////////////////////////////////////////////////
//	H E A D E R S.
////////////////////////////////////////////////////////////

#include <errno.h>
#include "base64.h"
#include "../debug.h"


////////////////////////////////////////////////////////////
//	S T R U C T U R E S.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//	C L A S S  D E F I N I T I O N S
////////////////////////////////////////////////////////////

CBase64::CBase64()
{

}


CBase64::~CBase64()
{

}


int
CBase64::ApplyAlgorithm(
	const unsigned char *pcuchBuffer,
	unsigned int uicchBuffer,
	BASE64 *pBase64
	)
{
	int iVal;
	unsigned int uiLoop;

	INIT_LOGGER(CBase64::ApplyAlgorithm)

	if (0 == pcuchBuffer || 0 == pBase64)
	{
		LOG("Parameter validation failed. pcuchBuffer or pBase64 is NULL. Exit");
		return EINVAL;
	}

	//
	//	Check if size is multiple of 4.
	//
	if (0 != (uicchBuffer%4))
	{
		LOG("The input buffer is not in size of 4. Hence not base 64 content");
		LOG("Size = %d", uicchBuffer);

		pBase64->bIsBase64 = false;
		return 0;
	}

	LOG("Data is in multiple of 4. Checking further conditions.");

	for (uiLoop = 0; uiLoop < uicchBuffer; uiLoop++)
	{
		iVal = pcuchBuffer[uicchBuffer];

		if (iVal >= 'A' && iVal <= 'Z')
		{
			continue;
		}

		if (iVal >= 'a' && iVal <= 'z')
		{
			continue;
		}

		if (iVal == '+' || iVal == '/')
		{
			continue;
		}

		if (iVal == '=')
		{
			LOG("character is %c", iVal);
			LOG("Position: %d", (uicchBuffer - uiLoop));
			if (2 == uicchBuffer - uiLoop || 1 == uicchBuffer - uiLoop)
			{
				continue;
			}
		}

		pBase64->bIsBase64 = false;
		return 0;
	}

	pBase64->bIsBase64 = true;
	return 0;
}


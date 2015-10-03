//**********************************************************
//
//	Module Name:
//		base64.h
//
//	Description:
//		Contains functions to detect if the given input
//		is base64 encoded.
//
//	Author:
//		Suraj K
//
//	History:
//		Date: 19 Sep, 2015
//		Comment: Created.
//
//**********************************************************

#ifndef	_BASE64_
#define	_BASE64_

////////////////////////////////////////////////////////////
//	H E A D E R S.
////////////////////////////////////////////////////////////

#include "algorithms.h"


////////////////////////////////////////////////////////////
//	S T R U C T U R E S.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//	C L A S S  D E C L A R A T I O N S
////////////////////////////////////////////////////////////

//**********************************************************
//
//	Class Name:
//		CBase64
//
//	Description:
//		This class finds if the given input is base64
//		encoded.
//
//**********************************************************
class CBase64:AbsAlgorithm
{
public:

	CBase64(
		);

	~CBase64(
		);

	int
	ApplyAlgorithm(
		const unsigned char *pcuchBuffer,
		unsigned int uicchBuffer,
		void *vpParam
		);

	int
	Write(
		const char *pcszFileName
		);

	int
	Write(
		unsigned char *puchBuff,
		unsigned int *puicbBuff
		);


};

#endif

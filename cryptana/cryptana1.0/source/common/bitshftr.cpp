//**********************************************************
//
//	Module Name:
//		bitshftr.cpp
//
//	Description:
//		This file contains bit shifting operations.
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

#include "../include/bitshftr.h"


////////////////////////////////////////////////////////////
//	F U N C T I O N  D E F I N I T I O N S
////////////////////////////////////////////////////////////

CBitShifter::CBitShifter(
	)
{
}

CBitShifter::~CBitShifter(
	)
{

}

unsigned char
CBitShifter::RotateRight(
	unsigned char uchToken,
	unsigned int uiCount
	)
{
	int iLoop;
	unsigned char uchTemp;

	for(iLoop = 0; iLoop < uiCount; iLoop++)
	{
		uchTemp = uchToken & 0x01;
		uchToken = uchToken >> 1;
		
		uchTemp = uchTemp << 7;
		uchToken = uchToken | uchTemp;
	}

	return uchToken;
}


unsigned char
CBitShifter::RotateLeft(
	unsigned char uchToken,
	unsigned int uiCount
	)
{
	int iLoop;
	unsigned char uchTemp;

	for(iLoop = 0; iLoop < uiCount; iLoop++)
	{
		uchTemp = uchToken & 0x80;
		uchToken = uchToken << 1;
		
		uchTemp = uchTemp >> 7;
		uchToken = uchToken | uchTemp;
	}

	return uchToken;
}


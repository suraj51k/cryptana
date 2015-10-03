//**********************************************************
//
//	Module Name:
//		bitshftr.h
//
//	Description:
//		This file contains the bit shifting operations.
//
//	Author:
//		Suraj K
//
//	History:
//		Date: 09 Aug, 2015
//		Comment: Created.
//
//**********************************************************

#ifndef _BITSHFTR_H
#define	_BITSHFTR_H

////////////////////////////////////////////////////////////
//	H E A D E R
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
//	C L A S S  D E C L A R A T I O N S
////////////////////////////////////////////////////////////

class CBitShifter
{
	public:

	CBitShifter(
		);

	~CBitShifter(
		);

	unsigned char
	RotateRight(
		unsigned char uchToken,
		unsigned int uiCount
		);

	unsigned char
	RotateLeft(
		unsigned char uchToken,
		unsigned int uiCount
		);

	private:
};

#endif // _BITSHFTR_H

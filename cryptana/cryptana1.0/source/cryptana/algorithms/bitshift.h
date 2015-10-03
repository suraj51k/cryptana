//**********************************************************
//
//	Module Name:
//		bitshift.h
//
//	Description:
//		Applies bit rotation on each byte of the given
//		data.
//
//	Author:
//		Suraj K
//
//	History:
//		Date: 09 Aug, 2015
//		Comment: Created.
//
//**********************************************************

#ifndef _BITSHIFT_H
#define	_BITSHIFT_H

////////////////////////////////////////////////////////////
//	H E A D E R
////////////////////////////////////////////////////////////

#include "algorithm.h"


////////////////////////////////////////////////////////////
//	S T R U C T U R E S
////////////////////////////////////////////////////////////

typedef struct _structBIT_SHIFT_ALGO_PARAM
{
	unsigned int uiShiftCount;

}	BIT_SHIFT_ALGO_PARAM, *P_BIT_SHIFT_ALGO_PARAM;


////////////////////////////////////////////////////////////
//	C L A S S  D E C L A R A T I O N
////////////////////////////////////////////////////////////

//**********************************************************
//
//	Class Name:
//		CBitShiftAlgo
//
//	Description:
//		This class applies the bit shifting algorithm
//
//**********************************************************
class CBitShiftAlgo:AbsAlgorithm
{
public:
	CBitShiftAlgo(
		);

	~CBitShiftAlgo(
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

private:

};

#endif // _BITSHIFT_H

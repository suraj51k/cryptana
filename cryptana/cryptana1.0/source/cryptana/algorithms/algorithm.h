//**********************************************************
//
//	Module Name:
//		algorithm.h
//
//	Description:
//		This is an abstract class for all the algorithms.		
//
//	Author:
//		Suraj K
//
//	History:
//		Date: 09 Aug, 2015
//		Comment: Created.
//
//**********************************************************

#ifndef _ALGORITHMS_H
#define	_ALGORITHMS_H

////////////////////////////////////////////////////////////
//	H E A D E R
////////////////////////////////////////////////////////////

class AbsAlgorithm
{
public:
	AbsAlgorithm(
		);

	~AbsAlgorithm(
		);

	virtual int
	ApplyAlgorithm(
		const unsigned char *pcuchBuffer,
		unsigned int uiBuffer,
		void *pvParam
		) = 0;

	virtual int
	Write(
		const char *pcszFileName
		) = 0;

	virtual int
	Write(
		unsigned char *puchBuff,
		unsigned int *puicbBuff
		) = 0;

protected:
	unsigned int m_uiSize;
	unsigned char *m_puchBuffer;

};

#endif	// _ALGORITHMS_H

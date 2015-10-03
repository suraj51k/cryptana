//**********************************************************
//
//	Module Name:
//		bitshift.cpp
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

////////////////////////////////////////////////////////////
//	H E A D E R
////////////////////////////////////////////////////////////

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include "bitshift.h"
#include "../../include/bitshftr.h"
#include "../debug.h"


////////////////////////////////////////////////////////////
//	D E F I N I T I O N S
////////////////////////////////////////////////////////////

CBitShiftAlgo::CBitShiftAlgo(
	)
{

}


CBitShiftAlgo::~CBitShiftAlgo(
	)
{
	
}


int
CBitShiftAlgo::ApplyAlgorithm(
	const unsigned char *pcuchBuffer,
	unsigned int uicchBuffer,
	void *pvParam
	)
{
	int iLoop;
	CBitShifter *pBitShftr;
	BIT_SHIFT_ALGO_PARAM *pParam;

	INIT_LOGGER(CBitShiftAlgo::ApplyAlgorithm)

	free(m_puchBuffer);

	if (NULL == pcuchBuffer || NULL == pvParam)
	{
		LOG("Invalid param.");

		return EINVAL;
	}

	LOG("Aplying CBitShiftAlgo...")
	pParam = (BIT_SHIFT_ALGO_PARAM *) pvParam;

	m_puchBuffer = (unsigned char*) malloc(uicchBuffer);
	if (NULL == m_puchBuffer)
	{
		LOG("malloc failed. Exit.");
		return errno;
	}

	memcpy(m_puchBuffer, pcuchBuffer, uicchBuffer);

	//
	//	Rotating bits.
	//
	try
	{
		pBitShftr = new CBitShifter();
	}
	catch (...)
	{
		free (m_puchBuffer);
		return errno;
	}

	for (iLoop = 0; iLoop < uicchBuffer; iLoop++)
	{
		m_puchBuffer[iLoop] = pBitShftr->RotateRight(
											m_puchBuffer[iLoop],
											pParam->uiShiftCount
											);
	}

	m_uiSize = uicchBuffer;

	return 0;
}


int
CBitShiftAlgo::Write(
	const char *pcszFileName
	)
{
	int iFd;
	int iRet;

	INIT_LOGGER(CBitShiftAlgo::Write)

	if (NULL == pcszFileName)
	{
		LOG("Invalid param. Exit.")

		return EINVAL;
	}

	if (NULL== m_puchBuffer)
	{
		LOG("Call ApplyAlgo first.")

		return EINVAL;
	}

	iFd  = open(pcszFileName, O_CREAT | O_EXCL | O_TRUNC);
	if (-1 == iFd)
	{
		LOG("file opening failed. %d.", errno)
		return errno;
	}

	iRet = write(
				iFd,
				m_puchBuffer,
				m_uiSize
				);
	if (m_uiSize != iRet)
	{
		LOG("Writing to file failed. errno:%d", errno);

		return errno;
	}

	return 0;
}


int
CBitShiftAlgo::Write(
	unsigned char *puchBuff,
	unsigned int *puicbBuff
	)
{
	INIT_LOGGER(CBitShiftAlgo::Write)

	if (NULL == puchBuff)
	{
		LOG("buff is NULL. ")
		LOG("Required size: %d", m_uiSize)

		*puicbBuff = m_uiSize;
		return 0;
	}

	if (*puicbBuff != m_uiSize)
	{
		LOG("Required size: %d", m_uiSize)
		LOG("Passed size: %d", puicbBuff)

		return EINVAL;
	}

	memcpy(puchBuff, m_puchBuffer, m_uiSize);

	return 0;
}


//**********************************************************
//
//	Module Name:
//		cryptana.cpp
//
//	Description:
//		The entry point file for the crytographic
//		analysis of files.
//
//	Author:
//		Suraj K
//
//	History:
//		Date: 08 Aug, 2015
//		Comment: Created.
//
//**********************************************************

////////////////////////////////////////////////////////////
//	H E A D E R
////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <sys/stat.h>
#include "cryptana.h"
#include "./algorithms/bitshift.h"
#include "../../../../common/source/include/macros.h"
#include "debug.h"


////////////////////////////////////////////////////////////
//	M A C R O S
////////////////////////////////////////////////////////////

#define	BANER_ROW									18
#define	BANER_COL									10
#define	BANNER_DISPLAY_TOKEN						" "
#define	BANNER_DISPLAY_BK_TOKEN						"|"

#define	FOLDER_CURRENT								"./"
#define	FOLDER_NAME_RESULT							"result/"
#define	FOLDER_NAME_BITROT							"bitrot/"

#define	MAX_BUFF_SIZE								1024


////////////////////////////////////////////////////////////
//	G L O B A L S
////////////////////////////////////////////////////////////

unsigned int uiBanner[BANER_ROW][BANER_COL] = {

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x80,0xff,0x81,0xff,0xff,0xff,0x81,0xff,0x00,
0x00,0x80,0x81,0x81,0x81,0x10,0x81,0xc1,0x81,0x00,
0x00,0x80,0x81,0x81,0x81,0x10,0x81,0xa1,0x81,0x00,
0x00,0x80,0xff,0xff,0xff,0x10,0xff,0x91,0xff,0x00,
0x00,0x80,0xa0,0x01,0x80,0x10,0x81,0x89,0x81,0x00,
0x00,0x80,0x90,0x01,0x80,0x10,0x81,0x85,0x81,0x00,
0x00,0xc0,0x88,0x01,0x80,0x10,0x81,0x83,0x81,0x00,
0x00,0xff,0x84,0xff,0x80,0x10,0x81,0x81,0x81,0x00
};


char *g_pszLogFileName = "./cryptana.log";


////////////////////////////////////////////////////////////
//	C L A S S  D E F I N I T I O N S
////////////////////////////////////////////////////////////

CCryptAna::CCryptAna()
{
	DisplayBanner();
}


CCryptAna::~CCryptAna()
{
}


int
main(int argc, char *argv[])
{
	int iRet;
	CCryptAna CryptoAnalysis;

	INIT_LOGGER(main)

	if (argc != 2)
	{
		printf ("Please enter the file name as command line param.");
		return EINVAL;
	}

	iRet = CryptoAnalysis.BitRotation(argv[1]);
}

void
CCryptAna::DisplayBanner(
	)
{	
	int iTemp;
	int iLoop;
	int iLoop2;
	unsigned int iLoop3;
	unsigned int uiMask;
	unsigned int uiData;

	uiMask = 0x80;

	for (iLoop = 0; iLoop < BANER_ROW; iLoop++)
	{
		for(iLoop2 = 0; iLoop2 < BANER_COL; iLoop2++)
		{
			uiData = uiBanner[iLoop][iLoop2];

			for(iLoop3 = 0; iLoop3 < 8; iLoop3++)
			{
				if (uiData & (uiMask>>iLoop3))
				{
					printf(BANNER_DISPLAY_TOKEN);
				}
				else
				{
					printf(BANNER_DISPLAY_BK_TOKEN);
					//printf("%s", (rand()%2)?"1":"0");
				}
			}

			printf(BANNER_DISPLAY_BK_TOKEN);
			//printf("%s%s", (rand()%2)?"1":"0", rand()%2?"1":"0");
		}
		printf("\n");
	}

	printf("\n");
	printf("*************************************************************************\n");
	printf("W E L C O M E\n");
	printf("*************************************************************************\n");
}


int
CCryptAna::BitRotation(
	const char *pcszFilename
	)
{
	int iFd;
	int iRet;
	int iLoop;
	int iFdWrite;
	unsigned int iTemp;
	unsigned char *puchBuff;
	CBitShiftAlgo BitRotator;
	char szFileName[PATH_MAX];
	BIT_SHIFT_ALGO_PARAM Param;
	unsigned char uchBuff[MAX_BUFF_SIZE];

	INIT_LOGGER(CCryptAna::BitRotation)

	if (NULL == pcszFilename)
	{
		LOG("Invalid param")

		return EINVAL;
	}

	iRet = access(pcszFilename, F_OK);
	if (-1 == iRet)
	{
		LOG("(%s) file not present. errno: %s", pcszFilename, errno)
		return errno;
	}

	//
	//	Create a folder for result
	//	./result/rotate
	//
	iRet = access(FOLDER_CURRENT FOLDER_NAME_RESULT, F_OK);
	if (-1 == iRet)
	{
		LOG("result folder not present.. Creating..")
		iRet = mkdir(
				FOLDER_CURRENT FOLDER_NAME_RESULT,
				0777
				);
		if (0 != iRet)
		{
			LOG("mkdir failed. errno: %d", errno);
			return errno;
		}

		LOG("Result folder created.")
	}

	iRet = access(
				FOLDER_CURRENT FOLDER_NAME_RESULT FOLDER_NAME_BITROT,
				F_OK
				);
	if (-1 == iRet)
	{
		LOG("result folder not present.. Creating..")
		iRet = mkdir(
				FOLDER_CURRENT FOLDER_NAME_RESULT FOLDER_NAME_BITROT,
				0777
				);
		if (0 != iRet)
		{
			LOG("mkdir failed. errno: %d", errno);
			return errno;
		}

		LOG(
			"%s folder created.",
			FOLDER_CURRENT FOLDER_NAME_RESULT FOLDER_NAME_BITROT
			)
	}
	
	for (iLoop = 1; iLoop <= 8; iLoop++)
	{
		Param.uiShiftCount = iLoop;

		LOG("Reading file (%s)", pcszFilename)

		//
		//	Read this file content, rotate
		//	1-7 times and create file.
		//
		iFd = open(
				pcszFilename,
				O_RDONLY
				);
		if (-1 == iFd)
		{
			LOG("Could not open file. errno: %d", errno)
			return errno;
		}

		iRet = snprintf(
					szFileName,
					ARRAY_SIZE(szFileName),
					"%sshift%d.dat",
					FOLDER_CURRENT FOLDER_NAME_RESULT FOLDER_NAME_BITROT,
					iLoop
					);
		if (iRet <= 0 || iRet >= ARRAY_SIZE(szFileName))
		{
			iRet = errno;

			LOG("sprintf failed: %d", errno)
			close(iFd);

			return iRet;
		}

		//
		//	Create file.
		//
		iFdWrite = open(
					szFileName,
					O_CREAT | O_TRUNC | O_WRONLY,
					S_IRWXG | S_IRWXU | S_IRWXO
					);
		if (-1 == iFdWrite)
		{
			iRet = errno;

			LOG("open failed for (%s): %d", szFileName, errno)
			return errno;
		}

		LOG("(%s) file created.", szFileName)

		//
		//	Write to the file.
		//	till the file ends.
		//
		do
		{
			iRet = read(
					iFd,
					uchBuff,
					ARRAY_SIZE(uchBuff)
					);
			if (iRet > 0)
			{
				LOG("read suceeded, read %d bytes.", iRet)
				LOG("Rotating bits..")

				iTemp = BitRotator.ApplyAlgorithm(
											uchBuff,
											iRet,
											(void *) &Param
											);
				if (0 != iTemp)
				{
					LOG("Bit rotation failed. Trying next file..")
					break;
				}

				iTemp = 0;
				iRet = BitRotator.Write(NULL, &iTemp);
				if (0 != iRet)
				{
					LOG("bit rotator failed.");
					break;
				}

				LOG("Encrypted data size: %d", iTemp)

				puchBuff = (unsigned char *) malloc(iTemp);
				if (NULL == puchBuff)
				{
					LOG("malloc failed: errno:%d", errno)
					break;
				}

				iRet = BitRotator.Write(puchBuff, &iTemp);
				if (0 != iRet)
				{
					LOG("BitRotator.Write() failed.");
					free(puchBuff);

					break;
				}

				iRet = write(
							iFdWrite,
							puchBuff,
							iTemp
							);
				if (iTemp != iRet)
				{
					free(puchBuff);

					LOG("write failed to ifd %d, return value: %d. errno: %d", iFdWrite, iTemp, errno)
					break;
				}

				free(puchBuff);
				LOG("%d bytes written", iRet)
			}
			else
			{
				LOG("%d bytes read. Writing skipped.", iRet)
			}

		}	while (-1 != iRet && 0 != iRet);

		close(iFdWrite);
		LOG("file closed %d", iFdWrite)

		close(iFd);
		LOG("file closed %d", iFd)
	}
}


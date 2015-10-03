//**********************************************************
//
//	Module Name:
//		ftypinfo.h
//
//	Description:
///		This module contains functions related to
//		storing and retriving the file types information.		
//
//	Author:
//		Suraj K
//
//	History:
//		Date: 25 Aug, 2015
//		Comment: Created.
//
//**********************************************************

#ifndef _FTYPINFO_H_
#define	_FTYPINFO_H_

////////////////////////////////////////////////////////////
//	H E A D E R S.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//	M A C R O S.
////////////////////////////////////////////////////////////

#define	MAX_SIG_LEN								20
#define	MAX_INFO_LEN							1024
#define	MAX_HEADER_SIG_LEN						2


////////////////////////////////////////////////////////////
//	S T R U C T U R E S.
////////////////////////////////////////////////////////////

#pragma pack(push, 1)
typedef struct _structFILE_TYPE_INFO
{
	unsigned int	uiOffset;
	unsigned int	uiSigSize;
	unsigned int	uiSig[MAX_SIG_LEN];
	char 			szInformation[MAX_INFO_LEN];

}	FILE_TYPE_INFO, *P_FILE_TYPE_INFO;
#pragma pack(pop)

#pragma pack(push, 1)
typedef	struct _structFILE_HEADER
{
	unsigned int	uiSig[MAX_HEADER_SIG_LEN];
	unsigned int	uiRecordCount;

}	FILE_HEADER, *P_FILE_HEADER;
#pragma pack(pop)


////////////////////////////////////////////////////////////
//	C L A S S  D E C L A R A T I O N.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
//	Name:
//		CFileTypeInfo
//
//	Description:
//		Contains functionality to add and remove the file
//		type information
//
///////////////////////////////////////////////////////////

class CFileTypeInfo
{
	public:
	CFileTypeInfo(
		const char *pcszFileName
		);

	~CFileTypeInfo(
		);


	private:
	int m_iFd;

	int
	IsSignatureOk(
		);

	int
	ReadIntoBuffer(
		FILE_TYPE_INFO **ppFileTypeInfo
		);

	int
	AddToFile(
		FILE_TYPE_INFO *pFileTypeInfo
		);

};

#endif	// _FTYPINFO_H_

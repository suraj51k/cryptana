//**********************************************************
//
//	Module Name:
//		filetype.h
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

////////////////////////////////////////////////////////////
//	C O N S T A N T S.
////////////////////////////////////////////////////////////

typedef enum _enumFILE_DATA_TYPE
{
	FILE_DATA_TYPE_FILE_NAME = 0,
	FILE_DATA_TYPE_FILE_DATA

}	FILE_DATA_TYPE;


////////////////////////////////////////////////////////////
//	S T R U C T U R E S.
////////////////////////////////////////////////////////////

typedef struct _structFILE_DATA
{
	char *pszFileName;
	FILE_DATA_TYPE FileDataType;

}	FILE_DATA, *P_FILE_FATA;


////////////////////////////////////////////////////////////
//	C L A S S  D E C L A R A T I O N.
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
//	Class:
//		CFileType
//
//	Description:
//		Finds the file type based on its signature.
//
////////////////////////////////////////////////////////////
class CFileType
{
public:

	CFileType(
		);

	~CFileType(
		);

protected:
	int
	ApplyAlgorithm(
		const unsigned char *pcuchBuffer,
		unsigned int uiBuffer,
		void *pvParam
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

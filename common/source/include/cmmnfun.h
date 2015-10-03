//**********************************************************
//
//	Module Name:
//		cmmnfun.cpp
//
//	Description:
//		Contains all the common functions.
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
//	C L A S S  D E F I N I T I O N S.
////////////////////////////////////////////////////////////

class CCommon
{
	///////////////////////////////////////////////////////
	//
	//	Function Name:
	//		ReadFile
	//
	//	Parameters:
	//		[IN] const char *pcszFileName
	//		The file name to be read.
	//
	//		[OUT] pszBuffer
	//		The buffer that will contain the file
	//		content.
	//
	//		[IN/OUT] uiccbBuffer
	//		Contains the size of buffer, 
	//		on return contains the size of data read.
	//
	//	Description:
	//		Reads the file content into the buffer.
	//		If the buffer pointer is NULL, the size of
	//		buffer needed to hold the file content is
	//		returned in uiccbBuffer.
	//
	///////////////////////////////////////////////////////
	static int
	ReadFile(
		const char *pcszFileName,
		char *pszBuffer,
		unsigned int uiccbBuffer
		);

};

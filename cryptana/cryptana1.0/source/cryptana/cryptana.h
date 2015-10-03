//**********************************************************
//
//	Module Name:
//		cryptana.h
//
//	Description:
//		Header file for the crypt analysis tool
//
//	Author:
//		Suraj K
//
//	History:
//		Date: 09 Aug, 2015
//		Comment: Created.
//
//**********************************************************


#ifndef	_CRYPTANA_H
#define	_CRYPTANA_H

////////////////////////////////////////////////////////////
//	H E A D E R
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//	C L A S S  D E C L A R A T I O N
////////////////////////////////////////////////////////////

class CCryptAna
{
	public:

	CCryptAna(
		);

	~CCryptAna(
		);

	static int
	BitRotation(
		const char *pcszFilename
		);

	private:

	void
	DisplayBanner(
		);

};


int
main(
	int argc,
	char *argv[]
	);

#endif	// _CRYPTANA_H


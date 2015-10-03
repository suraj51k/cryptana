//**********************************************************
//
//	Module Name:
//		head.h
//
//	Description:
//		Header file for writing header content of
//		cpp files.
//
//	Author:
//		Suraj K
//
//	History:
//		Date: 08 Aug, 2015
//		Comment: Created.
//
//**********************************************************

#include <stdio.h>

#define	ENABLE_LOG				0

int
main(
	int argc, 
	char* argv[]
	);

int
Backup(
	const char *pcszFrom,
	const char *pcszTo
	);

int
Restore(
	const char *pcszFrom,
	const char *pcszTo
	);

//**********************************************************
//
//	Module Name:
//		debug.h
//
//	Description:
//		
//
//	Author:
//		Suraj K
//
//	History:
//		Date: 16 Aug, 2015
//		Comment: Created.
//
//**********************************************************

#ifndef _DEBUG_H
#define	_DEBUG_H

////////////////////////////////////////////////////////////
//	H E A D E R S
////////////////////////////////////////////////////////////

#include "../../../../common/source/include/log.h"


////////////////////////////////////////////////////////////
//	M A C R O S
////////////////////////////////////////////////////////////

#define	ENABLE_LOG								1

#if	ENABLE_LOG
#define	INIT_LOGGER(X)			CLogger CLoggerInstance(#X);
#define	LOG(X, ...)				CLoggerInstance.log(X, ##__VA_ARGS__);
#else
#define	INIT_LOGGER(X)
#define LOG(X, ...)
#endif


#endif	// _DEBUG_H

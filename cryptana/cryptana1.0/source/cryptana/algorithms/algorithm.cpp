//**********************************************************
//
//	Module Name:
//		algorithm.cpp
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

////////////////////////////////////////////////////////////
//	H E A D E R
////////////////////////////////////////////////////////////

#include "../../../../../common/source/include/macros.h"
#include "algorithm.h"
#include "../debug.h"


////////////////////////////////////////////////////////////
//	C L A S S  D E F I N I T I O N
////////////////////////////////////////////////////////////

AbsAlgorithm::AbsAlgorithm(
	)
{
	m_puchBuffer = NULL;
	m_uiSize = 0;
}

AbsAlgorithm::~AbsAlgorithm(
	)
{
}

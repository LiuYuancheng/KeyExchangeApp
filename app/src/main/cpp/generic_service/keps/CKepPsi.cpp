/*
 * CKepPsi.cpp
 *
 *  Created on: 21 Feb 2020
 *      Author: yiwen
 */

#include "../../generic_service/keps/CKepPsi.h"


CKepPsi::CKepPsi(int count, CTwoWayKep *keps[]): CHybridTwoWayKep(count, keps)
{
	StateIndicator = 0;
	SyncState = SYN_STATE_INITIAL;
}


CKepPsi::~CKepPsi()
{
	// TODO Auto-generated destructor stub
}


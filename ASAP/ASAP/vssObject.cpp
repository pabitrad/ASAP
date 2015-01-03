#include "stdafx.h"
#include "vssObject.h"


vssObject::vssObject()
{
	

	IVssBackupComponents *pBackup = NULL;
	HRESULT result = CreateVssBackupComponents(&pBackup);

	// result == E_ACCESSDENIED at this point

	pBackup->InitializeForBackup();
}

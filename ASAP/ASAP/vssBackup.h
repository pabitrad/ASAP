#pragma once
#include "vsbackup.h"
class vssBackup //:
	//public IVssBackupComponents
{
	/// <summary>
	/// Setting this flag to true will enable 'component mode', which
	/// does not, in this example, do much of any substance.
	/// </summary>
	/// <remarks>
	/// VSS has the ability to selectively disable VSS-compatible
	/// components according to the specifics of the current backup.  One
	/// might, for example, only quiesce Outlook if only the Outlook PST
	/// file is intended to be backed up.  The ExamineComponents() method
	/// provides a framework for this sort of mode if you're interested.
	/// Otherwise, this example code quiesces all VSS-compatible components
	/// before making its shadow copy.
	/// </remarks>
	bool ComponentMode = false;

	/// <summary>A reference to the VSS context.</summary>
	IVssBackupComponents* _backup; 
public:
	vssBackup();
	~vssBackup();
};


#pragma once
#include "CWriterComponent.h"
#include "COptions.h"
#include "CDirectoryAction.h"

class VssBackup //:
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
	private:
		bool ComponentMode = false;

		void initializeVSS();
		bool ShouldAddComponent(CWriterComponent& component);
		void Cleanup(bool bAbnormalAbort, bool bSnapshotCreated, CComPtr<IVssBackupComponents> pBackupComponents, GUID snapshotSetId);
		void CalculateSourcePath(LPCTSTR wszSnapshotDevice, LPCTSTR wszBackupSource, LPCTSTR wszMountPoint, CString& output);
		void ProcessDirectory(LPCTSTR srcbase, CDirectoryAction& action, LPCTSTR directory, bool recursive, wregex* ignorePattern);
		bool ShouldProcess(wregex* ignorePattern, const CString& directory, const CString& name);
		bool ShouldProcess(wregex* ignorePattern, const CString& path);
		bool IsMatch(wregex* pattern, const CString& input);

		/// <summary>A reference to the VSS context.</summary>

public:
	VssBackup();
	~VssBackup();

	//static VssBackup *getInstance()
	//{
	//	if (pInstance == NULL)
	//	{
	//		pInstance = new VssBackup();
	//	}

	//	return pInstance;
	//}

	int startBackUp(COptions options);
};


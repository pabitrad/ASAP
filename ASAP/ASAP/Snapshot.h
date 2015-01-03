#pragma once
using namespace System;
using namespace System::ComponentModel;
//using namespace System::Collections::Generic;
//using namespace System::Diagnostics;
//using namespace System::IO;

//#include "backup.h"
//#include "vssobj.h"
#include <vss.h>
#include <vswriter.h>
#include <vsbackup.h>
#include <vector>
#include <algorithm>

/// <summary>A reference to the VSS context.</summary>
typedef HRESULT(STDAPICALLTYPE *_CreateVssBackupComponentsInternal)(
	__out IVssBackupComponents **ppBackup
	);

typedef void (APIENTRY *_VssFreeSnapshotPropertiesInternal)(
	__in VSS_SNAPSHOT_PROP *pProp
	);

typedef struct _BK_VSS_SNAPSHOT
{
	VSS_ID SnapshotId;
	PPH_STRING Volume;
	PH_STRINGREF VolumeSr; // without trailing backslash
	PPH_STRING SnapshotDevice;
} BK_VSS_SNAPSHOT, *PBK_VSS_SNAPSHOT;

typedef struct _BK_VSS_OBJECT
{
	IVssBackupComponents *Object;
	VSS_ID SnapshotSetId;
	std::vector<BK_VSS_SNAPSHOT> Snapshots;
} BK_VSS_OBJECT, *PBK_VSS_OBJECT;


/// <summary>
/// Utility class to manage the snapshot's contents and ID.
/// </summary>
ref class Snapshot 
{
		static _CreateVssBackupComponentsInternal CreateVssBackupComponentsInternal_I;
	
		static _VssFreeSnapshotPropertiesInternal VssFreeSnapshotPropertiesInternal_I;
		
		HRESULT result;
		HMODULE vssapiBase;
		IVssBackupComponents *backupComponents;


	/// <summary>Metadata about this object's snapshot.</summary>
	VssSnapshotProperties _props;

	/// <summary>Identifier for the overall shadow copy.</summary>
	Guid _set_id;

	/// <summary>Identifier for our single snapshot volume.</summary>
	Guid _snap_id;

	/// <summary>
	/// Initializes a snapshot.  We save the GUID of this snap in order to
	/// refer to it elsewhere in the class.
	/// </summary>
	/// <param name="backup">A VssBackupComponents implementation for the current OS.</param>
	Snapshot(IVssBackupComponents backup)
	{
		vssapiBase = LoadLibrary(L"vssapi.dll");

		if (vssapiBase)
		{
			CreateVssBackupComponentsInternal_I = (_CreateVssBackupComponentsInternal)GetProcAddress(vssapiBase, "CreateVssBackupComponentsInternal");
			VssFreeSnapshotPropertiesInternal_I = (_VssFreeSnapshotPropertiesInternal)GetProcAddress(vssapiBase, "VssFreeSnapshotPropertiesInternal");
		}

		if (!CreateVssBackupComponentsInternal_I || !VssFreeSnapshotPropertiesInternal_I)
			abort(); // Handle error

		result = CreateVssBackupComponentsInternal_I(&backupComponents);

		if (!SUCCEEDED(result))
			abort(); // Handle error

		_backup = backup;
	//	_set_id = backup.StartSnapshotSet();
//		CreateVssBackupComponents
	}
public:
	/// <summary>
	/// Dispose of the shadow copies created by this instance.
	/// </summary>
	void Dispose()
	{
		try { Delete(); }
		catch { }
	}

	/// <summary>
	/// Adds a volume to the current snapshot.
	/// </summary>
	/// <param name="volumeName">Name of the volume to add (eg. "C:\").</param>
	/// <remarks>
	/// Note the IsVolumeSupported check prior to adding each volume.
	/// </remarks>
	void AddVolume(string volumeName)
	{
		if (_backup.IsVolumeSupported(volumeName))
			_snap_id = _backup.AddToSnapshotSet(volumeName);
		else
			throw new VssVolumeNotSupportedException(volumeName);
	}

	/// <summary>
	/// Create the actual snapshot.  This process can take around 10s.
	/// </summary>
	void Copy()
	{
		_backup.DoSnapshotSet();
	}

	/// <summary>
	/// Remove all snapshots.
	/// </summary>
	void Delete()
	{
		_backup.DeleteSnapshotSet(_set_id, false);
	}

	/// <summary>
	/// Gets the string that identifies the root of this snapshot.
	/// </summary>
	String Root
	{
		get
		{
		if (_props == null)
		_props = _backup.GetSnapshotProperties(_snap_id);
		return _props.SnapshotDeviceObject;
	}
	}
};

ref  class VssSnapshotProperties
{

	Guid SnapshotId;

	Guid SnapshotSetId;

	int SnapshotsCount;

	[MarshalAs(UnmanagedType.LPWStr)]
	String SnapshotDeviceObject;

	[MarshalAs(UnmanagedType.LPWStr)]
	String OriginalVolumeName;

	[MarshalAs(UnmanagedType.LPWStr)]
	String OriginatingMachine;

	[MarshalAs(UnmanagedType.LPWStr)]
	String ServiceMachine;

	[MarshalAs(UnmanagedType.LPWStr)]
	String ExposedName;

	[MarshalAs(UnmanagedType.LPWStr)]
	String ExposedPath;

	Guid ProviderId;

	int SnapshotAttributes;

	long CreationTimestamp;

	int SnapshotState;
}
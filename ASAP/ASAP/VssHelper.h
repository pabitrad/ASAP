#pragma once


namespace ASAP {

	// The type of a file descriptor
	typedef enum
	{
		VSS_FDT_UNDEFINED = 0,
		VSS_FDT_EXCLUDE_FILES,
		VSS_FDT_FILELIST,
		VSS_FDT_DATABASE,
		VSS_FDT_DATABASE_LOG,
	} VSS_DESCRIPTOR_TYPE;


	//////////////////////////////////////////////////////////////////////////////////////
	// In-memory representation of a file descriptor
	//

	ref struct VssFileDescriptor
	{
		VssFileDescriptor() :
		isRecursive(false),
		type(VSS_FDT_UNDEFINED)
		{};

		// Initialize from a IVssWMFiledesc
		void Initialize(
			IVssWMFiledesc * pFileDesc,
			VSS_DESCRIPTOR_TYPE typeParam
			);

		// Print this file descriptor 
		void Print();

		// Get the string representation of the type
		wstring GetStringFromFileDescriptorType(VSS_DESCRIPTOR_TYPE eType);

		//
		//  Data members
		//

		wstring             path;
		wstring             filespec;
		wstring             alternatePath;
		bool                isRecursive;

		VSS_DESCRIPTOR_TYPE type;
		wstring             expandedPath;
		wstring             affectedVolume;
	};



	//////////////////////////////////////////////////////////////////////////////////////
	// In-memory representation of a component dependency
	//

#ifdef VSS_SERVER

	ref struct VssDependency
	{
		VssDependency() {};

		// Initialize from a IVssWMDependency
		void Initialize(
			IVssWMDependency * pDependency
			);

		// Print this dependency
		void Print();

		//
		//  Data members
		//

		wstring             writerId;
		wstring             logicalPath;
		wstring             componentName;
		wstring             fullPath;
	};

#endif


	//////////////////////////////////////////////////////////////////////////////////////
	// In-memory representation of a component
	//

	ref struct VssComponent
	{
		VssComponent() :
		type(VSS_CT_UNDEFINED),
		isSelectable(false),
		notifyOnBackupComplete(false),
		isTopLevel(false),
		isExcluded(false),
		isExplicitlyIncluded(false)
		{};

		// Initialize from a IVssWMComponent
		void Initialize(wstring writerNameParam, IVssWMComponent * pComponent);

		// Initialize from a IVssComponent
		void Initialize(wstring writerNameParam, IVssComponent * pComponent);

		// Print summary/detalied information about this component
		void Print(bool bListDetailedInfo);

		// Convert a component type into a string
		wstring GetStringFromComponentType(VSS_COMPONENT_TYPE eComponentType);

		// Return TRUE if the current component is ancestor of the given component
		bool IsAncestorOf(VssComponent & child);

		// return TRUEif it can be explicitly included
		bool CanBeExplicitlyIncluded();

		//
		//  Data members
		//

		wstring             name;
		wstring             writerName;
		wstring             logicalPath;
		wstring             caption;
		VSS_COMPONENT_TYPE  type;
		bool                isSelectable;
		bool                notifyOnBackupComplete;

		wstring             fullPath;
		bool                isTopLevel;
		bool                isExcluded;
		bool                isExplicitlyIncluded;
		vector<wstring>     affectedPaths;
		vector<wstring>     affectedVolumes;
		vector<VssFileDescriptor> descriptors;

#ifdef VSS_SERVER
		vector<VssDependency> dependencies;
#endif
	};


	//////////////////////////////////////////////////////////////////////////////////////
	// In-memory representation of a writer metadata
	//

	ref struct VssWriter
	{
		VssWriter() :
		isExcluded(false),
		supportsRestore(false),
		restoreMethod(VSS_RME_UNDEFINED),
		writerRestoreConditions(VSS_WRE_UNDEFINED),
		rebootRequiredAfterRestore(false)
		{};

		// Initialize from a IVssWMFiledesc
		void Initialize(IVssExamineWriterMetadata * pMetadata);

		// Initialize from a IVssWriterComponentsExt
		void InitializeComponentsForRestore(IVssWriterComponentsExt * pWriterComponents);

		// Print summary/detalied information about this writer
		void Print(bool bListDetailedInfo);

		wstring GetStringFromRestoreMethod(VSS_RESTOREMETHOD_ENUM eRestoreMethod);

		wstring GetStringFromRestoreConditions(VSS_WRITERRESTORE_ENUM eRestoreEnum);

		//
		//  Data members
		//

		wstring                     name;
		wstring                     id;
		wstring                     instanceId;
		vector<VssComponent>        components;
		vector<VssFileDescriptor>   excludedFiles;
		VSS_WRITERRESTORE_ENUM      writerRestoreConditions;
		bool                        supportsRestore;
		VSS_RESTOREMETHOD_ENUM      restoreMethod;
		bool                        rebootRequiredAfterRestore;

		bool                        isExcluded;
	};

	ref class VssHelper
	{
	public:
		// Constructor
		VssHelper();

		// Destructor
		~VssHelper();

		// Initialize the internal pointers
		void Initialize(DWORD dwContext = VSS_CTX_BACKUP, wstring xmlDoc = "", bool bDuringRestore = false);

		//
		//  Shadow copy creation related methods
		//

		// Method to create a shadow copy set with the given volumes
		void CreateSnapshotSet(
			vector<wstring> volumeList,
			wstring outputXmlFile,
			vector<wstring> excludedWriterList,
			vector<wstring> includedWriterList
			);

		// Prepare the shadow copy for backup
		void PrepareForBackup();

		// Add volumes to the shadow copy set
		void AddToSnapshotSet(vector<wstring> volumeList);

		// Effectively creating the shadow copy (calling DoSnapshotSet)
		void DoSnapshotSet();

		// Ending the backup (calling BackupComplete)
		void BackupComplete(bool succeeded);

		// Save the backup components document
		void SaveBackupComponentsDocument(wstring fileName);

		// Import the snapshot set
		void ImportSnapshotSet();

		// Generate the SETVAR script for this shadow copy set
		void GenerateSetvarScript(wstring stringFileName);

		// Marks all selected components as succeeded for backup
		void SetBackupSucceeded(bool succeeded);

		//
		//  Shadow copy query related methods
		//

		// Query all the shadow copies in the given set
		// If snapshotSetID is NULL, just query all shadow copies in the system
		void QuerySnapshotSet(VSS_ID snapshotSetID);

		// Query the properties of the given shadow copy
		void GetSnapshotProperties(VSS_ID snapshotID);

		// Print the properties for the given snasphot
		void PrintSnapshotProperties(VSS_SNAPSHOT_PROP & prop);

		//
		//  Shadow copy deletion related methods
		//

		// Delete all the shadow copies in the system
		void DeleteAllSnapshots();

		// Delete the given shadow copy set 
		void DeleteSnapshotSet(VSS_ID snapshotSetID);

		// Delete the given shadow copy
		void DeleteSnapshot(VSS_ID snapshotID);

		// Delete the oldest shadow copy on a volume
		void DeleteOldestSnapshot(const wstring& stringVolumeName);

		//
		//  Shadow copy break related methods
		//

		// Break the given shadow copy set 
		void BreakSnapshotSet(VSS_ID snapshotSetID, bool makeReadWrite, vector<wstring> *pVolumeNames = NULL);

		// Break using BreakEx 
		void BreakSnapshotSetEx(VSS_ID snapshotSetID, DWORD dwBreakExFlags);

		void AddResyncSet(VSS_ID snapshotSetID, wstring wsOptDestination);

		void DoResync(DWORD dwResyncFlags);

		// Make the volumes in this list read-write using VDS API
		void MakeVolumesReadWrite(vector<wstring> volumeNames);

		void RevertToSnapshot(VSS_ID snapshotID);

		// Return the list of shadow copy volume devices in this shadow copy set
		vector<wstring> GetSnapshotDevices(VSS_ID SnapshotSetID);

		// Returns an array of enumerated VDS objects
		vector< CComPtr<IUnknown> > EnumerateVdsObjects(IEnumVdsObject * pEnumeration);

		//
		//  Expose related methods
		//

		// Expose a shadow copy locally
		void ExposeSnapshotLocally(VSS_ID snapshotID, wstring path);

		// Expose a shadow copy remotely
		void ExposeSnapshotRemotely(VSS_ID snapshotID, wstring shareName, wstring pathFromRoot);


		//
		//  Writer-related methods
		//

		// Gather writer metadata
		void GatherWriterMetadata();
		void GatherWriterMetadataToScreen();

		// Gather writer status
		void GatherWriterStatus();

		// Initialize writer metadata
		void InitializeWriterMetadata();

		// Initialize the list of writers and components for restore
		void InitializeWriterComponentsForRestore();

		// List gathered writer metadata
		void ListWriterMetadata(bool bListDetailedInfo);

		// List gathered writer status
		void ListWriterStatus();

		// Pre restore
		void PreRestore();

		// Post restore
		void PostRestore();

		// Get writer status as string
		wstring GetStringFromWriterStatus(VSS_WRITER_STATE eWriterStatus);

		//
		//  Writer/Component selection-related methods
		//


		// Select the maximum number of components such that their 
		// file descriptors are pointing only to volumes to be shadow copied
		void SelectComponentsForBackup(
			vector<wstring> shadowSourceVolumes,
			vector<wstring> excludedWriterAndComponentList,
			vector<wstring> includedWriterAndComponentList
			);

		// Select the maximum number of components for restore
		void SelectComponentsForRestore(
			vector<wstring> excludedWriterAndComponentList,
			vector<wstring> includedWriterAndComponentList
			);

		// Discover directly excluded components (that were excluded through the command-line)
		void DiscoverDirectlyExcludedComponents(
			vector<wstring> excludedWriterAndComponentList,
			vector<VssWriter> & writerList
			);

		// Discover excluded components that have file groups outside the shadow set
		void DiscoverNonShadowedExcludedComponents(
			vector<wstring> shadowSourceVolumes
			);

		// Discover the components that should not be included (explicitly or implicitly)
		// These are componenets that are have directly excluded descendents
		void DiscoverAllExcludedComponents();

		// Discover excluded writers. These are writers that:
		// - either have a top-level nonselectable excluded component
		// - or do not have any included components (all its components are excluded)
		void DiscoverExcludedWriters();

		// Discover the components that should be explicitly included 
		// These are any included top components 
		void DiscoverExplicitelyIncludedComponents();

		// Exclude writers that do not support restore events
		void ExcludeWritersWithNoRestoreEvents();

		// Select explicitly included components
		void SelectExplicitelyIncludedComponents();

		// Select explicitly included components
		void SelectNonexcludedComponentsForRestore();

		// Set the restore status for all components
		void SetFileRestoreStatus(bool bSuccesfullyRestored);

		// Verify that the given components will be explicitly or implicitly selected
		void VerifyExplicitelyIncludedComponent(
			wstring includedComponent,
			vector<VssWriter> & writerList
			);

		// Verify that all the components of this writer are selected
		void VerifyExplicitelyIncludedWriter(
			wstring writerName,
			vector<VssWriter> & writerList
			);

		// Is this writer part of the backup?
		// (i.e. if it was not previously excluded)
		bool IsWriterSelected(GUID guidInstanceId);

		// Check the status for all selected writers
		void CheckSelectedWriterStatus();


	private:

		// Waits for the async operation to finish
		void WaitAndCheckForAsyncOperation(IVssAsync*  pAsync);



	private:

		//
		//  Data members
		//

		// TRUE if CoInitialize() was already called 
		// Needed to pair each succesfull call to CoInitialize with a corresponding CoUninitialize
		bool                            m_bCoInitializeCalled;

		// VSS context
		DWORD                           m_dwContext;

		// The IVssBackupComponents interface is automatically released when this object is destructed.
		// Needed to issue VSS calls 
		CComPtr<IVssBackupComponents>   m_pVssObject;

		// List of selected writers during the shadow copy creation process
		vector<wstring>                 m_latestVolumeList;

		// List of shadow copy IDs from the latest shadow copy creation process
		vector<VSS_ID>                  m_latestSnapshotIdList;

		// Latest shadow copy set ID
		VSS_ID                          m_latestSnapshotSetID;

		// List of writers
		vector<VssWriter>               m_writerList;

		// List of selected writers/componnets from the previous backup components document
		vector<VssWriter>               m_writerComponentsForRestore;

		// List of resync pairs
		map<VSS_ID, wstring, ltguid>      m_resyncPairs;

		// TRUE if we are during restore
		bool                            m_bDuringRestore;
	};
}
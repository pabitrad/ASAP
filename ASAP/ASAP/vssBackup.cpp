#include "stdafx.h"
#include "CWriter.h"
#include "CWriterComponent.h"
#include "CDirectoryAction.h"
#include "CCopyAction.h"
#include "CCopyFilter.h"
#include "CFilespecCopyFilter.h"
#include "CIncludeAllCopyFilter.h"
#include "CBackupState.h"
#include "CModifiedSinceCopyFilter.h"

#include "vssBackup.h"

VssBackup::VssBackup(void)
{
	initializeVSS();
}


VssBackup::~VssBackup()
{
}

///Intialize VSS componets
void VssBackup::initializeVSS()
{
	//CHECK_HRESULT(::CoInitialize(NULL));

}

int VssBackup::startBackUp(COptions options)
{
	bool bSnapshotCreated = false;
	bool bAbnormalAbort = true;

	int fileCount = 0;
	LONGLONG byteCount = 0;
	int directoryCount = 0;
	int skipCount = 0;
	SYSTEMTIME startTime;
	GUID snapshotSetId = GUID_NULL;
	CComPtr<IVssBackupComponents> pBackupComponents;

	try
	{
		CHECK_HRESULT(::CoInitialize(NULL));
		::CoInitializeSecurity(
			NULL,
			-1,
			NULL,
			NULL,
			RPC_C_AUTHN_LEVEL_PKT_PRIVACY,
			RPC_C_IMP_LEVEL_IDENTIFY,
			NULL,
			EOAC_NONE,
			NULL);

		::GetSystemTime(&startTime);
		CString startTimeString;
		Utilities::FormatDateTime(&startTime, TEXT(" "), false, startTimeString);

		if (options.get_ClearDestination())
		{
			if (!Utilities::DirectoryExists(options.get_Destination()))
			{
				CString message;
				message.AppendFormat(TEXT("Skipping recursive delete of destination directory %s because it appears not to exist."),
					options.get_Destination());
				OutputWriter::WriteLine(message, VERBOSITY_THRESHOLD_NORMAL);
			}
			else
			{
				CString message;
				message.AppendFormat(TEXT("Recursively deleting destination directory %s."),
					options.get_Destination());
				OutputWriter::WriteLine(message, VERBOSITY_THRESHOLD_NORMAL);

				bool doDelete = options.get_AcceptAll();

				if (!doDelete)
				{
					//if (Confirm(message))
					//{
					//	doDelete = true;
					//}
					//else
					//{
					//	OutputWriter::WriteLine(TEXT("Aborting backup."), VERBOSITY_THRESHOLD_NORMAL);
					//	return 3;
					//}
				}

				if (doDelete)
				{
					//DeleteRecursive(options.get_Destination(), options.get_IgnorePattern());
				}
			}
		}

		CBackupState backupState;

		LPSYSTEMTIME lastBackupTime;

		if (options.get_BackupType() == VSS_BT_INCREMENTAL)
		{
			backupState.Load(options.get_StateFile());

			LPSYSTEMTIME lastFullBackupTime = backupState.get_LastFullBackupTime();
			LPSYSTEMTIME lastIncrementalBackupTime = backupState.get_LastIncrementalBackupTime();
			if (lastIncrementalBackupTime != NULL)
			{
				lastBackupTime = lastIncrementalBackupTime;
			}
			else
			{
				lastBackupTime = lastFullBackupTime;
			}
		}

		CHECK_HRESULT(::CreateVssBackupComponents(&pBackupComponents));
		pBackupComponents->InitializeForBackup();

		CComPtr<IVssAsync> pWriterMetadataStatus;
		pBackupComponents->GatherWriterMetadata(&pWriterMetadataStatus);
		pWriterMetadataStatus->Wait();

		HRESULT hrGatherStatus;
		pWriterMetadataStatus->QueryStatus(&hrGatherStatus, NULL);

		vector<CWriter> writers;

		UINT cWriters;
		CHECK_HRESULT(pBackupComponents->GetWriterMetadataCount(&cWriters));

		for (UINT iWriter = 0; iWriter < cWriters; ++iWriter)
		{
			CWriter writer;
			CComPtr<IVssExamineWriterMetadata> pExamineWriterMetadata;
			GUID id;
			//OutputWriter::WriteLine(TEXT("Calling GetWriterMetadata"));
			CHECK_HRESULT(pBackupComponents->GetWriterMetadata(iWriter, &id, &pExamineWriterMetadata));
			GUID idInstance;
			GUID idWriter;
			BSTR bstrWriterName;
			VSS_USAGE_TYPE usage;
			VSS_SOURCE_TYPE source;
			CHECK_HRESULT(pExamineWriterMetadata->GetIdentity(&idInstance, &idWriter, &bstrWriterName, &usage, &source));

			writer.set_InstanceId(idInstance);
			writer.set_Name(bstrWriterName);
			writer.set_WriterId(idWriter);

			//CComBSTR writerName(bstrWriterName);
			//CString message;
			//message.AppendFormat(TEXT("Writer %d named %s"), iWriter, (LPCTSTR)writerName);
			//OutputWriter::WriteLine(message);

			UINT cIncludeFiles;
			UINT cExcludeFiles;
			UINT cComponents;
			CHECK_HRESULT(pExamineWriterMetadata->GetFileCounts(&cIncludeFiles, &cExcludeFiles, &cComponents));

			//message.Empty();
			//message.AppendFormat(TEXT("Writer has %d components"), cComponents);
			//OutputWriter::WriteLine(message);

			for (UINT iComponent = 0; iComponent < cComponents; ++iComponent)
			{
				CWriterComponent component;

				CComPtr<IVssWMComponent> pComponent;
				CHECK_HRESULT(pExamineWriterMetadata->GetComponent(iComponent, &pComponent));

				PVSSCOMPONENTINFO pComponentInfo;
				CHECK_HRESULT(pComponent->GetComponentInfo(&pComponentInfo));

				//CString message;
				//message.AppendFormat(TEXT("Component %d is named %s, has a path of %s, and is %sselectable for backup. %d files, %d databases, %d log files."),
				//	iComponent,
				//	pComponentInfo->bstrComponentName,
				//	pComponentInfo->bstrLogicalPath,
				//	pComponentInfo->bSelectable ? TEXT("") : TEXT("not "),
				//	pComponentInfo->cFileCount,
				//	pComponentInfo->cDatabases,
				//	pComponentInfo->cLogFiles);
				//OutputWriter::WriteLine(message);

				component.set_LogicalPath(pComponentInfo->bstrLogicalPath);
				component.set_SelectableForBackup(pComponentInfo->bSelectable);
				component.set_Writer(iWriter);
				component.set_Name(pComponentInfo->bstrComponentName);
				component.set_Type(pComponentInfo->type);

				for (UINT iFile = 0; iFile < pComponentInfo->cFileCount; ++iFile)
				{
					CComPtr<IVssWMFiledesc> pFileDesc;
					CHECK_HRESULT(pComponent->GetFile(iFile, &pFileDesc));

					CComBSTR bstrPath;
					CHECK_HRESULT(pFileDesc->GetPath(&bstrPath));

					CComBSTR bstrFileSpec;
					CHECK_HRESULT(pFileDesc->GetFilespec(&bstrFileSpec));

					//CString message;
					//message.AppendFormat(TEXT("File %d has path %s\\%s"), iFile, bstrPath, bstrFileSpec);
					//OutputWriter::WriteLine(message);
				}

				for (UINT iDatabase = 0; iDatabase < pComponentInfo->cDatabases; ++iDatabase)
				{
					CComPtr<IVssWMFiledesc> pFileDesc;
					CHECK_HRESULT(pComponent->GetDatabaseFile(iDatabase, &pFileDesc));

					CComBSTR bstrPath;
					CHECK_HRESULT(pFileDesc->GetPath(&bstrPath));

					CComBSTR bstrFileSpec;
					CHECK_HRESULT(pFileDesc->GetFilespec(&bstrFileSpec));

					//CString message;
					//message.AppendFormat(TEXT("Database file %d has path %s\\%s"), iDatabase, bstrPath, bstrFileSpec);
					//OutputWriter::WriteLine(message);
				}

				for (UINT iDatabaseLogFile = 0; iDatabaseLogFile < pComponentInfo->cLogFiles; ++iDatabaseLogFile)
				{
					CComPtr<IVssWMFiledesc> pFileDesc;
					CHECK_HRESULT(pComponent->GetDatabaseLogFile(iDatabaseLogFile, &pFileDesc));

					CComBSTR bstrPath;
					CHECK_HRESULT(pFileDesc->GetPath(&bstrPath));

					CComBSTR bstrFileSpec;
					CHECK_HRESULT(pFileDesc->GetFilespec(&bstrFileSpec));

					//CString message;
					//message.AppendFormat(TEXT("Database log file %d has path %s\\%s"), iDatabaseLogFile, bstrPath, bstrFileSpec);
					//OutputWriter::WriteLine(message);
				}

				CHECK_HRESULT(pComponent->FreeComponentInfo(pComponentInfo));

				writer.get_Components().push_back(component);
			}

			writer.ComputeComponentTree();

			for (unsigned int iComponent = 0; iComponent < writer.get_Components().size(); ++iComponent)
			{
				CWriterComponent& component = writer.get_Components()[iComponent];
				//CString message;
				//message.AppendFormat(TEXT("Component %d has name %s, path %s, is %sselectable for backup, and has parent %s"),
				//	iComponent,
				//	component.get_Name(),
				//	component.get_LogicalPath(),
				//	component.get_SelectableForBackup() ? TEXT("") : TEXT("not "),
				//	component.get_Parent() == NULL ? TEXT("(no parent)") : component.get_Parent()->get_Name());
				//OutputWriter::WriteLine(message);
			}

			writers.push_back(writer);
		}

		//GUID snapshotId;
		CHECK_HRESULT(pBackupComponents->StartSnapshotSet(&snapshotSetId));

		WCHAR wszVolumePathName[MAX_PATH];
		BOOL bWorked = ::GetVolumePathName(options.get_Source(), wszVolumePathName, MAX_PATH);

		if (!bWorked)
		{
			//DWORD error = ::GetLastError();
			//CString errorMessage;
			//Utilities::FormatErrorMessage(error, errorMessage);
			//CString message;
			//message.AppendFormat(TEXT("There was an error retrieving the volume name from the path. Path: %s Error: %s"),
			//	options.get_Source(), errorMessage);
			//throw new CVSSCopyException(message.GetString());
		}

		//OutputWriter::WriteLine(TEXT("Calling AddToSnapshotSet"));
		GUID snapshotId;
		CHECK_HRESULT(pBackupComponents->AddToSnapshotSet(wszVolumePathName, GUID_NULL, &snapshotId));

		for (unsigned int iWriter = 0; iWriter < writers.size(); ++iWriter)
		{
			CWriter writer = writers[iWriter];

			//CString message;
			//message.AppendFormat(TEXT("Adding components to snapshot set for writer %s"), writer.get_Name());
			//OutputWriter::WriteLine(message);
			for (unsigned int iComponent = 0; iComponent < writer.get_Components().size(); ++iComponent)
			{
				CWriterComponent component = writer.get_Components()[iComponent];

				if (ShouldAddComponent(component))
				{
					CString message;
					message.AppendFormat(TEXT("Adding component %s (%s) from writer %s"),
						component.get_Name(),
						component.get_LogicalPath(),
						writer.get_Name());
					//OutputWriter::WriteLine(message);
					CHECK_HRESULT(pBackupComponents->AddComponent(
						writer.get_InstanceId(),
						writer.get_WriterId(),
						component.get_Type(),
						component.get_LogicalPath(),
						component.get_Name()
						));
				}
				else
				{
					//CString message;
					//message.AppendFormat(TEXT("Not adding component %s from writer %s."),
					//	component.get_Name(), writer.get_Name());
					//OutputWriter::WriteLine(message);
				}
			}
		}

		//OutputWriter::WriteLine(TEXT("Calling SetBackupState"));
		// Issue #29: trying to figure out if using VSS_BT_INCREMENTAL causes a problem
		CHECK_HRESULT(pBackupComponents->SetBackupState(TRUE, FALSE, VSS_BT_FULL, FALSE));

		//OutputWriter::WriteLine(TEXT("Calling PrepareForBackup"));
		CComPtr<IVssAsync> pPrepareForBackupResults;
		CHECK_HRESULT(pBackupComponents->PrepareForBackup(&pPrepareForBackupResults));

		//OutputWriter::WriteLine(TEXT("Waiting for call to PrepareForBackup to finish..."));
		CHECK_HRESULT(pPrepareForBackupResults->Wait());

		HRESULT hrPrepareForBackupResults;
		CHECK_HRESULT(pPrepareForBackupResults->QueryStatus(&hrPrepareForBackupResults, NULL));

		if (hrPrepareForBackupResults != VSS_S_ASYNC_FINISHED)
		{
			throw new CVSSCopyException(TEXT("Prepare for backup failed."));
		}

		//OutputWriter::WriteLine(TEXT("Call to PrepareForBackup finished."));

		SYSTEMTIME snapshotTime;
		::GetSystemTime(&snapshotTime);

		//bWorked = ::SetConsoleCtrlHandler(CtrlHandler, TRUE);

		//if (!bWorked)
		//{
		//	OutputWriter::WriteLine(TEXT("Unable to set control handler. Ctrl-C and Ctrl-Break may have undesirable results."),
		//		VERBOSITY_THRESHOLD_NORMAL);
		//}

		//OutputWriter::WriteLine(TEXT("Calling DoSnapshotSet"));
		CComPtr<IVssAsync> pDoSnapshotSetResults;
		CHECK_HRESULT(pBackupComponents->DoSnapshotSet(&pDoSnapshotSetResults));

		//OutputWriter::WriteLine(TEXT("Waiting for call to DoSnapshotSet to finish..."));

		CHECK_HRESULT(pDoSnapshotSetResults->Wait());

		bSnapshotCreated = true;
		HRESULT hrDoSnapshotSetResults;
		CHECK_HRESULT(pDoSnapshotSetResults->QueryStatus(&hrDoSnapshotSetResults, NULL));

		if (hrDoSnapshotSetResults != VSS_S_ASYNC_FINISHED)
		{
			throw new CVSSCopyException(L"DoSnapshotSet failed.");
		}

		//OutputWriter::WriteLine(TEXT("Call to DoSnapshotSet finished."));

		//OutputWriter::WriteLine(TEXT("Calling GetSnapshotProperties"));
		VSS_SNAPSHOT_PROP snapshotProperties;
		CHECK_HRESULT(pBackupComponents->GetSnapshotProperties(snapshotId, &snapshotProperties));

		CString wszSource;
		CalculateSourcePath(
			snapshotProperties.m_pwszSnapshotDeviceObject,
			options.get_Source(),
			wszVolumePathName,
			wszSource
			);

		//message.Empty();
		//message.AppendFormat(TEXT("Recursively creating destination directory %s."),
		//	options.get_Destination());
		//OutputWriter::WriteLine(message);

		Utilities::CreateDirectory(options.get_Destination());

		OutputWriter::WriteLine(TEXT("Calling CopyRecursive"));

		vector<CCopyFilter*> filters;

		if (options.get_BackupType() == VSS_BT_FULL)
		{
			filters.push_back(new CIncludeAllCopyFilter());
		}
		else if (options.get_BackupType() == VSS_BT_INCREMENTAL)
		{
			filters.push_back(new CModifiedSinceCopyFilter(lastBackupTime, options.get_SkipDenied()));
		}

		filters.push_back(new CFilespecCopyFilter(options.get_Filespecs()));

		CCopyAction copyAction(wszSource, options.get_Destination(), options.get_SkipDenied(), filters);
		ProcessDirectory(wszSource, copyAction, TEXT(""), options.get_Recursive(), options.get_IgnorePattern());

		for (unsigned int iFilter = 0; iFilter < filters.size(); ++iFilter)
		{
			delete filters[iFilter];
		}

		fileCount = copyAction.get_FileCount();
		directoryCount = copyAction.get_DirectoryCount();
		skipCount = copyAction.get_SkipCount();
		byteCount = copyAction.get_ByteCount();

		OutputWriter::WriteLine(TEXT("Calling BackupComplete"));
		CComPtr<IVssAsync> pBackupCompleteResults;
		CHECK_HRESULT(pBackupComponents->BackupComplete(&pBackupCompleteResults));

		OutputWriter::WriteLine(TEXT("Waiting for call to BackupComplete to finish..."));
		CHECK_HRESULT(pBackupCompleteResults->Wait());

		HRESULT hrBackupCompleteResults;
		CHECK_HRESULT(pBackupCompleteResults->QueryStatus(&hrBackupCompleteResults, NULL));

		if (hrBackupCompleteResults != VSS_S_ASYNC_FINISHED)
		{
			throw new CVSSCopyException(TEXT("Completion of backup failed."));
		}

		OutputWriter::WriteLine(TEXT("Call to BackupComplete finished."));

		bAbnormalAbort = false;

		//if (options.get_StateFile() != NULL)
		//{
		//	OutputWriter::WriteLine(TEXT("Calling SaveAsXML"));
		//	CComBSTR bstrBackupDocument;
		//	CHECK_HRESULT(pBackupComponents->SaveAsXML(&bstrBackupDocument));

		//	if (options.get_BackupType() == VSS_BT_FULL)
		//	{
		//		backupState.set_LastFullBackupTime(&snapshotTime);
		//	}
		//	else if (options.get_BackupType() == VSS_BT_INCREMENTAL)
		//	{
		//		backupState.set_LastIncrementalBackupTime(&snapshotTime);
		//	}
		//	else
		//	{
		//		throw new CVSSCopyException(TEXT("Unsupported backup type."));
		//	}

		//	backupState.Save(options.get_StateFile(), bstrBackupDocument);
		//}
	}
	catch (CComException* e)
	{
		Cleanup(bAbnormalAbort, bSnapshotCreated, pBackupComponents, snapshotSetId);
		CString message;
		CString file;
		//e->get_File(file);
		//message.Format(TEXT("There was a COM failure 0x%x - %s (%d)"),
		//	e->get_Hresult(), file, e->get_Line());
		//OutputWriter::WriteLine(message, VERBOSITY_THRESHOLD_UNLESS_SILENT);
		return 1;
	}
	catch (CVSSCopyException* e)
	{
		Cleanup(bAbnormalAbort, bSnapshotCreated, pBackupComponents, snapshotSetId);
		OutputWriter::WriteLine(e->get_Message(), VERBOSITY_THRESHOLD_UNLESS_SILENT);
		return 1;
	}
	catch (CParseOptionsException* e)
	{
		Cleanup(bAbnormalAbort, bSnapshotCreated, pBackupComponents, snapshotSetId);
		CString message;
		message.AppendFormat(TEXT("Error: %s\n"), e->get_Message());
		OutputWriter::WriteLine(message, VERBOSITY_THRESHOLD_UNLESS_SILENT);
		OutputWriter::WriteLine(COptions::get_Usage(), VERBOSITY_THRESHOLD_UNLESS_SILENT);
		return 2;
	}
}

bool VssBackup::ShouldAddComponent(CWriterComponent& component)
{
	// Component should not be added if
	// 1) It is not selectable for backup and 
	// 2) It has a selectable ancestor
	// Otherwise, add it. 

	if (component.get_SelectableForBackup())
	{
		return true;
	}

	return !component.get_HasSelectableAncestor();
}

void VssBackup::Cleanup(bool bAbnormalAbort, bool bSnapshotCreated, CComPtr<IVssBackupComponents> pBackupComponents, GUID snapshotSetId)
{
	if (pBackupComponents == NULL)
	{
		return;
	}

	if (bAbnormalAbort)
	{
		pBackupComponents->AbortBackup();
	}
	if (bSnapshotCreated)
	{
		LONG cDeletedSnapshots;
		GUID nonDeletedSnapshotId;
		pBackupComponents->DeleteSnapshots(snapshotSetId, VSS_OBJECT_SNAPSHOT_SET, TRUE,
			&cDeletedSnapshots, &nonDeletedSnapshotId);
	}
}

void VssBackup::CalculateSourcePath(LPCTSTR wszSnapshotDevice, LPCTSTR wszBackupSource, LPCTSTR wszMountPoint, CString& output)
{
	CString backupSource(wszBackupSource);
	CString mountPoint(wszMountPoint);

	CString subdirectory = backupSource.Mid(mountPoint.GetLength());

	Utilities::CombinePath(wszSnapshotDevice, subdirectory, output);
}

void VssBackup::ProcessDirectory(LPCTSTR srcbase, CDirectoryAction& action, LPCTSTR directory, bool recursive, wregex* ignorePattern)
{
	WIN32_FIND_DATA findData;
	HANDLE hFindHandle;

	CString srcdir;
	Utilities::CombinePath(srcbase, directory, srcdir);

	if (!ShouldProcess(ignorePattern, srcdir))
	{
		return;
	}

	action.VisitDirectoryInitial(directory);

	CString pattern;
	Utilities::CombinePath(srcdir, TEXT("*"), pattern);

	Utilities::FixLongFilenames(pattern);

	hFindHandle = ::FindFirstFile(pattern, &findData);
	if (hFindHandle != INVALID_HANDLE_VALUE)
	{
		BOOL done = false;
		while (!done)
		{
			if ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
			{
				if (recursive)
				{
					if (Utilities::AreEqual(findData.cFileName, L".") || Utilities::AreEqual(findData.cFileName, L".."))
					{
						// Do nothing
					}
					else
					{
						CString subdirectory;
						Utilities::CombinePath(directory, findData.cFileName, subdirectory);
						if (!ShouldProcess(ignorePattern, srcbase, subdirectory))
						{
							continue;
						}
						ProcessDirectory(srcbase, action, subdirectory, recursive, ignorePattern);
					}
				}
			}
			else
			{
				CString file;
				Utilities::CombinePath(directory, findData.cFileName, file);
				if (!ShouldProcess(ignorePattern, srcbase, file)) continue;
				action.VisitFile(file);
			}

			BOOL worked = ::FindNextFile(hFindHandle, &findData);

			if (!worked)
			{
				int error = GetLastError();

				if (error == ERROR_NO_MORE_FILES)
				{
					done = true;
				}
				else
				{
					CString errorMessage;
					Utilities::FormatErrorMessage(error, errorMessage);
					CString message;
					message.AppendFormat(TEXT("There was an error calling FindNextFile. Path: %s Error: %s"),
						pattern, errorMessage);
					throw new CVSSCopyException(message.GetString());
				}
			}
		}
	}
	else
	{
		int error = GetLastError();

		if (error != ERROR_FILE_NOT_FOUND)
		{
			CString errorMessage;
			Utilities::FormatErrorMessage(error, errorMessage);
			CString message;
			message.AppendFormat(TEXT("There was an error calling FindFirstFile. Path: %s Error: %s"),
				pattern, errorMessage);
			throw new CVSSCopyException(message.GetString());
		}
	}
	::FindClose(hFindHandle);


	// Important to put this after FindClose, since otherwise there's still an 
	// open handle to the directory, and that can interfere with (e.g.) directory
	// deletion
	action.VisitDirectoryFinal(directory);
}

bool VssBackup::ShouldProcess(wregex* ignorePattern, const CString& directory, const CString& name)
{
	CString fullPath;
	Utilities::CombinePath(directory, name, fullPath);
	return ShouldProcess(ignorePattern, fullPath);
}

bool VssBackup::ShouldProcess(wregex* ignorePattern, const CString& path)
{
	if (!ignorePattern)
	{
		return true;
	}
	bool ignore = IsMatch(ignorePattern, path);
	if (ignore)
	{
		CString message;
		message.Format(TEXT("Ignoring %s"), path);
		OutputWriter::WriteLine(message);
	}
	return !ignore;
}

bool VssBackup::IsMatch(wregex* pattern, const CString& input)
{
	return regex_match(input.GetString(), *pattern);
}
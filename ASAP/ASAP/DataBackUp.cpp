#include "stdafx.h"
#include "DataBackUp.h"
#include "COptions.h"
#include "vssBackup.h"

using namespace System::Runtime::InteropServices;
using namespace System::Diagnostics;
using namespace System::Reflection;
using namespace System::IO;

namespace ASAP {
	DataBackUp::DataBackUp(JobStruct^ job)
	{
		_job = job;
		mainFormPtr = (MainForm^)Application::OpenForms[0];
		updateJobStartupInfo();
	}

	// You'll need to add using 'System.Security.AccessControl' for this code
	void DataBackUp::DeepCopy(DirectoryInfo^ source, DirectoryInfo^ target)
	{
		if (UserHasAccess(source))
		{
			//System::Type^ rights = dirSecurity->AccessRightType;
			array<DirectoryInfo^>^ directories = source->GetDirectories();

			if (directories->Length > 0)
			{
				for each (DirectoryInfo^ dir in directories)
				{
					DirectoryInfo^ SubDir = target->CreateSubdirectory(dir->Name);

					DeepCopy(dir, SubDir);
				}
			}
			else
			{
				target->Create();
			}

			for each(FileInfo^ file in source->GetFiles())
			{
				String^ targetFileName = Path::Combine(target->FullName, file->Name);
				if (targetFileName->Length <= 254)
				{
					mainFormPtr->Invoke(gcnew Action<String ^>(mainFormPtr, &MainForm::setCurrentBackupFile), targetFileName);

					try
					{
						file->CopyTo(targetFileName, true);
						mainFormPtr->Invoke(gcnew Action(mainFormPtr, &MainForm::incrementFileBackUpCount));
					}
					catch (Exception^ pe)
					{
						//Write to log file
						mainFormPtr->Invoke(gcnew Action(mainFormPtr, &MainForm::incrementFileMissedCount));
					}
				}
				else
				{
					// Write in log file
					mainFormPtr->Invoke(gcnew Action(mainFormPtr, &MainForm::incrementFileMissedCount));
				}
			}
		}
	}

	void DataBackUp::updateJobStartupInfo(void)
	{
		mainFormPtr->Invoke(gcnew Action<String ^>(mainFormPtr, &MainForm::setCurrentOperation), _job->Name());
		mainFormPtr->Invoke(gcnew Action(mainFormPtr, &MainForm::setBackUpStartTime));

		mainFormPtr->Invoke(gcnew Action<bool>(mainFormPtr, &MainForm::EnableDisableJobListBoxbuttons), false);
	}

	bool DataBackUp::UserHasAccess(DirectoryInfo^ folderPath)
	{
		try
		{
			// Attempt to get a list of security permissions from the folder. 
			// This will raise an exception if the path is read only or do not have access to view the permissions. 
			folderPath->GetDirectories();
				
			return true;
		}
		catch (Exception^)
		{
			//Log error
			return false;
		}
	}

	void DataBackUp::performVSSBackup()
	{
		String^ strArgument = "/" + _job->Name();
		String^ exePath = Path::GetDirectoryName(Assembly::GetEntryAssembly()->Location) + "\\VSSCopy.Exe";

		Process::Start(exePath, strArgument);
	}
}
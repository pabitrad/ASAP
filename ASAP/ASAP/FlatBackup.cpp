#include "stdafx.h"
#include "FlatBackup.h"

namespace ASAP {
	FlatBackup::FlatBackup(JobStruct^ job) : DataBackUp(job)
	{
		job = nullptr;
		catchMessage = "";
		backedup = 0;
		totalbytes = 0;
		failedtobackup = 0;
		alreadybackedup = 0;
	}

	void FlatBackup::StartBackUp(void)
	{
		if (_job != nullptr)
		{
			ArrayList^ sourceLocations = _job->Files();
			for each(String^ sourceLocation in sourceLocations)
			{
				String^ targetLocation = GetTagetLocation(sourceLocation);

				DeepCopy(gcnew DirectoryInfo(sourceLocation), gcnew DirectoryInfo(targetLocation));
			}
		}
	}

	String^ FlatBackup::GetTagetLocation(String^ sourceLocation)
	{
		String^ targetLoc = nullptr;
		int index = sourceLocation->IndexOf("\\");
		if (index >= 0)
		{
			String^ modifiedSourceLocation = sourceLocation->Remove(0, index);
			targetLoc = gcnew String(_job->Path() + _job->Name() + "\\" + DateTime::Today.ToString("MMddyyyy") + modifiedSourceLocation + "\\");
		}

		return targetLoc;
	}
}
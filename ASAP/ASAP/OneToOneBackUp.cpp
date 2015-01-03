#include "stdafx.h"
#include "OneToOneBackUp.h"

namespace ASAP {
	OneToOneBackUp::OneToOneBackUp(JobStruct^ job) : DataBackUp(job)
	{
	}

	void OneToOneBackUp::StartBackUp(void)
	{
		if (_job != nullptr)
		{
			String^ targetLocation = GetTagetLocation();
			String^ sourcePath = (String ^)(_job->Files()->ToArray()[0]);

			DeepCopy(gcnew DirectoryInfo(sourcePath), gcnew DirectoryInfo(targetLocation));
		}
	}

	String^ OneToOneBackUp::GetTagetLocation()
	{
		String^ path = (String ^) (_job->Files()->ToArray()[0]);

		String^ delimStr = "\\";
		array<Char>^ delimiter = delimStr->ToCharArray();
		array<String^>^ folders = path->Split(delimiter, StringSplitOptions::RemoveEmptyEntries);

		return _job->Path() + "\\" + folders[folders->Length - 1];
	}
}
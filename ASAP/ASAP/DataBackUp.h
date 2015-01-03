#pragma once
#include "JobStruct.h"
#include "MainForm.h"

using namespace System::IO;
using namespace System::Security::AccessControl;

namespace ASAP {
	ref class DataBackUp
	{
		public:
		   DataBackUp(JobStruct^ job);
		   virtual void StartBackUp(void) = 0;
		   void DeepCopy(DirectoryInfo^ source, DirectoryInfo^ target);

		protected:
			JobStruct^ _job;

		private:
			MainForm^ mainFormPtr;

			void updateJobStartupInfo(void);
			bool UserHasAccess(DirectoryInfo^ folderPath);
	};
}

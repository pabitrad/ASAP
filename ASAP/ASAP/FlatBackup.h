#pragma once
#include "DataBackUp.h"

namespace ASAP {
	ref class FlatBackup : public DataBackUp 
	{
		public:
			void StartBackUp(void) override;

		private:
			JobStruct^ job;
			String^ catchMessage;
			int backedup;
			long totalbytes;
			int failedtobackup;
			int alreadybackedup;
		public:
			FlatBackup(JobStruct^ job);
			String^ GetTagetLocation(String^ sources);
	};
}
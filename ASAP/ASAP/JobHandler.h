#pragma once
#include "JobStruct.h"

namespace ASAP {
	using namespace System;

	ref class JobHandler
	{
		private: String^ jobpath = "jobs";
				 ArrayList^ _jobs = gcnew ArrayList;

		public:
			JobHandler();
			bool Save(JobStruct^ job);
			void loadAll();
			void add(JobStruct^ job);
			JobStruct^ JobHandler::load(String^ file);
			ArrayList^ Jobs();
			void StartJob(String^ jobName);
			void deleteJob(String^ jobName);
	};
}
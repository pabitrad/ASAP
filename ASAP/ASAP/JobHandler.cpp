#include "stdafx.h"
#include "JobHandler.h"

using namespace System;
using namespace System::IO;

using namespace System::Windows::Forms;
namespace ASAP {

	JobHandler::JobHandler()
	{
		if (!Directory::Exists(jobpath)) Directory::CreateDirectory(jobpath);
	}

	ArrayList^ JobHandler::Jobs()
	{
		return _jobs;
	}

	bool JobHandler::Save(JobStruct^ job)
	{
		StreamWriter^ stream = gcnew StreamWriter(jobpath + "/" + job->Name() + ".job", false);
		bool b = false;
		if (stream != nullptr)
		{
			b = job->Save(stream);
			stream->Close();
		}
		return b;
	}

	JobStruct^ JobHandler::load(String^ file)
	{
		JobStruct^ myjob = gcnew JobStruct();

		StreamReader^ stream = gcnew StreamReader(file);
		if (stream != nullptr)
		{
			myjob->Load(stream);
			stream->Close();
		}

		return myjob;
	}

	void JobHandler::loadAll()
	{
		if (!Directory::Exists(jobpath)) Directory::CreateDirectory(jobpath);
		array<String^>^ files = Directory::GetFiles(jobpath);
		for each(String^ file in files)
		{
			Jobs()->Add(load(file));
		}
	}
	void JobHandler::add(JobStruct^ job)
	{
		Jobs()->Add(job);
		//String^ tmp = nullptr;
		//
		//ListViewItem^ lvi = gcnew ListViewItem(job->Name());
		//if (job->Type() == "flat")
		//{
		//	lvi->SubItems->Add("Flat file backup");
		//}
		//else
		//{
		//	lvi->SubItems->Add("Disk backup (VHD)");
		//}
		//lvi->SubItems->Add(job->Path());


		//if (job->Everyday() == true)
		//{
		//	lvi->SubItems->Add("Everyday @ " + job->Time().ToString("hh:mm tt"));
		//}
		//else
		//{
		//	tmp = job->DayNames();
		//	lvi->SubItems->Add(tmp + " @ " + job->Time().ToString("hh:mm y"));
		//}

		//if (job->LastRun() == DateTime::MinValue)
		//{
		//	lvi->SubItems->Add("Never");
		//}
		//else
		//{
		//	
		//	lvi->SubItems->Add(job->LastRun().ToString("MM/dd/yyy hh:mm:ss tt"));
		//}
	}

	void JobHandler::StartJob(String^ jobName)
	{
		JobStruct^ selectedJob = nullptr;
		for each (JobStruct^ var in Jobs())
		{
			if (var->Name() == jobName)
			{
				selectedJob = var;
				break;
			}
		}

		if (selectedJob != nullptr)
		{
			selectedJob->Executejob();
		}
	}

	void JobHandler::deleteJob(String^ jobName)
	{
		String^ jobFileName = jobpath + "/" + jobName + ".job";
		File::Delete(jobFileName);
	}
}

#include "stdafx.h"
#include "DataBackUp.h"
#include "OneToOneBackUp.h"
#include "FlatBackup.h"
#include "JobStruct.h"

namespace ASAP {
	JobStruct::JobStruct(void){
		_Days = gcnew array<bool^>(7){ false, false, false, false, false, false, false };
		_Jobtype = "Flat File Backup";
		_obj = gcnew Object();
	}

	String^ JobStruct::Type()
	{
		return _Jobtype;
	}

	void JobStruct::Type(String^ s)
	{
		_Jobtype = s;
	}

	String^ JobStruct::Name()
	{
		return _Name;
	}
	
	void JobStruct::Name(String^ s)
	{
		_Name = s;
	}
	
	bool JobStruct::Schedule()
	{
		return _Schedule;
	}
	
	void JobStruct::Schedule(bool b)
	{
		_Schedule = b;
	}
	
	TimeSpan JobStruct::Time()
	{
		//return _Time - _Time.Date;
		return _Time;
	}
	
	void JobStruct::Time(TimeSpan d)
	{
		_Time = d;
	}

	DateTime JobStruct::LastRun()
	{
		return _LastRun;
	}
	
	void JobStruct::LastRun(DateTime d)
	{
		_LastRun = d;
	}
	
	bool JobStruct::Logging()
	{
		return _Logging;
	}
	
	void JobStruct::Logging(bool b)
	{
		_Logging = b;
	}
	
	String^ JobStruct::LoggingPath()
	{
		return _LoggingPath;
	}
	
	void JobStruct::LoggingPath(String^ s)
	{
		_LoggingPath = s;
	}
	
	bool JobStruct::EmailLogging()
	{
		return _EmailLogging;
	}
	
	void JobStruct::EmailLogging(bool b)
	{
		_EmailLogging = b;
	}
	
	String^ JobStruct::EmailAdress()
	{
		return _EmailAdress;
	}
	
	void JobStruct::EmailAdress(String^ s)
	{
		_EmailAdress = s;
	}
	
	String^ JobStruct::Path()
	{
		return _Path;
	}
	
	void JobStruct::Path(String^ s)
	{
		_Path = s;
	}
	
	String^ JobStruct::SavingType()
	{
		return _SavingType;
	}
	
	void JobStruct::SavingType(String^ s)
	{
		_SavingType = s;
	}

	void JobStruct::Days(int d, bool^ b)
	{
		_Days[d] = b;
	}

	bool^ JobStruct::Days(int d)
	{
		return _Days[d];
	}

	array<bool^>^ JobStruct::Days()
	{
		return _Days;
	}

	bool JobStruct::Everyday()
	{
		bool b = true;
		for each (bool var in Days())
		{
			b = var;
			if (var == false) break;
		}
		return b;
	}

	String^ JobStruct::DayNames()
	{
		String^ tmp;
		for (DayOfWeek d = DayOfWeek::Sunday; d <= DayOfWeek::Saturday;d++)
		{
			bool^ b = Days(int(d));
			if (*b)
			{
				tmp += " " + d.ToString();
			}
		}

		return tmp;
	}

	void JobStruct::DayNames(String^ s)
	{
		for (DayOfWeek d = DayOfWeek::Sunday; d <= DayOfWeek::Saturday;d++)
		{
			if (s == d.ToString())
			{
				Days(int(d), true);
				break;
			}
		}
	}

	ArrayList^ JobStruct::Files(){
		return _Files;
	}
	void JobStruct::Files(ArrayList^ fa){
		_Files = fa;
	}
	void JobStruct::Files(String^ s, bool b){
		if (b)
		{
			if (!_Files->Contains(s))
				_Files->Add(s);
		}
		else
		{
			_Files->Remove(s);
		}
	}
}


bool ASAP::JobStruct::Save(System::IO::StreamWriter^ stream)
{
//	System::IO::StreamWriter^ stream = gcnew System::IO::StreamWriter(jobpath + "/" + job.Name + ".job", false))
	{
		stream->WriteLine("type=" + Type());
		stream->WriteLine("name=" + Name());
		if (Schedule() == true)
		{
			stream->WriteLine("schedule=true");
			String^ tmp = String::Empty;
//			for each(bool^ in Days())
			for (DayOfWeek d = DayOfWeek::Sunday; d <= DayOfWeek::Saturday; d++)
			{
				bool^ b = Days(int(d));
				if (*b)
				{
					tmp += " " + d.ToString();
				}
			}

			stream->WriteLine("days=" + tmp);
			stream->WriteLine("backuptime=" + Time());
		}
		else stream->WriteLine("schedule=false");

		if (Logging() == true)
		{
			stream->WriteLine("logging=true");
			stream->WriteLine("loggingpath=" + LoggingPath());
		}
		else stream->WriteLine("logging=false");

		if (EmailLogging() == true)
		{
			stream->WriteLine("email_logging=true");
			stream->WriteLine("email=" + EmailAdress());
		}
		else stream->WriteLine("email_logging=false");

//		if (Type() == "flat")
		{
			String^ tmp = nullptr;
			stream->WriteLine("path=" + Path());
			stream->WriteLine("saving_type=" + SavingType());
			for each(String^ file in Files())
			{
				if (tmp == nullptr) tmp += file;
				else tmp += "|" + file;
			}
			stream->WriteLine("files=" + tmp);
		}
		//else
		//{
		//	stream->WriteLine("path=" + Path());
		//	tmp = null;
		//	foreach(string drive in job.Drives)
		//	{
		//		if (tmp == null) tmp += drive;
		//		else tmp += " " + drive;
		//	}
		//	stream->WriteLine("drives=" + tmp);
		//}
		DateTime lastRun = LastRun();
		if (lastRun != DateTime::MinValue)
		{
			stream->WriteLine("last run=" + lastRun.ToString());
		}

		CreateTimer();
	}
	return false;
}

bool ASAP::JobStruct::Load(System::IO::StreamReader^ stream)
{
	{
		String^ line;
		while ((line = stream->ReadLine()) != nullptr)
		{
			array<String^>^ tmp = line->Split('=');
			if (tmp[0] == "type") Type(tmp[1]);
			else if (tmp[0] == "name") Name(tmp[1]);
			else if (tmp[0] == "schedule")
			{
				if (tmp[1] == "true") Schedule(true);
				else Schedule(false);
			}
			else if (tmp[0] == "backuptime") Time(TimeSpan::Parse(tmp[1]));
			else if (tmp[0] == "days")
			{
				array<String^>^ days = tmp[1]->Trim()->Split(' ');
				for each(String^ d in  days)
				{
					DayNames(d);
				}
			}
			else if (tmp[0] == "last run") LastRun(DateTime::Parse(tmp[1]));
			else if (tmp[0] == "logging")
			{
				if (tmp[1] == "true") Logging(true);
				else Logging(false);
			}
			else if (tmp[0] == "logging_path") LoggingPath(tmp[1]);
			else if (tmp[0] == "email_logging")
			{
				if (tmp[1] == "true") EmailLogging(true);
				else EmailLogging(false);
			}
			else if (tmp[0] == "email") EmailAdress(tmp[1]);
			else if (tmp[0] == "path") Path(tmp[1]);
			else if (tmp[0] == "saving_type") SavingType(tmp[1]);
			else if (tmp[0] == "files")
			{
				array<String^>^ files = tmp[1]->Split('|');
				for each(String^ f in files)
				{
					Files(f,true);
				}
			}
			else if (tmp[0] == "drives")
			{
				array<String^>^ drives = tmp[1]->Split(' ');
				for each(String^ d in drives)
				{
//					Drives(d);
				}
			}
		}

		CreateTimer();
	}
	return false;
}

void ASAP::JobStruct::JobTimerCallBack(Object^ state)
{
	Monitor::Enter(_obj);
	try
	{
		// execute the job in intervals determined by the methd
		JobStruct^ jobPtr = (JobStruct ^)(state);
		if (jobPtr != nullptr)
		{
			bool^ bReturn = jobPtr->IsScheduledForToday();
			if (*bReturn)
			{
				jobPtr->Executejob();
			}
		}
	}
	catch (System::Exception^ pe)
	{
		//Log error message
	}
	Monitor::Exit(_obj);
}

bool^ ASAP::JobStruct::IsScheduledForToday()
{
	return Days((int)DateTime::Today.DayOfWeek);
}

void ASAP::JobStruct::Executejob()
{
	DataBackUp^ backUp = nullptr;
	if (Type() == "One to One")
	{
		backUp = gcnew OneToOneBackUp(this);
	}
	else if (Type() == "Flat File Backup")
	{
		backUp = gcnew FlatBackup(this);
	}

	if (backUp != nullptr)
	{
		BackgroundWorker^ backUpBackGroundWorker = gcnew BackgroundWorker();
		backUpBackGroundWorker->DoWork += gcnew DoWorkEventHandler(bgWorker_DoWork);
		backUpBackGroundWorker->RunWorkerCompleted += gcnew RunWorkerCompletedEventHandler(bgWorker_RunWorkerCompleted);
		backUpBackGroundWorker->RunWorkerAsync(backUp);
	}
}

void ASAP::JobStruct::CreateTimer()
{
	if (_Days->Length > 0)
	{
		TimeSpan currentTime = DateTime::Now - DateTime::Now.Date;
		TimeSpan timeDiff = this->Time() - currentTime;

		if (currentTime > this->Time())  // crosses over midnight
			timeDiff += TimeSpan::FromTicks(TimeSpan::TicksPerDay);
		int totalMilliseconds = timeDiff.TotalMilliseconds;

		_jobTimer = gcnew System::Threading::Timer(gcnew TimerCallback(JobTimerCallBack), this, totalMilliseconds, 24 * 60 * 60 * 1000);
	}
}

void ASAP::JobStruct::bgWorker_DoWork(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
{
	DataBackUp^ backUp = (DataBackUp^)e->Argument;
	backUp->StartBackUp();
}

void ASAP::JobStruct::bgWorker_RunWorkerCompleted(Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e)
{
	MainForm^ ptrMainForm = (MainForm^)Application::OpenForms[0];
	ptrMainForm->Invoke(gcnew Action(ptrMainForm, &MainForm::markJobCompleted));
}
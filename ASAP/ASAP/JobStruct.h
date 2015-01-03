#pragma once
namespace ASAP {
	using namespace System;
	using namespace System::Collections;
	using namespace System::Threading;

	ref class JobStruct
	{
	public:
		JobStruct(void);
	private:
		String^ _Jobtype;
		String^ _Name;
		bool _Schedule;
		array<bool^>^ _Days;
		TimeSpan _Time;
		DateTime _LastRun;

		bool _Logging;
		String^ _LoggingPath;
		bool _EmailLogging;
		String^ _EmailAdress;

		String^ _Path;
		String^ _SavingType;
		ArrayList^ _Files = gcnew ArrayList;
		ArrayList^ _Drives = gcnew ArrayList;

		System::Threading::Timer^ _jobTimer;
		static Object^ _obj;

	public:
		String^ Type();
		void Type(String^ s);
		String^ Name();
		void Name(String^ s);
		bool Schedule();
		void Schedule(bool b);
		TimeSpan Time();
		void Time(TimeSpan d);
		DateTime LastRun();
		void LastRun(DateTime d);
		bool Logging();
		void Logging(bool b);
		String^ LoggingPath();
		void LoggingPath(String^ s);
		bool EmailLogging();
		void EmailLogging(bool b);
		String^ EmailAdress();
		void EmailAdress(String^ s);
		String^ Path();
		void Path(String^ s);
		String^ SavingType();
		void SavingType(String^ s);
		void Days(int d, bool^ b);
		bool^ Days(int d);
		array<bool^>^ Days();
		bool Save(System::IO::StreamWriter^ stream);
		bool Load(System::IO::StreamReader^ stream);
		bool Everyday();
		String^ DayNames();
		void DayNames(String^ s);
		void Files(ArrayList^ fa);
		ArrayList^ Files();
		void Files(String^ s, bool b);
		void Executejob(void);
		bool^ IsScheduledForToday();
		void CreateTimer();
		static void bgWorker_DoWork(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
		static void bgWorker_RunWorkerCompleted(Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e);
		static void JobTimerCallBack(Object^ state);
	};
}
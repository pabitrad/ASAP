#include "stdafx.h"
#include "MainForm.h"
using namespace System::Globalization;

namespace ASAP {
	void MainForm::setCurrentOperation(String^ jobName)
	{
		lblCurrentOperation->Text = jobName;
	}

	void MainForm::setBackUpStartTime(void)
	{
		lblBackupStartTime->Text = DateTime::Now.ToString("MM/dd/yyyy HH:mm:ss", CultureInfo::InvariantCulture);
		lblNoOfFilesBackedUp->Text = "0";
		lblNoOfFilesMissed->Text = "0";
	}

	void MainForm::incrementFileBackUpCount(void)
	{
		int filebackUpCount = Convert::ToInt32(lblNoOfFilesBackedUp->Text) + 1;
		lblNoOfFilesBackedUp->Text = filebackUpCount.ToString();
	}

	void MainForm::incrementFileMissedCount(void)
	{
		int fileMissedCount = Convert::ToInt32(lblNoOfFilesMissed->Text) + 1;
		lblNoOfFilesMissed->Text = fileMissedCount.ToString();
	}

	void MainForm::setCurrentBackupFile(String^ backUpFileName)
	{
		lblCurrentFile->Text = backUpFileName;
	}

	void MainForm::markJobCompleted()
	{
		MessageBox::Show("Job completed successfully", "Complete");
		resetCurrentOperation();
	}

	void MainForm::EnableDisableJobListBoxbuttons(bool bEnable)
	{
		btnEditSavesSet->Enabled = bEnable;
		btnRunSavedSetNow->Enabled = bEnable;
		btnDeleteSavedSet->Enabled = bEnable;
	}

	void MainForm::resetCurrentOperation()
	{
		lblCurrentOperation->Text = "Idle";
		lblCurrentFile->Text = String::Empty;
		lblNoOfFilesBackedUp->Text = String::Empty;
		lblBackupStartTime->Text = String::Empty;
		lblNoOfFilesMissed->Text = String::Empty;
	}

	void MainForm::CheckUncheckEveryDay(bool bChecked)
	{
		cbSunday->Checked = bChecked;
		cbMonday->Checked = bChecked;
		cbTuesday->Checked = bChecked;
		cbWednesday->Checked = bChecked;
		cbThursday->Checked = bChecked;
		cbFriday->Checked = bChecked;
		cbSaturday->Checked = bChecked;
	}

	void MainForm::initializeFileSelection(void)
	{
		trSelect->Nodes->Clear();
		// get the logical drives
		array<String^>^ drives = Directory::GetLogicalDrives();

		for (int i = 0; i < drives->Length; i++)
		{
			String^ name = dynamic_cast<String^>(drives->GetValue(i));
			TreeNode^ tn = gcnew TreeNode(name);
			trSelect->Nodes->Add(tn);
			//tn->Nodes->Add(gcnew TreeNode("<dummy>"));
			tn->Nodes->Add(gcnew TreeNode(""));
		}
	}

	void MainForm::btnEditSavesSet_Click(System::Object^  sender, System::EventArgs^  e)
	{
		this->tabControl1->SelectedTab = tabPage2;
	}

	void MainForm::btnReset_Click(System::Object^  sender, System::EventArgs^  e)
	{
		tbSetName->Text = String::Empty;
		rbFlatFile->Checked = true;
		initializeFileSelection();

		if (cbSchedule->Checked)
		{
			cbSchedule->Checked = false;
			CheckUncheckEveryDay(false);
			EnableDays(false);
			tbDes->Text = String::Empty;
			dtpTime->Text = "12:00 AM";
		}
	}

	void MainForm::EnableDays(bool bEnabled)
	{
		cbSunday->Enabled = bEnabled;
		cbMonday->Enabled = bEnabled;
		cbTuesday->Enabled = bEnabled;
		cbWednesday->Enabled = bEnabled;
		cbThursday->Enabled = bEnabled;
		cbFriday->Enabled = bEnabled;
		cbSaturday->Enabled = bEnabled;

		labelEveryday->Enabled = bEnabled;
	}

	void MainForm::addJobtoJobList(void)
	{
		ListViewItem^ l = lvBackupSet->Items->Add(Job->Name());
		l->SubItems->Add(Job->Type());
		l->SubItems->Add(Job->Path());

		TimeSpan whenToRun = Job->Time();
		l->SubItems->Add(whenToRun.ToString());

		DateTime lastRun = Job->LastRun();
		if (lastRun != DateTime::MinValue)
		{
			l->SubItems->Add(Job->LastRun().ToString());
		}
	}
}
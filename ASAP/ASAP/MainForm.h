#pragma once
#include "jobHandler.h"

namespace ASAP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
	JobHandler Jobs;
	private: System::Windows::Forms::ColumnHeader^  columnName;
	private: System::Windows::Forms::ColumnHeader^  clumnType;
	private: System::Windows::Forms::ColumnHeader^  columnDestination;
	private: System::Windows::Forms::ColumnHeader^  columnWhenRun;
	private: System::Windows::Forms::ColumnHeader^  columnLastRun;
	private: System::Windows::Forms::TreeView^  trSelect;
	private: System::Windows::Forms::ImageList^  imageList1;

	public:

		JobStruct^ Job = gcnew JobStruct;
		MainForm(void)
		{
			InitializeComponent();
			Jobs.loadAll();
			for each (JobStruct^ var in Jobs.Jobs())
			{
				 ListViewItem^ l = lvBackupSet->Items->Add(var->Name());
				 l->SubItems->Add(var->Type());
				 l->SubItems->Add(var->Path());

				 TimeSpan whenToRun = var->Time();
				 l->SubItems->Add(whenToRun.ToString());

				 DateTime lastRun = var->LastRun();
				 if (lastRun != DateTime::MinValue)
				 {
					 l->SubItems->Add(var->LastRun().ToString());
				 }
			}

			initializeFileSelection();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	internal: System::Windows::Forms::GroupBox^  groupBox14;
	protected: 
	internal: System::Windows::Forms::Label^  label9;
	internal: System::Windows::Forms::TextBox^  TextBox8;
	internal: System::Windows::Forms::CheckBox^  CheckBox4;
	internal: System::Windows::Forms::TextBox^  TextBox7;
	internal: System::Windows::Forms::Label^  label10;
	internal: System::Windows::Forms::Label^  label11;
	internal: System::Windows::Forms::TextBox^  textBox6;
	internal: System::Windows::Forms::Label^  label12;
	internal: System::Windows::Forms::TextBox^  textBox9;
	private: System::Windows::Forms::ListView^  lvBackupSet;
	internal:

	internal: 
	private: System::Windows::Forms::TabPage^  tabPage3;
	internal: System::Windows::Forms::GroupBox^  groupBox13;
	private: 
	internal: System::Windows::Forms::CheckBox^  CheckBox3;
	internal: System::Windows::Forms::Label^  label7;
	internal: System::Windows::Forms::TextBox^  textBox3;
	internal: System::Windows::Forms::Label^  label8;
	internal: System::Windows::Forms::TextBox^  textBox5;
	internal: System::Windows::Forms::GroupBox^  groupBox12;
	internal: System::Windows::Forms::ComboBox^  ComboBox2;
	internal: System::Windows::Forms::GroupBox^  groupBox11;
	internal: System::Windows::Forms::CheckBox^  CheckBox1;
	internal: System::Windows::Forms::TextBox^  TextBox2;
	private: System::Windows::Forms::RadioButton^  rbFlatFile;
	private: System::Windows::Forms::RadioButton^  rbVHD;
	internal: System::Windows::Forms::TextBox^  tbDes;
	private:
	internal:


	internal:

	internal: 


	private: 
	private: System::Windows::Forms::GroupBox^  groupBox4;
	internal: 
	internal: System::Windows::Forms::Button^  btnBrowseDes;
	private: 
	internal: System::Windows::Forms::Label^  lblDes;
	internal: System::Windows::Forms::CheckBox^  cbFavorite;
	private: System::Windows::Forms::RadioButton^  rbOnetoOne;
	internal:

	internal:

	internal: 
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::ProgressBar^  progressBar;
	private: System::Windows::Forms::Button^  btnSBrowse;
	private: System::Windows::Forms::TextBox^  copyLocation;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::ColumnHeader^  columnHeader3;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;
	private: System::Windows::Forms::ColumnHeader^  columnHeader4;
	private: System::Windows::Forms::TreeView^  treeView1;
	private: System::Windows::Forms::Button^  btnClose;
	private: System::Windows::Forms::Button^  btnOpen;
	private: System::Windows::Forms::GroupBox^  groupBox17;
	private: System::Windows::Forms::Button^  btnBrowse;
	private: System::Windows::Forms::TextBox^  txtboxVhdDir;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ListView^  listView3;
	private: System::Windows::Forms::GroupBox^  groupBox16;
	private: System::Windows::Forms::TabPage^  tabPage4;
	private: System::Windows::Forms::GroupBox^  groupBox15;
	private: System::Windows::Forms::Button^  btnCopy;
	internal: System::Windows::Forms::CheckBox^  cbDocuments;
	private: 
	internal: System::Windows::Forms::CheckBox^  cbDesktop;
	internal: System::Windows::Forms::CheckBox^  cbProfile;
private: System::Windows::Forms::Label^  lblTransferRate;
internal:

	internal: 
	private: System::Windows::Forms::TabPage^  tabPage2;
	internal: System::Windows::Forms::GroupBox^  groupBox10;
	internal: System::Windows::Forms::CheckBox^  cbModifyDate;
	internal: System::Windows::Forms::CheckBox^  cbArchiveBit;
	private:


	internal: System::Windows::Forms::GroupBox^  groupBox9;
	internal: System::Windows::Forms::CheckBox^  cbEncryption;


	internal: System::Windows::Forms::Label^  label6;
internal: System::Windows::Forms::TextBox^  tbEncryptionPass;



	internal: System::Windows::Forms::GroupBox^  groupBox8;
	internal: System::Windows::Forms::CheckBox^  cbLogging;
	internal: System::Windows::Forms::Label^  lblLogging;
	internal: System::Windows::Forms::TextBox^  tbLogPath;
	internal: System::Windows::Forms::CheckBox^  cbDefaultLog;
	private: System::Windows::Forms::GroupBox^  groupBox7;
private: System::Windows::Forms::TextBox^  tbSetName;

	internal: 

	internal: System::Windows::Forms::GroupBox^  groupBox6;
	private: 
	internal: System::Windows::Forms::DateTimePicker^  dtpTime;
	internal: System::Windows::Forms::CheckBox^  cbSaturday;
	internal: System::Windows::Forms::Label^  lblAt;
	internal: System::Windows::Forms::CheckBox^  cbTuesday;
private: System::Windows::Forms::LinkLabel^  labelEveryday;
internal:

	internal: 
	internal: System::Windows::Forms::CheckBox^  cbFriday;
	private: 
	internal: System::Windows::Forms::CheckBox^  cbSchedule;
	internal: System::Windows::Forms::CheckBox^  cbThursday;
	internal: System::Windows::Forms::CheckBox^  cbWednesday;
	internal: System::Windows::Forms::CheckBox^  cbSunday;
	internal: System::Windows::Forms::CheckBox^  cbMonday;
private: System::Windows::Forms::Button^  btnReset;
private: System::Windows::Forms::Button^  btnSave;
internal:

	internal: 

	private: System::Windows::Forms::GroupBox^  groupBox5;
	internal: System::Windows::Forms::Label^  label5;

internal:
	private:

	internal: 
	private: System::Windows::Forms::Label^  label20;
private: System::Windows::Forms::Button^  btnEditSavesSet;
private: System::Windows::Forms::Button^  btnDeleteSavedSet;


private: System::Windows::Forms::Label^  lblNoOfFilesMissed;

	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label17;
private: System::Windows::Forms::Button^  btnRunSavedSetNow;

private: System::Windows::Forms::Label^  lblNoOfFilesBackedUp;

private: System::Windows::Forms::Label^  lblBackupStartTime;

	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::Label^  lblCurrentFile;

private: System::Windows::Forms::Label^  lblCurrentOperation;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage5;
private: System::ComponentModel::IContainer^  components;

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->groupBox14 = (gcnew System::Windows::Forms::GroupBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->TextBox8 = (gcnew System::Windows::Forms::TextBox());
			this->CheckBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->TextBox7 = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->lvBackupSet = (gcnew System::Windows::Forms::ListView());
			this->columnName = (gcnew System::Windows::Forms::ColumnHeader());
			this->clumnType = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnDestination = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnWhenRun = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnLastRun = (gcnew System::Windows::Forms::ColumnHeader());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox13 = (gcnew System::Windows::Forms::GroupBox());
			this->CheckBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox12 = (gcnew System::Windows::Forms::GroupBox());
			this->ComboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox11 = (gcnew System::Windows::Forms::GroupBox());
			this->CheckBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->TextBox2 = (gcnew System::Windows::Forms::TextBox());
			this->rbFlatFile = (gcnew System::Windows::Forms::RadioButton());
			this->rbVHD = (gcnew System::Windows::Forms::RadioButton());
			this->tbDes = (gcnew System::Windows::Forms::TextBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->btnBrowseDes = (gcnew System::Windows::Forms::Button());
			this->lblDes = (gcnew System::Windows::Forms::Label());
			this->cbFavorite = (gcnew System::Windows::Forms::CheckBox());
			this->rbOnetoOne = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->progressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->btnSBrowse = (gcnew System::Windows::Forms::Button());
			this->copyLocation = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->btnClose = (gcnew System::Windows::Forms::Button());
			this->btnOpen = (gcnew System::Windows::Forms::Button());
			this->groupBox17 = (gcnew System::Windows::Forms::GroupBox());
			this->btnBrowse = (gcnew System::Windows::Forms::Button());
			this->txtboxVhdDir = (gcnew System::Windows::Forms::TextBox());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->listView3 = (gcnew System::Windows::Forms::ListView());
			this->groupBox16 = (gcnew System::Windows::Forms::GroupBox());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox15 = (gcnew System::Windows::Forms::GroupBox());
			this->btnCopy = (gcnew System::Windows::Forms::Button());
			this->cbDocuments = (gcnew System::Windows::Forms::CheckBox());
			this->cbDesktop = (gcnew System::Windows::Forms::CheckBox());
			this->cbProfile = (gcnew System::Windows::Forms::CheckBox());
			this->lblTransferRate = (gcnew System::Windows::Forms::Label());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox10 = (gcnew System::Windows::Forms::GroupBox());
			this->cbModifyDate = (gcnew System::Windows::Forms::CheckBox());
			this->cbArchiveBit = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox9 = (gcnew System::Windows::Forms::GroupBox());
			this->cbEncryption = (gcnew System::Windows::Forms::CheckBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->tbEncryptionPass = (gcnew System::Windows::Forms::TextBox());
			this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
			this->cbLogging = (gcnew System::Windows::Forms::CheckBox());
			this->lblLogging = (gcnew System::Windows::Forms::Label());
			this->tbLogPath = (gcnew System::Windows::Forms::TextBox());
			this->cbDefaultLog = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->tbSetName = (gcnew System::Windows::Forms::TextBox());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->dtpTime = (gcnew System::Windows::Forms::DateTimePicker());
			this->cbSaturday = (gcnew System::Windows::Forms::CheckBox());
			this->lblAt = (gcnew System::Windows::Forms::Label());
			this->cbTuesday = (gcnew System::Windows::Forms::CheckBox());
			this->labelEveryday = (gcnew System::Windows::Forms::LinkLabel());
			this->cbFriday = (gcnew System::Windows::Forms::CheckBox());
			this->cbSchedule = (gcnew System::Windows::Forms::CheckBox());
			this->cbThursday = (gcnew System::Windows::Forms::CheckBox());
			this->cbWednesday = (gcnew System::Windows::Forms::CheckBox());
			this->cbSunday = (gcnew System::Windows::Forms::CheckBox());
			this->cbMonday = (gcnew System::Windows::Forms::CheckBox());
			this->btnReset = (gcnew System::Windows::Forms::Button());
			this->btnSave = (gcnew System::Windows::Forms::Button());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->trSelect = (gcnew System::Windows::Forms::TreeView());
			this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->btnEditSavesSet = (gcnew System::Windows::Forms::Button());
			this->btnDeleteSavedSet = (gcnew System::Windows::Forms::Button());
			this->lblNoOfFilesMissed = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->btnRunSavedSetNow = (gcnew System::Windows::Forms::Button());
			this->lblNoOfFilesBackedUp = (gcnew System::Windows::Forms::Label());
			this->lblBackupStartTime = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->lblCurrentFile = (gcnew System::Windows::Forms::Label());
			this->lblCurrentOperation = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox14->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->groupBox13->SuspendLayout();
			this->groupBox12->SuspendLayout();
			this->groupBox11->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox17->SuspendLayout();
			this->groupBox16->SuspendLayout();
			this->tabPage4->SuspendLayout();
			this->groupBox15->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->groupBox10->SuspendLayout();
			this->groupBox9->SuspendLayout();
			this->groupBox8->SuspendLayout();
			this->groupBox7->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox14
			// 
			this->groupBox14->Controls->Add(this->label9);
			this->groupBox14->Controls->Add(this->TextBox8);
			this->groupBox14->Controls->Add(this->CheckBox4);
			this->groupBox14->Controls->Add(this->TextBox7);
			this->groupBox14->Controls->Add(this->label10);
			this->groupBox14->Controls->Add(this->label11);
			this->groupBox14->Controls->Add(this->textBox6);
			this->groupBox14->Controls->Add(this->label12);
			this->groupBox14->Controls->Add(this->textBox9);
			this->groupBox14->Location = System::Drawing::Point(9, 270);
			this->groupBox14->Name = L"groupBox14";
			this->groupBox14->Size = System::Drawing::Size(337, 146);
			this->groupBox14->TabIndex = 41;
			this->groupBox14->TabStop = false;
			this->groupBox14->Text = L"Offline Storage Settings";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(21, 52);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(72, 13);
			this->label9->TabIndex = 15;
			this->label9->Text = L"Server Name:";
			// 
			// TextBox8
			// 
			this->TextBox8->Location = System::Drawing::Point(200, 108);
			this->TextBox8->Name = L"TextBox8";
			this->TextBox8->PasswordChar = '*';
			this->TextBox8->Size = System::Drawing::Size(110, 20);
			this->TextBox8->TabIndex = 22;
			// 
			// CheckBox4
			// 
			this->CheckBox4->AutoSize = true;
			this->CheckBox4->Location = System::Drawing::Point(24, 19);
			this->CheckBox4->Name = L"CheckBox4";
			this->CheckBox4->Size = System::Drawing::Size(132, 17);
			this->CheckBox4->TabIndex = 14;
			this->CheckBox4->Text = L"Enable Offline Storage";
			this->CheckBox4->UseVisualStyleBackColor = true;
			// 
			// TextBox7
			// 
			this->TextBox7->Location = System::Drawing::Point(24, 108);
			this->TextBox7->Name = L"TextBox7";
			this->TextBox7->Size = System::Drawing::Size(170, 20);
			this->TextBox7->TabIndex = 21;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(255, 52);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(29, 13);
			this->label10->TabIndex = 16;
			this->label10->Text = L"Port:";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(197, 92);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(56, 13);
			this->label11->TabIndex = 20;
			this->label11->Text = L"Password:";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(24, 68);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(225, 20);
			this->textBox6->TabIndex = 17;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(21, 92);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(58, 13);
			this->label12->TabIndex = 19;
			this->label12->Text = L"Username:";
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(258, 68);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(52, 20);
			this->textBox9->TabIndex = 18;
			// 
			// lvBackupSet
			// 
			this->lvBackupSet->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {
				this->columnName, this->clumnType,
					this->columnDestination, this->columnWhenRun, this->columnLastRun
			});
			this->lvBackupSet->FullRowSelect = true;
			this->lvBackupSet->Location = System::Drawing::Point(6, 19);
			this->lvBackupSet->Name = L"lvBackupSet";
			this->lvBackupSet->Size = System::Drawing::Size(758, 154);
			this->lvBackupSet->TabIndex = 0;
			this->lvBackupSet->UseCompatibleStateImageBehavior = false;
			this->lvBackupSet->View = System::Windows::Forms::View::Details;
			this->lvBackupSet->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::lvBackupSet_SelectedIndexChanged);
			// 
			// columnName
			// 
			this->columnName->Text = L"Backup name";
			this->columnName->Width = 99;
			// 
			// clumnType
			// 
			this->clumnType->Text = L"Backup type";
			this->clumnType->Width = 83;
			// 
			// columnDestination
			// 
			this->columnDestination->Text = L"Destination";
			this->columnDestination->Width = 90;
			// 
			// columnWhenRun
			// 
			this->columnWhenRun->Text = L"When to Run";
			this->columnWhenRun->Width = 91;
			// 
			// columnLastRun
			// 
			this->columnLastRun->Text = L"Last Run";
			this->columnLastRun->Width = 92;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->groupBox14);
			this->tabPage3->Controls->Add(this->groupBox13);
			this->tabPage3->Controls->Add(this->groupBox12);
			this->tabPage3->Controls->Add(this->groupBox11);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(782, 453);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Global Options";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// groupBox13
			// 
			this->groupBox13->Controls->Add(this->CheckBox3);
			this->groupBox13->Controls->Add(this->label7);
			this->groupBox13->Controls->Add(this->textBox3);
			this->groupBox13->Controls->Add(this->label8);
			this->groupBox13->Controls->Add(this->textBox5);
			this->groupBox13->Location = System::Drawing::Point(9, 90);
			this->groupBox13->Name = L"groupBox13";
			this->groupBox13->Size = System::Drawing::Size(337, 174);
			this->groupBox13->TabIndex = 40;
			this->groupBox13->TabStop = false;
			this->groupBox13->Text = L"File Exclude Setting";
			// 
			// CheckBox3
			// 
			this->CheckBox3->AutoSize = true;
			this->CheckBox3->Location = System::Drawing::Point(24, 36);
			this->CheckBox3->Name = L"CheckBox3";
			this->CheckBox3->Size = System::Drawing::Size(132, 17);
			this->CheckBox3->TabIndex = 13;
			this->CheckBox3->Text = L"Enable File Exclutions:";
			this->CheckBox3->UseVisualStyleBackColor = true;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(21, 70);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(238, 13);
			this->label7->TabIndex = 2;
			this->label7->Text = L"Do not backup files wth these extenstions (*.sys):";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(24, 86);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(293, 20);
			this->textBox3->TabIndex = 3;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(21, 109);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(232, 13);
			this->label8->TabIndex = 8;
			this->label8->Text = L"Do not backup folders with these names (temp):";
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(24, 125);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(293, 20);
			this->textBox5->TabIndex = 9;
			// 
			// groupBox12
			// 
			this->groupBox12->Controls->Add(this->ComboBox2);
			this->groupBox12->Location = System::Drawing::Point(352, 6);
			this->groupBox12->Name = L"groupBox12";
			this->groupBox12->Size = System::Drawing::Size(331, 121);
			this->groupBox12->TabIndex = 39;
			this->groupBox12->TabStop = false;
			this->groupBox12->Text = L"Drive tattoo";
			// 
			// ComboBox2
			// 
			this->ComboBox2->FormattingEnabled = true;
			this->ComboBox2->Location = System::Drawing::Point(140, 72);
			this->ComboBox2->Name = L"ComboBox2";
			this->ComboBox2->Size = System::Drawing::Size(170, 21);
			this->ComboBox2->TabIndex = 0;
			// 
			// groupBox11
			// 
			this->groupBox11->Controls->Add(this->CheckBox1);
			this->groupBox11->Controls->Add(this->TextBox2);
			this->groupBox11->Location = System::Drawing::Point(9, 6);
			this->groupBox11->Name = L"groupBox11";
			this->groupBox11->Size = System::Drawing::Size(337, 78);
			this->groupBox11->TabIndex = 36;
			this->groupBox11->TabStop = false;
			this->groupBox11->Text = L"Email Reports";
			// 
			// CheckBox1
			// 
			this->CheckBox1->AutoSize = true;
			this->CheckBox1->Location = System::Drawing::Point(21, 19);
			this->CheckBox1->Name = L"CheckBox1";
			this->CheckBox1->Size = System::Drawing::Size(127, 17);
			this->CheckBox1->TabIndex = 5;
			this->CheckBox1->Text = L"Enable Email Reports";
			this->CheckBox1->UseVisualStyleBackColor = true;
			// 
			// TextBox2
			// 
			this->TextBox2->Location = System::Drawing::Point(21, 42);
			this->TextBox2->Name = L"TextBox2";
			this->TextBox2->Size = System::Drawing::Size(152, 20);
			this->TextBox2->TabIndex = 6;
			this->TextBox2->Text = L"Email Address";
			// 
			// rbFlatFile
			// 
			this->rbFlatFile->AutoSize = true;
			this->rbFlatFile->Checked = true;
			this->rbFlatFile->Location = System::Drawing::Point(11, 19);
			this->rbFlatFile->Name = L"rbFlatFile";
			this->rbFlatFile->Size = System::Drawing::Size(101, 17);
			this->rbFlatFile->TabIndex = 0;
			this->rbFlatFile->TabStop = true;
			this->rbFlatFile->Text = L"Flat File Backup";
			this->rbFlatFile->UseVisualStyleBackColor = true;
			this->rbFlatFile->CheckedChanged += gcnew System::EventHandler(this, &MainForm::Backup_Type_CheckedChanged);
			// 
			// rbVHD
			// 
			this->rbVHD->AutoSize = true;
			this->rbVHD->Location = System::Drawing::Point(276, 19);
			this->rbVHD->Name = L"rbVHD";
			this->rbVHD->Size = System::Drawing::Size(105, 17);
			this->rbVHD->TabIndex = 1;
			this->rbVHD->Text = L"Virual Convertion";
			this->rbVHD->UseVisualStyleBackColor = true;
			this->rbVHD->CheckedChanged += gcnew System::EventHandler(this, &MainForm::Backup_Type_CheckedChanged);
			// 
			// tbDes
			// 
			this->tbDes->Location = System::Drawing::Point(6, 40);
			this->tbDes->Name = L"tbDes";
			this->tbDes->Size = System::Drawing::Size(312, 20);
			this->tbDes->TabIndex = 36;
			this->tbDes->TextChanged += gcnew System::EventHandler(this, &MainForm::tbDes_TextChanged);
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->tbDes);
			this->groupBox4->Controls->Add(this->btnBrowseDes);
			this->groupBox4->Controls->Add(this->lblDes);
			this->groupBox4->Location = System::Drawing::Point(239, 376);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(331, 74);
			this->groupBox4->TabIndex = 1;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Backup Storage Location:";
			// 
			// btnBrowseDes
			// 
			this->btnBrowseDes->Location = System::Drawing::Point(198, 11);
			this->btnBrowseDes->Name = L"btnBrowseDes";
			this->btnBrowseDes->Size = System::Drawing::Size(63, 23);
			this->btnBrowseDes->TabIndex = 37;
			this->btnBrowseDes->Text = L"Browse...";
			this->btnBrowseDes->UseVisualStyleBackColor = true;
			this->btnBrowseDes->Click += gcnew System::EventHandler(this, &MainForm::btnBrowseDes_Click);
			// 
			// lblDes
			// 
			this->lblDes->AutoSize = true;
			this->lblDes->Location = System::Drawing::Point(20, 16);
			this->lblDes->Name = L"lblDes";
			this->lblDes->Size = System::Drawing::Size(135, 13);
			this->lblDes->TabIndex = 34;
			this->lblDes->Text = L"Select Location of backup:";
			// 
			// cbFavorite
			// 
			this->cbFavorite->AutoSize = true;
			this->cbFavorite->Location = System::Drawing::Point(15, 366);
			this->cbFavorite->Name = L"cbFavorite";
			this->cbFavorite->Size = System::Drawing::Size(86, 17);
			this->cbFavorite->TabIndex = 51;
			this->cbFavorite->Text = L"My Favorites";
			this->cbFavorite->UseVisualStyleBackColor = true;
			// 
			// rbOnetoOne
			// 
			this->rbOnetoOne->AutoSize = true;
			this->rbOnetoOne->Location = System::Drawing::Point(151, 19);
			this->rbOnetoOne->Name = L"rbOnetoOne";
			this->rbOnetoOne->Size = System::Drawing::Size(80, 17);
			this->rbOnetoOne->TabIndex = 2;
			this->rbOnetoOne->Text = L"One to One";
			this->rbOnetoOne->UseVisualStyleBackColor = true;
			this->rbOnetoOne->CheckedChanged += gcnew System::EventHandler(this, &MainForm::Backup_Type_CheckedChanged);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->rbOnetoOne);
			this->groupBox3->Controls->Add(this->rbVHD);
			this->groupBox3->Controls->Add(this->rbFlatFile);
			this->groupBox3->Location = System::Drawing::Point(389, 6);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(387, 46);
			this->groupBox3->TabIndex = 0;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Backup Type:";
			// 
			// progressBar
			// 
			this->progressBar->Location = System::Drawing::Point(17, 19);
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(604, 36);
			this->progressBar->TabIndex = 5;
			this->progressBar->Visible = false;
			// 
			// btnSBrowse
			// 
			this->btnSBrowse->Location = System::Drawing::Point(357, 30);
			this->btnSBrowse->Name = L"btnSBrowse";
			this->btnSBrowse->Size = System::Drawing::Size(75, 23);
			this->btnSBrowse->TabIndex = 3;
			this->btnSBrowse->Text = L"Browse";
			this->btnSBrowse->UseVisualStyleBackColor = true;
			// 
			// copyLocation
			// 
			this->copyLocation->Location = System::Drawing::Point(97, 32);
			this->copyLocation->Name = L"copyLocation";
			this->copyLocation->Size = System::Drawing::Size(254, 20);
			this->copyLocation->TabIndex = 2;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(97, 16);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(161, 13);
			this->label13->TabIndex = 1;
			this->label13->Text = L"Enter the location to restore files:";
			// 
			// columnHeader3
			// 
			this->columnHeader3->Tag = L"2";
			this->columnHeader3->Text = L"Type";
			this->columnHeader3->Width = 102;
			// 
			// columnHeader2
			// 
			this->columnHeader2->Tag = L"3";
			this->columnHeader2->Text = L"Date Modified";
			this->columnHeader2->Width = 114;
			// 
			// columnHeader4
			// 
			this->columnHeader4->Tag = L"2";
			this->columnHeader4->Text = L"Size";
			this->columnHeader4->Width = 69;
			// 
			// treeView1
			// 
			this->treeView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->treeView1->Location = System::Drawing::Point(6, 19);
			this->treeView1->Name = L"treeView1";
			this->treeView1->Size = System::Drawing::Size(213, 276);
			this->treeView1->TabIndex = 0;
			// 
			// btnClose
			// 
			this->btnClose->Location = System::Drawing::Point(686, 19);
			this->btnClose->Name = L"btnClose";
			this->btnClose->Size = System::Drawing::Size(75, 23);
			this->btnClose->TabIndex = 3;
			this->btnClose->Text = L"Close";
			this->btnClose->UseVisualStyleBackColor = true;
			// 
			// btnOpen
			// 
			this->btnOpen->Location = System::Drawing::Point(605, 19);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(75, 23);
			this->btnOpen->TabIndex = 2;
			this->btnOpen->Text = L"Open";
			this->btnOpen->UseVisualStyleBackColor = true;
			// 
			// groupBox17
			// 
			this->groupBox17->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox17->Controls->Add(this->btnClose);
			this->groupBox17->Controls->Add(this->btnOpen);
			this->groupBox17->Controls->Add(this->btnBrowse);
			this->groupBox17->Controls->Add(this->txtboxVhdDir);
			this->groupBox17->Location = System::Drawing::Point(9, 6);
			this->groupBox17->Name = L"groupBox17";
			this->groupBox17->Size = System::Drawing::Size(767, 59);
			this->groupBox17->TabIndex = 6;
			this->groupBox17->TabStop = false;
			this->groupBox17->Text = L"Enter or Browse to the VHD you want to open:";
			// 
			// btnBrowse
			// 
			this->btnBrowse->Location = System::Drawing::Point(524, 19);
			this->btnBrowse->Name = L"btnBrowse";
			this->btnBrowse->Size = System::Drawing::Size(75, 23);
			this->btnBrowse->TabIndex = 1;
			this->btnBrowse->Text = L"Browse...";
			this->btnBrowse->UseVisualStyleBackColor = true;
			// 
			// txtboxVhdDir
			// 
			this->txtboxVhdDir->Location = System::Drawing::Point(17, 19);
			this->txtboxVhdDir->Name = L"txtboxVhdDir";
			this->txtboxVhdDir->Size = System::Drawing::Size(501, 20);
			this->txtboxVhdDir->TabIndex = 0;
			// 
			// columnHeader1
			// 
			this->columnHeader1->Tag = L"5";
			this->columnHeader1->Text = L"Name";
			this->columnHeader1->Width = 245;
			// 
			// listView3
			// 
			this->listView3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->listView3->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {
				this->columnHeader1, this->columnHeader2,
					this->columnHeader3, this->columnHeader4
			});
			this->listView3->FullRowSelect = true;
			this->listView3->Location = System::Drawing::Point(225, 19);
			this->listView3->Name = L"listView3";
			this->listView3->Size = System::Drawing::Size(536, 276);
			this->listView3->TabIndex = 1;
			this->listView3->UseCompatibleStateImageBehavior = false;
			this->listView3->View = System::Windows::Forms::View::Details;
			// 
			// groupBox16
			// 
			this->groupBox16->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox16->Controls->Add(this->listView3);
			this->groupBox16->Controls->Add(this->treeView1);
			this->groupBox16->Location = System::Drawing::Point(9, 71);
			this->groupBox16->Name = L"groupBox16";
			this->groupBox16->Size = System::Drawing::Size(767, 303);
			this->groupBox16->TabIndex = 7;
			this->groupBox16->TabStop = false;
			this->groupBox16->Text = L"Explore the VHD file:";
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->groupBox15);
			this->tabPage4->Controls->Add(this->groupBox16);
			this->tabPage4->Controls->Add(this->groupBox17);
			this->tabPage4->Location = System::Drawing::Point(4, 22);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(782, 453);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"Restore";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// groupBox15
			// 
			this->groupBox15->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox15->Controls->Add(this->progressBar);
			this->groupBox15->Controls->Add(this->btnSBrowse);
			this->groupBox15->Controls->Add(this->copyLocation);
			this->groupBox15->Controls->Add(this->label13);
			this->groupBox15->Controls->Add(this->btnCopy);
			this->groupBox15->Location = System::Drawing::Point(9, 380);
			this->groupBox15->Name = L"groupBox15";
			this->groupBox15->Size = System::Drawing::Size(767, 70);
			this->groupBox15->TabIndex = 8;
			this->groupBox15->TabStop = false;
			this->groupBox15->Text = L"Copy Options:";
			// 
			// btnCopy
			// 
			this->btnCopy->Location = System::Drawing::Point(627, 19);
			this->btnCopy->Name = L"btnCopy";
			this->btnCopy->Size = System::Drawing::Size(134, 30);
			this->btnCopy->TabIndex = 0;
			this->btnCopy->Text = L"Copy Selected Files";
			this->btnCopy->UseVisualStyleBackColor = true;
			// 
			// cbDocuments
			// 
			this->cbDocuments->AutoSize = true;
			this->cbDocuments->Location = System::Drawing::Point(15, 343);
			this->cbDocuments->Name = L"cbDocuments";
			this->cbDocuments->Size = System::Drawing::Size(97, 17);
			this->cbDocuments->TabIndex = 50;
			this->cbDocuments->Text = L"My Documents";
			this->cbDocuments->UseVisualStyleBackColor = true;
			// 
			// cbDesktop
			// 
			this->cbDesktop->AutoSize = true;
			this->cbDesktop->Location = System::Drawing::Point(121, 343);
			this->cbDesktop->Name = L"cbDesktop";
			this->cbDesktop->Size = System::Drawing::Size(83, 17);
			this->cbDesktop->TabIndex = 52;
			this->cbDesktop->Text = L"My Desktop";
			this->cbDesktop->UseVisualStyleBackColor = true;
			// 
			// cbProfile
			// 
			this->cbProfile->AutoSize = true;
			this->cbProfile->Location = System::Drawing::Point(121, 366);
			this->cbProfile->Name = L"cbProfile";
			this->cbProfile->Size = System::Drawing::Size(85, 17);
			this->cbProfile->TabIndex = 53;
			this->cbProfile->Text = L"Entire Profile";
			this->cbProfile->UseVisualStyleBackColor = true;
			// 
			// lblTransferRate
			// 
			this->lblTransferRate->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->lblTransferRate->Location = System::Drawing::Point(451, 196);
			this->lblTransferRate->Name = L"lblTransferRate";
			this->lblTransferRate->Size = System::Drawing::Size(181, 22);
			this->lblTransferRate->TabIndex = 11;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->groupBox10);
			this->tabPage2->Controls->Add(this->groupBox9);
			this->tabPage2->Controls->Add(this->groupBox8);
			this->tabPage2->Controls->Add(this->groupBox7);
			this->tabPage2->Controls->Add(this->groupBox6);
			this->tabPage2->Controls->Add(this->btnReset);
			this->tabPage2->Controls->Add(this->btnSave);
			this->tabPage2->Controls->Add(this->groupBox5);
			this->tabPage2->Controls->Add(this->groupBox4);
			this->tabPage2->Controls->Add(this->groupBox3);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(782, 453);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"New Backup Set";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// groupBox10
			// 
			this->groupBox10->Controls->Add(this->cbModifyDate);
			this->groupBox10->Controls->Add(this->cbArchiveBit);
			this->groupBox10->Location = System::Drawing::Point(239, 288);
			this->groupBox10->Name = L"groupBox10";
			this->groupBox10->Size = System::Drawing::Size(200, 74);
			this->groupBox10->TabIndex = 61;
			this->groupBox10->TabStop = false;
			this->groupBox10->Text = L"Backup By:";
			// 
			// cbModifyDate
			// 
			this->cbModifyDate->AutoSize = true;
			this->cbModifyDate->Checked = true;
			this->cbModifyDate->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbModifyDate->Location = System::Drawing::Point(13, 19);
			this->cbModifyDate->Name = L"cbModifyDate";
			this->cbModifyDate->Size = System::Drawing::Size(102, 17);
			this->cbModifyDate->TabIndex = 1;
			this->cbModifyDate->Text = L"File Modify Date";
			this->cbModifyDate->UseVisualStyleBackColor = true;
			this->cbModifyDate->CheckedChanged += gcnew System::EventHandler(this, &MainForm::cbModifyDate_CheckedChanged);
			// 
			// cbArchiveBit
			// 
			this->cbArchiveBit->AutoSize = true;
			this->cbArchiveBit->Location = System::Drawing::Point(13, 42);
			this->cbArchiveBit->Name = L"cbArchiveBit";
			this->cbArchiveBit->Size = System::Drawing::Size(77, 17);
			this->cbArchiveBit->TabIndex = 0;
			this->cbArchiveBit->Text = L"Archive Bit";
			this->cbArchiveBit->UseVisualStyleBackColor = true;
			this->cbArchiveBit->CheckedChanged += gcnew System::EventHandler(this, &MainForm::cbArchiveBit_CheckedChanged);
			// 
			// groupBox9
			// 
			this->groupBox9->Controls->Add(this->cbEncryption);
			this->groupBox9->Controls->Add(this->label6);
			this->groupBox9->Controls->Add(this->tbEncryptionPass);
			this->groupBox9->Location = System::Drawing::Point(443, 58);
			this->groupBox9->Name = L"groupBox9";
			this->groupBox9->Size = System::Drawing::Size(333, 105);
			this->groupBox9->TabIndex = 60;
			this->groupBox9->TabStop = false;
			this->groupBox9->Text = L"Encrption Settings";
			// 
			// cbEncryption
			// 
			this->cbEncryption->AutoSize = true;
			this->cbEncryption->Location = System::Drawing::Point(18, 19);
			this->cbEncryption->Name = L"cbEncryption";
			this->cbEncryption->Size = System::Drawing::Size(125, 17);
			this->cbEncryption->TabIndex = 11;
			this->cbEncryption->Text = L"Enable File Encrytion";
			this->cbEncryption->UseVisualStyleBackColor = true;
			this->cbEncryption->CheckedChanged += gcnew System::EventHandler(this, &MainForm::cbEncryption_CheckedChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(15, 39);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(100, 13);
			this->label6->TabIndex = 10;
			this->label6->Text = L"Encytion Password:";
			// 
			// tbEncryptionPass
			// 
			this->tbEncryptionPass->Location = System::Drawing::Point(18, 57);
			this->tbEncryptionPass->Name = L"tbEncryptionPass";
			this->tbEncryptionPass->PasswordChar = '*';
			this->tbEncryptionPass->Size = System::Drawing::Size(196, 20);
			this->tbEncryptionPass->TabIndex = 12;
			// 
			// groupBox8
			// 
			this->groupBox8->Controls->Add(this->cbLogging);
			this->groupBox8->Controls->Add(this->lblLogging);
			this->groupBox8->Controls->Add(this->tbLogPath);
			this->groupBox8->Controls->Add(this->cbDefaultLog);
			this->groupBox8->Location = System::Drawing::Point(443, 165);
			this->groupBox8->Name = L"groupBox8";
			this->groupBox8->Size = System::Drawing::Size(333, 105);
			this->groupBox8->TabIndex = 59;
			this->groupBox8->TabStop = false;
			this->groupBox8->Text = L"Logging";
			// 
			// cbLogging
			// 
			this->cbLogging->AutoSize = true;
			this->cbLogging->Checked = true;
			this->cbLogging->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbLogging->Location = System::Drawing::Point(13, 18);
			this->cbLogging->Name = L"cbLogging";
			this->cbLogging->Size = System::Drawing::Size(100, 17);
			this->cbLogging->TabIndex = 12;
			this->cbLogging->Text = L"Enable Logging";
			this->cbLogging->UseVisualStyleBackColor = true;
			this->cbLogging->CheckedChanged += gcnew System::EventHandler(this, &MainForm::cbLogging_CheckedChanged);
			// 
			// lblLogging
			// 
			this->lblLogging->AutoSize = true;
			this->lblLogging->Location = System::Drawing::Point(52, 60);
			this->lblLogging->Name = L"lblLogging";
			this->lblLogging->Size = System::Drawing::Size(73, 13);
			this->lblLogging->TabIndex = 11;
			this->lblLogging->Text = L"Logging Path:";
			this->lblLogging->Visible = false;
			// 
			// tbLogPath
			// 
			this->tbLogPath->Location = System::Drawing::Point(13, 76);
			this->tbLogPath->Name = L"tbLogPath";
			this->tbLogPath->Size = System::Drawing::Size(164, 20);
			this->tbLogPath->TabIndex = 13;
			this->tbLogPath->Visible = false;
			// 
			// cbDefaultLog
			// 
			this->cbDefaultLog->AutoSize = true;
			this->cbDefaultLog->Checked = true;
			this->cbDefaultLog->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbDefaultLog->Location = System::Drawing::Point(13, 38);
			this->cbDefaultLog->Name = L"cbDefaultLog";
			this->cbDefaultLog->Size = System::Drawing::Size(126, 17);
			this->cbDefaultLog->TabIndex = 40;
			this->cbDefaultLog->Text = L"Default Logging Path";
			this->cbDefaultLog->UseVisualStyleBackColor = true;
			this->cbDefaultLog->CheckedChanged += gcnew System::EventHandler(this, &MainForm::cbDefaultLog_CheckedChanged);
			// 
			// groupBox7
			// 
			this->groupBox7->Controls->Add(this->tbSetName);
			this->groupBox7->Location = System::Drawing::Point(6, 6);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(377, 46);
			this->groupBox7->TabIndex = 54;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = L"Backup Set Name:";
			// 
			// tbSetName
			// 
			this->tbSetName->Location = System::Drawing::Point(6, 16);
			this->tbSetName->Name = L"tbSetName";
			this->tbSetName->Size = System::Drawing::Size(365, 20);
			this->tbSetName->TabIndex = 0;
			this->tbSetName->TextChanged += gcnew System::EventHandler(this, &MainForm::tbSetName_TextChanged);
			// 
			// groupBox6
			// 
			this->groupBox6->BackColor = System::Drawing::Color::Transparent;
			this->groupBox6->Controls->Add(this->dtpTime);
			this->groupBox6->Controls->Add(this->cbSaturday);
			this->groupBox6->Controls->Add(this->lblAt);
			this->groupBox6->Controls->Add(this->cbTuesday);
			this->groupBox6->Controls->Add(this->labelEveryday);
			this->groupBox6->Controls->Add(this->cbFriday);
			this->groupBox6->Controls->Add(this->cbSchedule);
			this->groupBox6->Controls->Add(this->cbThursday);
			this->groupBox6->Controls->Add(this->cbWednesday);
			this->groupBox6->Controls->Add(this->cbSunday);
			this->groupBox6->Controls->Add(this->cbMonday);
			this->groupBox6->Location = System::Drawing::Point(239, 58);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(198, 224);
			this->groupBox6->TabIndex = 51;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Set the Schedule";
			// 
			// dtpTime
			// 
			this->dtpTime->CustomFormat = L"hh:mm tt";
			this->dtpTime->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->dtpTime->Location = System::Drawing::Point(95, 107);
			this->dtpTime->Name = L"dtpTime";
			this->dtpTime->ShowUpDown = true;
			this->dtpTime->Size = System::Drawing::Size(86, 20);
			this->dtpTime->TabIndex = 31;
			this->dtpTime->Value = System::DateTime(2014, 7, 31, 0, 0, 0, 0);
			this->dtpTime->ValueChanged += gcnew System::EventHandler(this, &MainForm::dtpTime_ValueChanged);
			// 
			// cbSaturday
			// 
			this->cbSaturday->AutoSize = true;
			this->cbSaturday->Enabled = false;
			this->cbSaturday->Location = System::Drawing::Point(6, 163);
			this->cbSaturday->Name = L"cbSaturday";
			this->cbSaturday->Size = System::Drawing::Size(68, 17);
			this->cbSaturday->TabIndex = 20;
			this->cbSaturday->Tag = L"6";
			this->cbSaturday->Text = L"Saturday";
			this->cbSaturday->UseVisualStyleBackColor = true;
			this->cbSaturday->CheckedChanged += gcnew System::EventHandler(this, &MainForm::cbDayChange);
			// 
			// lblAt
			// 
			this->lblAt->AutoSize = true;
			this->lblAt->Location = System::Drawing::Point(91, 88);
			this->lblAt->Name = L"lblAt";
			this->lblAt->Size = System::Drawing::Size(18, 13);
			this->lblAt->TabIndex = 32;
			this->lblAt->Text = L"@";
			// 
			// cbTuesday
			// 
			this->cbTuesday->AutoSize = true;
			this->cbTuesday->Enabled = false;
			this->cbTuesday->Location = System::Drawing::Point(6, 88);
			this->cbTuesday->Name = L"cbTuesday";
			this->cbTuesday->Size = System::Drawing::Size(67, 17);
			this->cbTuesday->TabIndex = 16;
			this->cbTuesday->Tag = L"2";
			this->cbTuesday->Text = L"Tuesday";
			this->cbTuesday->UseVisualStyleBackColor = true;
			this->cbTuesday->CheckedChanged += gcnew System::EventHandler(this, &MainForm::cbDayChange);
			// 
			// labelEveryday
			// 
			this->labelEveryday->AutoSize = true;
			this->labelEveryday->Enabled = false;
			this->labelEveryday->Location = System::Drawing::Point(6, 194);
			this->labelEveryday->Name = L"labelEveryday";
			this->labelEveryday->Size = System::Drawing::Size(54, 13);
			this->labelEveryday->TabIndex = 33;
			this->labelEveryday->TabStop = true;
			this->labelEveryday->Text = L"Every day";
			this->labelEveryday->Click += gcnew System::EventHandler(this, &MainForm::labelEveryday_Click);
			// 
			// cbFriday
			// 
			this->cbFriday->AutoSize = true;
			this->cbFriday->Enabled = false;
			this->cbFriday->Location = System::Drawing::Point(6, 144);
			this->cbFriday->Name = L"cbFriday";
			this->cbFriday->Size = System::Drawing::Size(54, 17);
			this->cbFriday->TabIndex = 19;
			this->cbFriday->Tag = L"5";
			this->cbFriday->Text = L"Friday";
			this->cbFriday->UseVisualStyleBackColor = true;
			this->cbFriday->CheckedChanged += gcnew System::EventHandler(this, &MainForm::cbDayChange);
			// 
			// cbSchedule
			// 
			this->cbSchedule->AutoSize = true;
			this->cbSchedule->Location = System::Drawing::Point(5, 19);
			this->cbSchedule->Name = L"cbSchedule";
			this->cbSchedule->Size = System::Drawing::Size(133, 17);
			this->cbSchedule->TabIndex = 44;
			this->cbSchedule->Text = L"Enable Daily Schedule";
			this->cbSchedule->UseVisualStyleBackColor = true;
			this->cbSchedule->CheckedChanged += gcnew System::EventHandler(this, &MainForm::cbSchedule_CheckedChanged);
			this->cbSchedule->Click += gcnew System::EventHandler(this, &MainForm::cbSchedule_Click);
			// 
			// cbThursday
			// 
			this->cbThursday->AutoSize = true;
			this->cbThursday->Enabled = false;
			this->cbThursday->Location = System::Drawing::Point(6, 126);
			this->cbThursday->Name = L"cbThursday";
			this->cbThursday->Size = System::Drawing::Size(70, 17);
			this->cbThursday->TabIndex = 18;
			this->cbThursday->Tag = L"4";
			this->cbThursday->Text = L"Thursday";
			this->cbThursday->UseVisualStyleBackColor = true;
			this->cbThursday->CheckedChanged += gcnew System::EventHandler(this, &MainForm::cbDayChange);
			// 
			// cbWednesday
			// 
			this->cbWednesday->AutoSize = true;
			this->cbWednesday->Enabled = false;
			this->cbWednesday->Location = System::Drawing::Point(6, 106);
			this->cbWednesday->Name = L"cbWednesday";
			this->cbWednesday->Size = System::Drawing::Size(83, 17);
			this->cbWednesday->TabIndex = 17;
			this->cbWednesday->Tag = L"3";
			this->cbWednesday->Text = L"Wednesday";
			this->cbWednesday->UseVisualStyleBackColor = true;
			this->cbWednesday->CheckedChanged += gcnew System::EventHandler(this, &MainForm::cbDayChange);
			// 
			// cbSunday
			// 
			this->cbSunday->AutoSize = true;
			this->cbSunday->Enabled = false;
			this->cbSunday->Location = System::Drawing::Point(6, 49);
			this->cbSunday->Name = L"cbSunday";
			this->cbSunday->Size = System::Drawing::Size(62, 17);
			this->cbSunday->TabIndex = 15;
			this->cbSunday->Tag = L"0";
			this->cbSunday->Text = L"Sunday";
			this->cbSunday->UseVisualStyleBackColor = true;
			this->cbSunday->CheckStateChanged += gcnew System::EventHandler(this, &MainForm::cbDayChange);
			// 
			// cbMonday
			// 
			this->cbMonday->AutoSize = true;
			this->cbMonday->Enabled = false;
			this->cbMonday->Location = System::Drawing::Point(6, 68);
			this->cbMonday->Name = L"cbMonday";
			this->cbMonday->Size = System::Drawing::Size(64, 17);
			this->cbMonday->TabIndex = 14;
			this->cbMonday->Tag = L"1";
			this->cbMonday->Text = L"Monday";
			this->cbMonday->UseVisualStyleBackColor = true;
			this->cbMonday->CheckedChanged += gcnew System::EventHandler(this, &MainForm::cbDayChange);
			// 
			// btnReset
			// 
			this->btnReset->Location = System::Drawing::Point(616, 424);
			this->btnReset->Name = L"btnReset";
			this->btnReset->Size = System::Drawing::Size(75, 23);
			this->btnReset->TabIndex = 5;
			this->btnReset->Text = L"Reset";
			this->btnReset->UseVisualStyleBackColor = true;
			this->btnReset->Click += gcnew System::EventHandler(this, &MainForm::btnReset_Click);
			// 
			// btnSave
			// 
			this->btnSave->Location = System::Drawing::Point(697, 424);
			this->btnSave->Name = L"btnSave";
			this->btnSave->Size = System::Drawing::Size(75, 23);
			this->btnSave->TabIndex = 4;
			this->btnSave->Text = L"Save";
			this->btnSave->UseVisualStyleBackColor = true;
			this->btnSave->Click += gcnew System::EventHandler(this, &MainForm::btnSave_Click);
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->trSelect);
			this->groupBox5->Controls->Add(this->cbFavorite);
			this->groupBox5->Controls->Add(this->cbDocuments);
			this->groupBox5->Controls->Add(this->cbDesktop);
			this->groupBox5->Controls->Add(this->cbProfile);
			this->groupBox5->Controls->Add(this->label5);
			this->groupBox5->Location = System::Drawing::Point(6, 58);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(227, 392);
			this->groupBox5->TabIndex = 3;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"File Selecttions:";
			// 
			// trSelect
			// 
			this->trSelect->CheckBoxes = true;
			this->trSelect->ImageIndex = 0;
			this->trSelect->ImageList = this->imageList1;
			this->trSelect->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->trSelect->Location = System::Drawing::Point(6, 19);
			this->trSelect->Name = L"trSelect";
			this->trSelect->SelectedImageIndex = 1;
			this->trSelect->Size = System::Drawing::Size(215, 285);
			this->trSelect->TabIndex = 54;
			this->trSelect->AfterCheck += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::trSelect_AfterCheck);
			this->trSelect->BeforeExpand += gcnew System::Windows::Forms::TreeViewCancelEventHandler(this, &MainForm::trSelect_BeforeExpand);
			// 
			// imageList1
			// 
			this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList1.ImageStream")));
			this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList1->Images->SetKeyName(0, L"folder_closed.BMP");
			this->imageList1->Images->SetKeyName(1, L"folder_open.BMP");
			this->imageList1->Images->SetKeyName(2, L"White.bmp");
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(56, 318);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(67, 13);
			this->label5->TabIndex = 49;
			this->label5->Text = L"Quick Picks:";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(451, 159);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(75, 13);
			this->label20->TabIndex = 10;
			this->label20->Text = L"Transfer Rate:";
			// 
			// btnEditSavesSet
			// 
			this->btnEditSavesSet->Enabled = false;
			this->btnEditSavesSet->Location = System::Drawing::Point(6, 179);
			this->btnEditSavesSet->Name = L"btnEditSavesSet";
			this->btnEditSavesSet->Size = System::Drawing::Size(108, 23);
			this->btnEditSavesSet->TabIndex = 1;
			this->btnEditSavesSet->Text = L"Edit Saved Set";
			this->btnEditSavesSet->UseVisualStyleBackColor = true;
			this->btnEditSavesSet->Click += gcnew System::EventHandler(this, &MainForm::btnEditSavesSet_Click);
			// 
			// btnDeleteSavedSet
			// 
			this->btnDeleteSavedSet->Enabled = false;
			this->btnDeleteSavedSet->Location = System::Drawing::Point(638, 179);
			this->btnDeleteSavedSet->Name = L"btnDeleteSavedSet";
			this->btnDeleteSavedSet->Size = System::Drawing::Size(126, 23);
			this->btnDeleteSavedSet->TabIndex = 2;
			this->btnDeleteSavedSet->Text = L"Delete Saved Set";
			this->btnDeleteSavedSet->UseVisualStyleBackColor = true;
			this->btnDeleteSavedSet->Click += gcnew System::EventHandler(this, &MainForm::btnDeleteSavedSet_Click);
			// 
			// lblNoOfFilesMissed
			// 
			this->lblNoOfFilesMissed->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->lblNoOfFilesMissed->Location = System::Drawing::Point(451, 114);
			this->lblNoOfFilesMissed->Name = L"lblNoOfFilesMissed";
			this->lblNoOfFilesMissed->Size = System::Drawing::Size(181, 22);
			this->lblNoOfFilesMissed->TabIndex = 9;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(451, 88);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(119, 13);
			this->label18->TabIndex = 8;
			this->label18->Text = L"Number of Missed Files:";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(243, 88);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(135, 13);
			this->label17->TabIndex = 7;
			this->label17->Text = L"Number of Files Backedup:";
			// 
			// btnRunSavedSetNow
			// 
			this->btnRunSavedSetNow->Enabled = false;
			this->btnRunSavedSetNow->Location = System::Drawing::Point(310, 179);
			this->btnRunSavedSetNow->Name = L"btnRunSavedSetNow";
			this->btnRunSavedSetNow->Size = System::Drawing::Size(137, 23);
			this->btnRunSavedSetNow->TabIndex = 3;
			this->btnRunSavedSetNow->Text = L"Run Saved Set Now!";
			this->btnRunSavedSetNow->UseVisualStyleBackColor = true;
			this->btnRunSavedSetNow->Click += gcnew System::EventHandler(this, &MainForm::btnRunSavedSetNow_Click);
			// 
			// lblNoOfFilesBackedUp
			// 
			this->lblNoOfFilesBackedUp->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->lblNoOfFilesBackedUp->Location = System::Drawing::Point(243, 114);
			this->lblNoOfFilesBackedUp->Name = L"lblNoOfFilesBackedUp";
			this->lblNoOfFilesBackedUp->Size = System::Drawing::Size(181, 22);
			this->lblNoOfFilesBackedUp->TabIndex = 6;
			// 
			// lblBackupStartTime
			// 
			this->lblBackupStartTime->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->lblBackupStartTime->Location = System::Drawing::Point(6, 114);
			this->lblBackupStartTime->Name = L"lblBackupStartTime";
			this->lblBackupStartTime->Size = System::Drawing::Size(181, 22);
			this->lblBackupStartTime->TabIndex = 5;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(6, 88);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(84, 13);
			this->label14->TabIndex = 4;
			this->label14->Text = L"Backup Started:";
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->groupBox2);
			this->tabPage1->Controls->Add(this->groupBox1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(782, 453);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Backup Status";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->lblTransferRate);
			this->groupBox2->Controls->Add(this->label20);
			this->groupBox2->Controls->Add(this->lblNoOfFilesMissed);
			this->groupBox2->Controls->Add(this->label18);
			this->groupBox2->Controls->Add(this->label17);
			this->groupBox2->Controls->Add(this->lblNoOfFilesBackedUp);
			this->groupBox2->Controls->Add(this->lblBackupStartTime);
			this->groupBox2->Controls->Add(this->label14);
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Controls->Add(this->lblCurrentFile);
			this->groupBox2->Controls->Add(this->lblCurrentOperation);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Location = System::Drawing::Point(6, 0);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(770, 229);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 16);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(93, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Current Operation:";
			// 
			// lblCurrentFile
			// 
			this->lblCurrentFile->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->lblCurrentFile->Location = System::Drawing::Point(6, 196);
			this->lblCurrentFile->Name = L"lblCurrentFile";
			this->lblCurrentFile->Size = System::Drawing::Size(439, 22);
			this->lblCurrentFile->TabIndex = 3;
			// 
			// lblCurrentOperation
			// 
			this->lblCurrentOperation->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->lblCurrentOperation->Location = System::Drawing::Point(6, 39);
			this->lblCurrentOperation->Name = L"lblCurrentOperation";
			this->lblCurrentOperation->Size = System::Drawing::Size(181, 23);
			this->lblCurrentOperation->TabIndex = 1;
			this->lblCurrentOperation->Text = L"Idle";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 174);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(60, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Current File";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->btnRunSavedSetNow);
			this->groupBox1->Controls->Add(this->btnDeleteSavedSet);
			this->groupBox1->Controls->Add(this->btnEditSavesSet);
			this->groupBox1->Controls->Add(this->lvBackupSet);
			this->groupBox1->Location = System::Drawing::Point(6, 235);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(770, 208);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Saved Backup Sets";
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Controls->Add(this->tabPage5);
			this->tabControl1->Location = System::Drawing::Point(-4, -2);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(790, 479);
			this->tabControl1->TabIndex = 1;
			// 
			// tabPage5
			// 
			this->tabPage5->Location = System::Drawing::Point(4, 22);
			this->tabPage5->Name = L"tabPage5";
			this->tabPage5->Padding = System::Windows::Forms::Padding(3);
			this->tabPage5->Size = System::Drawing::Size(782, 453);
			this->tabPage5->TabIndex = 4;
			this->tabPage5->Text = L"About";
			this->tabPage5->UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(783, 474);
			this->Controls->Add(this->tabControl1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainForm";
			this->Text = L"ASAP";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->groupBox14->ResumeLayout(false);
			this->groupBox14->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			this->groupBox13->ResumeLayout(false);
			this->groupBox13->PerformLayout();
			this->groupBox12->ResumeLayout(false);
			this->groupBox11->ResumeLayout(false);
			this->groupBox11->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox17->ResumeLayout(false);
			this->groupBox17->PerformLayout();
			this->groupBox16->ResumeLayout(false);
			this->tabPage4->ResumeLayout(false);
			this->groupBox15->ResumeLayout(false);
			this->groupBox15->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->groupBox10->ResumeLayout(false);
			this->groupBox10->PerformLayout();
			this->groupBox9->ResumeLayout(false);
			this->groupBox9->PerformLayout();
			this->groupBox8->ResumeLayout(false);
			this->groupBox8->PerformLayout();
			this->groupBox7->ResumeLayout(false);
			this->groupBox7->PerformLayout();
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->tabPage1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->ResumeLayout(false);

		}

#pragma endregion
	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
				//dtpTime->Format = DateTimePickerFormat::Time;
			 }

	private: System::Void cbSchedule_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void btnBrowseDes_Click(System::Object^  sender, System::EventArgs^  e) {
		FolderBrowserDialog dlg;
		System::Windows::Forms::DialogResult result = dlg.ShowDialog();
		if (result == System::Windows::Forms::DialogResult::OK)
		{
			tbDes->Text = dlg.SelectedPath;
		}
	}

private: System::Void cbSchedule_Click(System::Object^  sender, System::EventArgs^  e) {
	Job->Schedule(cbSchedule->Checked);
	EnableDays(cbSchedule->Checked);
}

private: System::Void Backup_Type_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	RadioButton^ bt = (RadioButton^)sender;
	if (bt->Checked)	 Job->Type(bt->Text);
}

private: System::Void cbEncryption_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

}

private: System::Void cbLogging_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 Job->Logging(((CheckBox^)sender)->Checked);
}

private: System::Void cbDefaultLog_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			
}

private: System::Void cbModifyDate_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			
}

private: System::Void cbArchiveBit_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
}

private: System::Void cbDayChange(System::Object^  sender, System::EventArgs^  e) {
	CheckBox^ cb = (CheckBox^)sender;
	Job->Days(System::Convert::ToByte(cb->Tag->ToString()), cb->Checked);
}

private: System::Void labelEveryday_Click(System::Object^  sender, System::EventArgs^  e) {
	CheckUncheckEveryDay(true);
}

private: System::Void tbDes_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 Job->Path(((TextBox^)sender)->Text);
}

private: System::Void tbSetName_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 Job->Name(((TextBox^)sender)->Text);
}

private: System::Void btnSave_Click(System::Object^  sender, System::EventArgs^  e) {
	if (tbSetName->Text->Trim()->Length == 0)
	{
		MessageBox::Show("Backup Set Name can not be empty.");
		return;
	}

	ArrayList^ souurceFiles = Job->Files();
	if (souurceFiles->Count == 0)
	{
		MessageBox::Show("Select at least one source location for back up operation.");
		return;
	}

	Jobs.add(Job);
	Jobs.Save(Job);
	MessageBox::Show("Job saved successfully.");
	addJobtoJobList();
	btnReset_Click(nullptr, nullptr);
}

private: System::Void trSelect_BeforeExpand(System::Object^  sender, System::Windows::Forms::TreeViewCancelEventArgs^  e) {
	// First zap the dummy node, assuming there is one
	if (e->Node->Nodes->Count != 0)
		e->Node->Nodes->RemoveAt(0);
	buildTree(e->Node);
}

private: 
	System::Void trSelect_AfterCheck(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
	if (e->Action != TreeViewAction::Unknown)
	{
		if (e->Node->Nodes->Count > 0)
		{
			this->CheckAllChildNodes(e->Node, e->Node->Checked);
		}
		else
			Job->Files(e->Node->FullPath,e->Node->Checked);
	}
}

// Updates all child tree nodes recursively. 
void CheckAllChildNodes(TreeNode^ treeNode, bool nodeChecked)
{
	IEnumerator^ myEnum = treeNode->Nodes->GetEnumerator();
	while (myEnum->MoveNext())
	{
		TreeNode^ node = safe_cast<TreeNode^>(myEnum->Current);
		node->Checked = nodeChecked;
		if (node->Nodes->Count > 0)
		{
			// If the current node has child nodes, call the CheckAllChildsNodes method recursively. 
			this->CheckAllChildNodes(node, nodeChecked);
		}
		else
			Job->Files(node->FullPath, node->Checked);
	}
}

void buildTree(TreeNode^ node)
{
	// Get a list of subdirectories
	array<String^>^ dirs;
	array<String^>^ files;
	try
	{
		dirs = Directory::GetDirectories(node->FullPath);
		files = Directory::GetFiles(node->FullPath);
	}
	catch (System::Exception^ pe)
	{
		MessageBox::Show(pe->Message, "Some Error!");
		return;
	}

	// Add a child node for each one
	for (int i = 0; i<dirs->Length; i++)
	{
		String^ dirName = dynamic_cast<String^>(dirs->GetValue(i));
		String^ s = Path::GetFileName(dirName);
	
		array<TreeNode^>^ n = node->Nodes->Find(s, true);
		if (n->Length==0){
			TreeNode^ tn = gcnew TreeNode(s);
			tn->Name = s;
			tn->Checked = node->Checked;
			node->Nodes->Add(tn);
			// Add a dummy child node
			//tn->Nodes->Add(gcnew TreeNode("<dummy>"));
			tn->Nodes->Add(gcnew TreeNode(""));
		}
	}
	// Create new objects to represent the files Next, the files

	for (int i = 1; i < files->Length; i++)
	{
		String^ dirName = dynamic_cast<String^>(files->GetValue(i));
		String^ s = Path::GetFileName(dirName);

		array<TreeNode^>^ n = node->Nodes->Find(s, true);
		if (n->Length == 0){
			TreeNode^ tn = gcnew TreeNode(s);
			tn->Name = s;
			tn->Checked = node->Checked;
			tn->SelectedImageIndex = 2;
			tn->ImageIndex = 2;
			node->Nodes->Add(tn);
		}
	}
}


	private: System::Void dtpTime_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		Job->Time(dtpTime->Value.TimeOfDay);
	}

	private: System::Void btnRunSavedSetNow_Click(System::Object^  sender, System::EventArgs^  e) {
		try
		{
			ListView::SelectedListViewItemCollection^ list = lvBackupSet->SelectedItems;
			if (list->Count > 0)
			{
				ListViewItem^ item = list[0];
				String^ jobName = item->Text;
				Jobs.StartJob(jobName);
			}
		}
		catch (System::Exception^ pe)
		{
			MessageBox::Show(pe->Message, "Some Error!");
		}
	}

	private: System::Void lvBackupSet_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		ListView^ listView = (ListView ^)(sender);
		if (listView != nullptr && listView->SelectedItems->Count > 0)
		{
			EnableDisableJobListBoxbuttons(true);
		}
		else
		{
			EnableDisableJobListBoxbuttons(false);
		}
	}

	private: System::Void btnDeleteSavedSet_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		try
		{
			ListViewItem^ item = lvBackupSet->SelectedItems[0];
			String^ jobName = item->Text;
			Jobs.deleteJob(jobName);

			MessageBox::Show("Job deleted successfully.");
		}
		catch (System::Exception^ pe)
		{
			MessageBox::Show(pe->Message, "Delete Error!");
		}
	}
	
	protected:
		void btnEditSavesSet_Click(System::Object^  sender, System::EventArgs^  e);
	
	public:
		void EnableDisableJobListBoxbuttons(bool flag);
		void setCurrentOperation(String^ jobName);
		void setBackUpStartTime(void);
		void incrementFileBackUpCount(void);
		void incrementFileMissedCount(void);
		void setCurrentBackupFile(String^ backUpFile);
		void markJobCompleted();
		void resetCurrentOperation(void);
		void EnableDays(bool bEnabled);
		void addJobtoJobList(void);

		private: 
			System::Void btnReset_Click(System::Object^  sender, System::EventArgs^  e);
			
			void initializeFileSelection();
			void CheckUncheckEveryDay(bool bChecked);
};
}


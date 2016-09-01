#pragma once

/*
Author: Neil Kenny 

Automaitcally generated gui created by designer

*/
#include "VideoHandler.h"
#include "BallObserver.h"
#include "JugglingDataObserver.h"
#include "IManagedBallObserver.h"
#include "IManagedJugglingDataObserver.h"
#include "SHeightSiteswap.h"
namespace JugglingAnalyser {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	/// <summary>
	/// Summary for Form1
	/// </summary>
	
	public ref class Form1 : public System::Windows::Forms::Form, public IManagedBallObserver, public IManagedJugglingDataObserver
	{
	public:
		Form1(void)
		{
			VideoHandlerObject = new VideoHandler();
			databaseObject = new DatabaseHandler();
			m_ballObserver = NULL;
			m_throwObserver = NULL;

			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			
			std::vector<std::vector<std::string>> tutorialData = databaseObject->Query("SELECT name FROM TUTORIAL;");
			for(std::vector<std::vector<std::string>>::iterator it = tutorialData.begin(); it < tutorialData.end(); it++){
				std::vector<std::string> row = *it; 

				
				String^ result = gcnew System::String(row[0].c_str());
				this->listBox1->Items->Add(result);
			}
		}

		virtual void BallsUpdated( const std::vector<Ball> balls )
		{
			this->listBox3->BeginUpdate();
			
			this->listBox3->Items->Clear();
			for( std::vector<Ball>::const_iterator it = balls.begin(); it != balls.end(); ++it )
			{
				this->listBox3->Items->Add( String::Format( "Ball {0} siteswap: {1} flight time: {2} ", it->getBallNum(), it->getSiteswap(), it->getFlightTime() ) );
			}

			this->listBox3->EndUpdate();
		}

		virtual void JugglingDataUpdated( const std::vector<ThrowData> siteswapData )
		{
			this->listBox4->BeginUpdate();
				

				for(std::vector<ThrowData>::const_iterator it = siteswapData.begin(); it != siteswapData.end(); ++it){
				
					//this->listBox4->Items->Add( String::Format("Siteswap {0}: Average Height: {1} , \n average Flight time: {2} , average angle of throw: {3}, average z range", it->siteswap, it->height, it->theta, it->z ) );
					this->listBox4->Items->Add( String::Format("Siteswap {0} average data", it->siteswap) );
					this->listBox4->Items->Add( String::Format("	Height: {0}", it->height) );
					this->listBox4->Items->Add( String::Format("	Flight time: {0}", it->flightTime) );
					this->listBox4->Items->Add( String::Format("	Angle of throw: {0}",it->theta) );
					this->listBox4->Items->Add( String::Format("	Z(in cm): {0}",it->z) );
					}	

			this->listBox4->EndUpdate();
		}


		

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if( m_ballObserver != NULL )
			{
				delete m_ballObserver;
				m_ballObserver = NULL;
			}

			if(m_throwObserver != NULL)
			{
				delete m_throwObserver; 
				m_throwObserver = NULL; 
			}

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^  listBox1;
	protected: 
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::RadioButton^  radioButton3;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		VideoHandler *VideoHandlerObject;
		DatabaseHandler *databaseObject;
		BallObserver* m_ballObserver;
		JugglingDataObserver* m_throwObserver;

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::ListBox^  listBox2;
	private: System::Windows::Forms::ListBox^  listBox3;
	private: System::Windows::Forms::Button^  button2;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::ListBox^  listBox4;
	private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::Button^  button3;
		 System::ComponentModel::Container ^components;
		
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->listBox3 = (gcnew System::Windows::Forms::ListBox());
			this->listBox4 = (gcnew System::Windows::Forms::ListBox());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(13, 13);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(68, 17);
			this->radioButton1->TabIndex = 1;
			this->radioButton1->Text = L"Webcam";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton1_CheckedChanged);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(13, 37);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(55, 17);
			this->radioButton2->TabIndex = 2;
			this->radioButton2->Text = L"Kinect";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton2_CheckedChanged);
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(13, 61);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(41, 17);
			this->radioButton3->TabIndex = 3;
			this->radioButton3->Text = L"File";
			this->radioButton3->UseVisualStyleBackColor = true;
			this->radioButton3->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton3_CheckedChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(13, 149);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Threshold trackbar";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(13, 194);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 8;
			this->button2->Text = L"Get base height";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(127, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(91, 13);
			this->label1->TabIndex = 10;
			this->label1->Text = L"Training programs";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click_1);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(500, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(85, 13);
			this->label2->TabIndex = 11;
			this->label2->Text = L"Program content";
			this->label2->Click += gcnew System::EventHandler(this, &Form1::label2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(127, 165);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(70, 13);
			this->label3->TabIndex = 12;
			this->label3->Text = L"Juggling data";
			this->label3->Click += gcnew System::EventHandler(this, &Form1::label3_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(500, 165);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(74, 13);
			this->label4->TabIndex = 14;
			this->label4->Text = L"Siteswap data";
			this->label4->Click += gcnew System::EventHandler(this, &Form1::label4_Click);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(127, 28);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(310, 108);
			this->listBox1->TabIndex = 0;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listBox1_SelectedIndexChanged);
			// 
			// listBox2
			// 
			this->listBox2->FormattingEnabled = true;
			this->listBox2->Location = System::Drawing::Point(500, 28);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(272, 108);
			this->listBox2->TabIndex = 6;
			// 
			// listBox3
			// 
			this->listBox3->FormattingEnabled = true;
			this->listBox3->Location = System::Drawing::Point(127, 184);
			this->listBox3->Name = L"listBox3";
			this->listBox3->Size = System::Drawing::Size(310, 95);
			this->listBox3->TabIndex = 7;
			this->listBox3->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listBox3_SelectedIndexChanged_1);
			// 
			// listBox4
			// 
			this->listBox4->FormattingEnabled = true;
			this->listBox4->Location = System::Drawing::Point(500, 184);
			this->listBox4->Name = L"listBox4";
			this->listBox4->Size = System::Drawing::Size(272, 95);
			this->listBox4->TabIndex = 13;
			// 
			// folderBrowserDialog1
			// 
			this->folderBrowserDialog1->HelpRequest += gcnew System::EventHandler(this, &Form1::folderBrowserDialog1_HelpRequest);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(13, 237);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 15;
			this->button3->Text = L"All throw data";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(829, 389);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton3);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->listBox2);
			this->Controls->Add(this->listBox3);
			this->Controls->Add(this->listBox4);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->button2);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Shown += gcnew System::EventHandler(this, &Form1::onFormShown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void radioButton1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(radioButton1->Checked){
					 VideoHandlerObject->setFeed(1);
				 
					 VideoHandlerObject->ManageFeeds();
				 }
			 }
	private: System::Void radioButton2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(radioButton2->Checked){
					 VideoHandlerObject->setFeed(2);
					 VideoHandlerObject->ManageFeeds();
				 }
			 }
	private: System::Void radioButton3_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				if(radioButton3->Checked){
					 VideoHandlerObject->setFeed(3);
					 OpenFileDialog^ openFileObject = gcnew OpenFileDialog;
					 openFileObject->ShowDialog();
					 VideoHandlerObject->setFileUri(openFileObject->FileName);
					 VideoHandlerObject->ManageFeeds();
				}
			 }
private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {

			listBox2->Items->Clear();
			
			std::string sIndex = std::to_string(static_cast<long long>(listBox1->SelectedIndex));
			std::string sQuery = "SELECT name FROM PROGRAM where TUTORIALID = " + sIndex + " ;";
			 

			 char *cQuery = new char[sQuery.length() + 1];
			 strcpy(cQuery, sQuery.c_str());

			
			std::vector<std::vector<std::string>> trainingProgramData = databaseObject->Query(cQuery);
			for(std::vector<std::vector<std::string>>::iterator it = trainingProgramData.begin(); it < trainingProgramData.end(); it++){
				std::vector<std::string> row = *it; 

				
				String^ result = gcnew System::String(row[0].c_str());
				this->listBox2->Items->Add(result);
			}

}

private: System::Void folderBrowserDialog1_HelpRequest(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

			 VideoHandlerObject->createTrackBar("Thresholding trackbar");
		 }

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 VideoHandlerObject->trackBasePattern();

		 }
private: System::Void onFormShown(System::Object^  sender, System::EventArgs^  e) 
		 {
 
			 m_throwObserver = new JugglingDataObserver(this);
			 VideoHandlerObject->addThrowObserver(m_throwObserver);
			// m_throwObserver->test();

			 m_ballObserver = new BallObserver(this);
			 VideoHandlerObject->addBallObserver(m_ballObserver);
			
			 // mB_ballObserver->test();

			
		 }
private: System::Void listBox3_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void listBox3_SelectedIndexChanged_1(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void trackBar1_Scroll(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label1_Click_1(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label4_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

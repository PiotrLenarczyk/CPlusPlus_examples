#pragma once


namespace fileGenerator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected: 
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox1;


	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 53);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 32);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Generuj";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(166, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(25, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"MiB";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(2, 12);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(158, 20);
			this->textBox1->TabIndex = 2;
			this->textBox1->Text = L"1";
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(2, 37);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(199, 10);
			this->progressBar1->TabIndex = 5;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(102, 50);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"status";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(105, 71);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(0, 13);
			this->label3->TabIndex = 7;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(213, 97);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"File Generator";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	typedef unsigned char		u8;
	typedef unsigned int		u32;
	typedef unsigned long long	u64;
	#define RAND_A	(1103515245)
	#define RAND_C	(12345)
	#define RAND_M	(0x80000000)
	private:	u64 seed;
	private:	void srand8B( u64 setSeed ){ seed = setSeed; };
	private:	u64 rand8B( u8 hex )
	{	return seed = ( (RAND_A * (seed ^ hex)) + RAND_C) % RAND_M;
	};
	private:	u64 rand8B( void )
	{	return seed = ( (RAND_A * seed) + RAND_C) % RAND_M;
	};
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				#define MAX_DISC_SPEED	800.0f
				int fileSizeB, fileSizeMiB; float percentage, speed; String^ fileSizeStr; char speedArr[ 0x40 ]; char fileName[ 0x10 ];
				clock_t t;
				FILE *pFile;
				percentage = 0.0f;
				label2->Text = "started disk write"; label2->Refresh();
				label3->Text = ""; label3->Refresh();
				
				//get write size
				fileSizeStr = textBox1->Text;
				fileSizeMiB = System::Int64::Parse( fileSizeStr );
				fileSizeB = fileSizeMiB * 1024 * 1024;
				//initialize random generator
				srand(time(0)); seed = rand();
				for ( int i = 0x0; i < (rand() % 0x100); i++ )
					rand8B( (u8)rand() );	
				//get random buffer
				for ( int j = 0x0; j < (sizeof( data8B ) / sizeof(u64)); j++ )
					data8B[ j ] = rand8B() ^ ( rand8B() << 32 );
				itoa( rand8B(), fileName, 10 );
				fileName[ 8 ] = '.';fileName[ 9 ] = 't';fileName[ 10 ] = 'x';fileName[ 11 ] = 't';fileName[ 12 ] = NULL;
				//write to file
				pFile = fopen( fileName, "wb" );
				t = clock(); 
					for ( int i = 0x0; i < fileSizeMiB; i++ )
					{	//write random buffer to file
						fwrite( (char*)&data8B[0], sizeof( char ), sizeof( data8B ), pFile );
						percentage = float(i+1) / float(fileSizeMiB); percentage *= 100.0f;
						progressBar1->Value = (int)percentage; progressBar1->Refresh();
					};
				fclose( pFile );
				t = clock() - t;
				label2->Text = "done"; label2->Refresh();
				speed = (t * 1.0f) / (float)(CLOCKS_PER_SEC);
				speed = fileSizeMiB / speed; 
				if((speed > 0.0f)&&(speed < MAX_DISC_SPEED))
				{	sprintf( speedArr, "%.1f [MiBps]", speed );
					label3->Text = gcnew String( speedArr ); label3->Refresh();
				};
			 }
	};
}


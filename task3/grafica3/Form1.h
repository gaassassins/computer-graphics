#pragma once


namespace grafica3 {

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
	private: System::Collections::Generic::List<line> lines; //������ lines ���� list
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::Button^  btnOpen;



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
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->btnOpen = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// openFileDialog
			// 
			this->openFileDialog->DefaultExt = L"txt";
			this->openFileDialog->FileName = L"openFileDialog1";
			this->openFileDialog->Filter = L"��������� ����� (*.txt)|*.txt|��� ����� (*.*)|*.*";
			this->openFileDialog->Title = L"������� ����";
			//this->openFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openFileDialog_FileOk);
			// 
			// btnOpen
			// 
			this->btnOpen->Location = System::Drawing::Point(12, 12);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(75, 23);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = L"�������";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &Form1::btnOpen_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(300, 300);
			this->Controls->Add(this->btnOpen);
			this->KeyPreview = true;
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->ResumeLayout(false);
		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 lines.Clear(); //������� ������ �������� � ������
				 unit (T); //������������� ������� �
			 }

	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Graphics^ g = e->Graphics; //������� ���������
				 System::Drawing::Pen^ blackPen = gcnew Pen(Color::Black);
				 blackPen->Width = 2;

				 for (int i = 0; i < lines.Count; i++) { //������ ����� � �����
					 point2vec(lines[i].start, A); //��������� ��������� ����� ��� ��������
					 point2vec(lines[i].end, B);

					 vec A1, B1; //�������� ����� � ���������� ����������� � ��������������� ������� �
					 timesMatVec(T,A,A1);
					 timesMatVec(T,B,B1);

					 point a, b; //������� � ���������
					 vec2point(A1, a);
					 vec2point(B1, b);
					 g ->DrawLine(blackPen,
						 a.x,System::Windows::Forms::Form::ClientRectangle.Height-a.y,
						 b.x,System::Windows::Forms::Form::ClientRectangle.Height-b.y); //������ ����� �� ������ 9
				 }
			 }
	private: System::Void openFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 }

	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {//������ �������� �����
				 if (this->openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK){//���������� �� �� ������� "��"
						 wchar_t fileName[1024];
						 for (int i = 0; i < openFileDialog->FileName->Length; i++)
							 fileName[i] = openFileDialog->FileName[i];
						 fileName[openFileDialog->FileName->Length] = '\0'; //������ �� �����

						 std::ifstream in;
						 in.open(fileName);
						 if (in.is_open()) { //����  ���� ��������
							 lines.Clear(); //������� ������ lines
							 std::string str;
							 getline (in, str);

							 while (in) { //��������� ���������
								 if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) { //�� �������� �� ��� ������ ������� ��� ������� � �������������
										 std::stringstream s(str);
										 line l;
										 s >> l.start.x >> l.start.y >> l.end.x >> l.end.y; //�������� ���������� �����
										 std::string linename;
										 s >> linename;
										 l.name = gcnew String(linename.c_str());
										 lines.Add(l); //�������� ������� � ����� ������
								 }
								 getline (in, str);
							 }
						 }
						 this->Refresh();
				 }
			 }

	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 mat R,T1; //������� �������������� � ��������������� ������� ��� ������ ���������� ������������
				 float Heig,Widt; //������ � ������

				 switch(e->KeyCode){

										 case Keys::W : //�����
						 move(0, 1, R);
						 break;

					 case Keys::S : //����
						 move(0, -1, R);
						 break;

					 case Keys::A : //�����
						 move(-1, 0, R);
						 break;

					 case Keys::D : //������
						 move(1, 0, R);
						 break;

					 case Keys::E : //������� �� ������� �������
						 rotate(0.05, R);
						 break;

					 case Keys::X : //���������� �����������
						 scale(1.1,1.1, R);
						 break;

					 case Keys::Q : //������� ������ ������� ������� 
						 rotate_p(0.05, R);
						 break;

					 case Keys::Z : //���������� �����������
						 scale(1/1.1, 1/1.1, R);
						 break;

					 case Keys::G : //������� �������� �����
						 move(0, -10, R);
						 break;

					 case Keys::T : //������� �������� ����
						 move(0, 10, R);
						 break;

					 case Keys::F : //������� �������� �����
						 move(10, 0, R);
						 break;

					 case Keys::H : //������� �������� ������
						 move(-10, 0, R);
						 break;

					 case Keys::U : //���������� ����������� ������������ 
						 z_goriz(System::Windows::Forms::Form::ClientRectangle.Height,R);
						 break;

					 case Keys::J : //���������� ����������� ��������������
						 z_vert(System::Windows::Forms::Form::ClientRectangle.Width,R);
						 break;

					 case Keys::Y : //������� �� ������� ������� �� ������ �����
						 move(-System::Windows::Forms::Form::ClientRectangle.Width/2, 
							 -System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 times(R,T,T1);//����������� ������� R �� T � ���������� � T1
						 set(T1,T); //T1 ������������ � T
						 rotate(0.1, R);
						 times(R,T,T1);//����������� ������� R �� T � ���������� � T1
						 set(T1,T); //T1 ������������ � T
						 move(System::Windows::Forms::Form::ClientRectangle.Width/2, 
							 System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 break;

					 case Keys::R : //������� ������ ������� ������� �� ������ �����
						 move(-System::Windows::Forms::Form::ClientRectangle.Width/2, 
							 -System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 times(R,T,T1);//����������� ������� R �� T � ���������� � T1
						 set(T1,T); //T1 ������������ � T
						 rotate_p(0.1, R);
						 times(R,T,T1);//����������� ������� R �� T � ���������� � T1
						 set(T1,T); //T1 ������������ � T
						 move(System::Windows::Forms::Form::ClientRectangle.Width/2, 
							 System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 break;

					 case Keys::C : //���������� ����������� ������������ �����
						 move(-System::Windows::Forms::Form::ClientRectangle.Width/2, 
							 -System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 times(R,T,T1);//����������� ������� R �� T � ���������� � T1
						 set(T1,T);//T1 ������������ � T
						 scale(1/1.1, 1/1.1, R);
						 times(R,T,T1);//����������� ������� R �� T � ���������� � T1
						 set(T1,T);//T1 ������������ � T
						 move(System::Windows::Forms::Form::ClientRectangle.Width/2, 
							 System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 break;

					 case Keys::V: //���������� ����������� ������������ �����
						 move(-System::Windows::Forms::Form::ClientRectangle.Width/2, 
							 -System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 times(R,T,T1);//����������� ������� R �� T � ���������� � T1
						 set(T1,T);//T1 ������������ � T
						 scale(1.1,1.1, R);
						 times(R,T,T1);//����������� ������� R �� T � ���������� � T1
						 set(T1,T);//T1 ������������ � T
						 move(System::Windows::Forms::Form::ClientRectangle.Width/2, 
							 System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 break;

					 case Keys::I: //���������� �� ���������
						 move(0, -System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 times(R,T,T1);//����������� ������� R �� T � ���������� � T1
						 set(T1,T);//T1 ������������ � T
						 scale(1,1/1.1, R);
						 times(R,T,T1);//����������� ������� R �� T � ���������� � T1
						 set(T1,T);//T1 ������������ � T
						 move(0, System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 break;

					 case Keys::O: //���������� �� ���������
						 move(0, -System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 times(R,T,T1);//����������� ������� R �� T � ���������� � T1
						 set(T1,T);//T1 ������������ � T
						 scale(1, 1.1, R);
						 times(R,T,T1);//����������� ������� R �� T � ���������� � T1
						 set(T1,T);//T1 ������������ � T
						 move(0, System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 break;

					 case Keys::K: //������ �� �����������
						 move(-System::Windows::Forms::Form::ClientRectangle.Width/2, 0, R);
						 times(R,T,T1); //����������� ������� R �� T � ���������� � T1
						 set(T1,T);//T1 ������������ � T
						 scale(1/1.1,1, R);
						 times(R,T,T1);//����������� ������� R �� T � ���������� � T1
						 set(T1,T);//T1 ������������ � T
						 move(System::Windows::Forms::Form::ClientRectangle.Width/2, 0, R);
						 break;

					 case Keys::L: //���������� �� �����������
						 move(-System::Windows::Forms::Form::ClientRectangle.Width/2, 0, R);
						 times(R,T,T1);//����������� ������� R �� T � ���������� � T1
						 set(T1,T);//T1 ������������ � T
						 scale(1.1,1, R);
						 times(R,T,T1);//����������� ������� R �� T � ���������� � T1
						 set(T1,T);//T1 ������������ � T
						 move(System::Windows::Forms::Form::ClientRectangle.Width/2, 0, R);
						 break;

					 case Keys::Escape: // ����� � �������� ��������� �����������
						 unit(R);
						 unit(T);
						 break;

					 default: // � ������� R ������������ ��������� ������� � ������ �������
						 unit(R);
				 }
				 times(R,T,T1);
				 set(T1,T);
				 this->Refresh();
			 }

	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 this->Refresh();
			 }
	};
}


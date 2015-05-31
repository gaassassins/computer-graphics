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

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::Button^  btnOpen;
	private: System::Collections::Generic::List<line> lines;
			 float left, right, top, bottom;
			 float Wcx, Wcy, Wx, Wy;
			 float Vcx, Vcy, Vx, Vy;
			 bool drawNames;




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
			this->ClientSize = System::Drawing::Size(483, 388);
			this->Controls->Add(this->btnOpen);
			this->DoubleBuffered = true;
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
				 
				 drawNames = false;
				 Rectangle rect = Form::ClientRectangle;

				 left = 100;
				 top = 100;
				 bottom = 100;
				 right = 100;

				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;
				
				 lines.Clear(); //������� ������ �������� � ������
				 unit (T); //������������� ������� �
			 }

	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				
				 Graphics^ g = e->Graphics; //������� ���������

				 System::Drawing::Pen^ blackPen = gcnew Pen(Color::Black);
				 blackPen->Width = 2;

				System::Drawing::Pen^ redPen = gcnew Pen(Color::Red);
				redPen->Width = 4;

				g->DrawRectangle(redPen, Wcx, top, Wx, Wy);
				 point min = {left, top};
				 point max = {System::Windows::Forms::Form::ClientRectangle.Width - right, 
					 System::Windows::Forms::Form::ClientRectangle.Height - bottom};
				 
				 System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 8);
				 SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);


				 for (int i = 0; i < lines.Count; i++) { //������ ����� � �����
					 
					 point start = lines[i].start;
					 point end = lines[i].end;

					 vec A, B;
					 point2vec(start, A); //��������� ��������� ����� ��� ��������
					 point2vec(end, B);

					 vec A1, B1; //�������� ����� � ���������� ����������� � ��������������� ������� �
					 timesMatVec(T,A,A1);
					 timesMatVec(T,B,B1);

					 point a, b; //������� � ���������
					 vec2point(A1, a);
					 vec2point(B1, b);

					 if (clip(a, b, min, max)) 
					 {
						 g->DrawLine(blackPen, a.x, a.y, b.x, b.y);

						 float sx = a.x + (b.x - a.x) / 2;
						 float sy = a.y + (b.y - a.y) / 2;
						 float delta = 10;

						 if(
							 drawNames 
							 && sx >= left + delta 
							 && sx <= left + Wx - delta
							 && sy >= top + delta 
							 && sy <= top + Wy - delta) 
						 {
							 g->DrawString(lines[i].name, drawFont, drawBrush, sx, sy);
						 }

					 }
				 }
			 }

	private: System::Void openFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 }

	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {//������ �������� �����
				 
				 if (this->openFileDialog->ShowDialog() 
					 == System::Windows::Forms::DialogResult::OK){//���������� �� �� ������� "��"

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
						 bool read = false;

						 while (in) { //��������� ���������
							 if ((str.find_first_not_of(" \t\r\n") 
								 != std::string::npos) 
								 && (str[0] != '#')) { //�� �������� �� ��� ������ ������� ��� ������� � �������������
								
								 std::stringstream s(str);
								 line l;
								 std::string linename;

								 float x, y, w, h;
								 if(!read) {

									 s >> x >> y >> w >> h;

									 Vcx = x;
									 Vcy = y;
									 Vx = w;
									 Vy = h;

									 read = true;
								 }
								 else {
									 s >> l.start.x >> l.start.y >> l.end.x >> l.end.y >> linename;
									 l.name = gcnew String(linename.c_str());
									 lines.Add(l); //�������� ������� � ����� ������
								 }
							 }
							 getline (in, str);
						 }
					 }
					 frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
					 this->Refresh();
				 }
			 }

	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 mat R,T1; //������� �������������� � ��������������� ������� ��� ������ ���������� ������������
				 unit(R);

				 switch(e->KeyCode){

					 case Keys::W : //�����
						 move(0, -1, R);
						 break;

					 case Keys::S : //����
						 move(0, 1, R);
						 break;

					 case Keys::A : //�����
						 move(-1, 0, R);
						 break;

					 case Keys::D : //������
						 move(1, 0, R);
						 break;

					 case Keys::E : //������� �� ������� �������
						 rotate(0.05, left, top, R);
						 break;

					 case Keys::X : //���������� �����������
						 scale(1.1,1.1, R);
						 break;

					 case Keys::Q : //������� ������ ������� ������� 
						 rotate(-0.05, left, top, R);
						 break;

					 case Keys::Z : //���������� �����������
						 scale(1/1.1, 1/1.1, R);
						 break;

					 case Keys::G : //������� �������� ����
						 move(0, 10, R);
						 break;

					 case Keys::T : //������� �������� �����
						 move(0, -10, R);
						 break;

					 case Keys::F : //������� �������� �����
						 move(-10, 0, R);
						 break;

					 case Keys::H : //������� �������� ������
						 move(10, 0, R);
						 break;

					 case Keys::U : //���������� ����������� �������������� 
						 z_goriz(R);
						 times(R, T, T1);
						set(T1, T);
						move(0, System::Windows::Forms::Form::ClientRectangle.Height - bottom + top, R);	
						 break;

					 case Keys::J : //���������� ����������� ������������
						 z_vert(R);
						 times(R, T, T1);
						set(T1, T);
						move(System::Windows::Forms::Form::ClientRectangle.Width - right + left, 0, R);

						 break;

					 case Keys::Y : //������� �� ������� ������� �� ������ �����
						 rotate(0.05, System::Windows::Forms::Form::ClientRectangle.Width/2, System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 break;

					 case Keys::R : //������� ������ ������� ������� �� ������ �����
						 rotate(-0.05, System::Windows::Forms::Form::ClientRectangle.Width/2, System::Windows::Forms::Form::ClientRectangle.Height/2, R);
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

					 case Keys::I: //������� �� ���������
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

					 case Keys::P:

						drawNames = !drawNames;
						break;

					 case Keys::Escape: // ����� � �������� ��������� �����������
						 frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
						 }

				 times(R,T,T1);
				 set(T1,T);
				 this->Refresh();
			 }

	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {

				 float oldWx = Wx;
				 float oldWy = Wy;

				 Wcx = left;
				 Wcy = System::Windows::Forms::Form::ClientRectangle.Height - bottom;
				 Wx = System::Windows::Forms::Form::ClientRectangle.Width - left - right;
				 Wy = System::Windows::Forms::Form::ClientRectangle.Height - top - bottom;

				 mat R, T1;

				 move(-Wcx, 
					  -top, 
					   R);

				 times(R, T, T1);

				 scale(Wx / oldWx, 
					   Wy / oldWy, 
					   R);

				 times(R, T, T1);

				 move(Wcx, top, R);

				 times(R, T, T1);

				 set(T1, T);

				 this->Refresh();
			 }
	};
}


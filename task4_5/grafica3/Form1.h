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
			this->openFileDialog->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
			this->openFileDialog->Title = L"Открыть файл";
			// 
			// btnOpen
			// 
			this->btnOpen->Location = System::Drawing::Point(12, 12);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(75, 23);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = L"Открыть";
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
				
				 lines.Clear(); //Очищаем список отрезков в начале
				 unit (T); //Инициализация матрицы Т
			 }

	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				
				 Graphics^ g = e->Graphics; //область рисования

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


				 for (int i = 0; i < lines.Count; i++) { //Рисуем линии в цикле
					 
					 point start = lines[i].start;
					 point end = lines[i].end;

					 vec A, B;
					 point2vec(start, A); //Считываем параметры точек для отрезков
					 point2vec(end, B);

					 vec A1, B1; //Получаем точки в однородных координатах с преобразованием матрицы Т
					 timesMatVec(T,A,A1);
					 timesMatVec(T,B,B1);

					 point a, b; //Обратно в декартову
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

	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {//Чтение входного файла
				 
				 if (this->openFileDialog->ShowDialog() 
					 == System::Windows::Forms::DialogResult::OK){//Завершится ли по нажатию "ОК"

					 wchar_t fileName[1024];
					 for (int i = 0; i < openFileDialog->FileName->Length; i++)
						 fileName[i] = openFileDialog->FileName[i];
					     fileName[openFileDialog->FileName->Length] = '\0'; //Читаем из файла

					 std::ifstream in;
					 in.open(fileName);

					 if (in.is_open()) { //Если  файл открылся
						 lines.Clear(); //Очищаем список lines
						
						 std::string str;
						 getline (in, str);
						 bool read = false;

						 while (in) { //Считываем построчно
							 if ((str.find_first_not_of(" \t\r\n") 
								 != std::string::npos) 
								 && (str[0] != '#')) { //не является ли она пустой строкой или строкой с комментариями
								
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
									 lines.Add(l); //Помещаем отрезок в конец списка
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
				 mat R,T1; //матрица преобразования и вспомогательная матрица для записи результата перемножения
				 unit(R);

				 switch(e->KeyCode){

					 case Keys::W : //вверх
						 move(0, -1, R);
						 break;

					 case Keys::S : //вниз
						 move(0, 1, R);
						 break;

					 case Keys::A : //влево
						 move(-1, 0, R);
						 break;

					 case Keys::D : //вправо
						 move(1, 0, R);
						 break;

					 case Keys::E : //поворот по часовой стрелке
						 rotate(0.05, left, top, R);
						 break;

					 case Keys::X : //увеличение изображения
						 scale(1.1,1.1, R);
						 break;

					 case Keys::Q : //поворот против часовой стрелки 
						 rotate(-0.05, left, top, R);
						 break;

					 case Keys::Z : //уменьшение изображения
						 scale(1/1.1, 1/1.1, R);
						 break;

					 case Keys::G : //быстрое смещение вниз
						 move(0, 10, R);
						 break;

					 case Keys::T : //быстрое смещение вверх
						 move(0, -10, R);
						 break;

					 case Keys::F : //быстрое смещение влево
						 move(-10, 0, R);
						 break;

					 case Keys::H : //быстрое смещение вправо
						 move(10, 0, R);
						 break;

					 case Keys::U : //зеркальное отображение горизонтальное 
						 z_goriz(R);
						 times(R, T, T1);
						set(T1, T);
						move(0, System::Windows::Forms::Form::ClientRectangle.Height - bottom + top, R);	
						 break;

					 case Keys::J : //зеркальное отображение вертикальное
						 z_vert(R);
						 times(R, T, T1);
						set(T1, T);
						move(System::Windows::Forms::Form::ClientRectangle.Width - right + left, 0, R);

						 break;

					 case Keys::Y : //поворот по часовой стрелке от центра формы
						 rotate(0.05, System::Windows::Forms::Form::ClientRectangle.Width/2, System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 break;

					 case Keys::R : //поворот против часовой стрелке от центра формы
						 rotate(-0.05, System::Windows::Forms::Form::ClientRectangle.Width/2, System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 break;

					 case Keys::C : //уменьшение изображения относительно формы
						 move(-System::Windows::Forms::Form::ClientRectangle.Width/2, 
							 -System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 times(R,T,T1);//перемножаем матрицу R на T и записываем в T1
						 set(T1,T);//T1 переписываем в T
						 scale(1/1.1, 1/1.1, R);
						 times(R,T,T1);//перемножаем матрицу R на T и записываем в T1
						 set(T1,T);//T1 переписываем в T
						 move(System::Windows::Forms::Form::ClientRectangle.Width/2, 
							 System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 break;

					 case Keys::V: //увеличение изображения относительно формы
						 move(-System::Windows::Forms::Form::ClientRectangle.Width/2, 
							 -System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 times(R,T,T1);//перемножаем матрицу R на T и записываем в T1
						 set(T1,T);//T1 переписываем в T
						 scale(1.1,1.1, R);
						 times(R,T,T1);//перемножаем матрицу R на T и записываем в T1
						 set(T1,T);//T1 переписываем в T
						 move(System::Windows::Forms::Form::ClientRectangle.Width/2, 
							 System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 break;

					 case Keys::I: //сужение по вертикали
						 move(0, -System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 times(R,T,T1);//перемножаем матрицу R на T и записываем в T1
						 set(T1,T);//T1 переписываем в T
						 scale(1,1/1.1, R);
						 times(R,T,T1);//перемножаем матрицу R на T и записываем в T1
						 set(T1,T);//T1 переписываем в T
						 move(0, System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 break;

					 case Keys::O: //увеличение по вертикали
						 move(0, -System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 times(R,T,T1);//перемножаем матрицу R на T и записываем в T1
						 set(T1,T);//T1 переписываем в T
						 scale(1, 1.1, R);
						 times(R,T,T1);//перемножаем матрицу R на T и записываем в T1
						 set(T1,T);//T1 переписываем в T
						 move(0, System::Windows::Forms::Form::ClientRectangle.Height/2, R);
						 break;

					 case Keys::K: //сжатие по горизонтали
						 move(-System::Windows::Forms::Form::ClientRectangle.Width/2, 0, R);
						 times(R,T,T1); //перемножаем матрицу R на T и записываем в T1
						 set(T1,T);//T1 переписываем в T
						 scale(1/1.1,1, R);
						 times(R,T,T1);//перемножаем матрицу R на T и записываем в T1
						 set(T1,T);//T1 переписываем в T
						 move(System::Windows::Forms::Form::ClientRectangle.Width/2, 0, R);
						 break;

					 case Keys::L: //увеличение по горизонтали
						 move(-System::Windows::Forms::Form::ClientRectangle.Width/2, 0, R);
						 times(R,T,T1);//перемножаем матрицу R на T и записываем в T1
						 set(T1,T);//T1 переписываем в T
						 scale(1.1,1, R);
						 times(R,T,T1);//перемножаем матрицу R на T и записываем в T1
						 set(T1,T);//T1 переписываем в T
						 move(System::Windows::Forms::Form::ClientRectangle.Width/2, 0, R);
						 break;

					 case Keys::P:

						drawNames = !drawNames;
						break;

					 case Keys::Escape: // выход в исходное положение изображения
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


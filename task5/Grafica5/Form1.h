#pragma once


namespace Grafica5 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Form1
	///
	/// Внимание! При изменении имени этого класса необходимо также изменить
	///          свойство имени файла ресурсов ("Resource File Name") для средства компиляции управляемого ресурса,
	///          связанного со всеми файлами с расширением .resx, от которых зависит данный класс. В противном случае,
	///          конструкторы не смогут правильно работать с локализованными
	///          ресурсами, сопоставленными данной форме.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;
			private: System::Collections::Generic::List<line> lines;
	private: float left, right, top, bottom, Wcx, Wcy, Wx, Wy, Vcx, Vcy, Vx, Vy, OldVcx, OldVcy, OldVx, OldVy;
	private: int L, K;
	private: float shiftX, shiftY;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 362);
			this->MinimumSize = System::Drawing::Size(300, 400);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Graphics^ g = e->Graphics; //задаем графическую область
				 Rectangle rect = Form::ClientRectangle; //присваиваем форме переменную
				 
				 Pen^ blackPen = gcnew Pen(Color::Black); //задаем то, чем будем рисовать
				 Pen^ redPen = gcnew Pen(Color::Black);

				 blackPen->Width = 2;
				 redPen->Width = 2;


				 g->DrawRectangle(redPen, Wcx, top, Wx, Wy);
				 //задается координатная плоскость вертикальными и горизонтальными линиями
				 
				 float stx = Wx / (K + 1); //шаг с координатой
				 float sty = Wy / (L + 1);
				 float cx1 = left, cy1, cx2, cy2; //задаем координаты в области

				 Pen^ bluePen = gcnew Pen(Color::Black);
				 bluePen->Width = 1;


				 System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 8);
				 SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);

				 //сначала зададим горизонтальные линии
				 for (int i = 0; i < K; i++) { 
					 cx1 += stx;
					 cy1 = bottom;
					 cx2 = cx1;
					 cy2 = bottom + Wy;

					 g->DrawLine(bluePen, cx1, cy1, cx2, cy2);
					 float xcor = ( (cx1 - Wcx) / Wx ) * Vx + Vcx;
					 xcor = ceil(100 * (xcor)) / 100.0;
					 g->DrawString(Convert::ToString(xcor), drawFont, drawBrush, cx2 - 10, cy1 - 20);
				 }

				 cy1 = bottom;
				 
				//затем вертикальные линии
				 for (int i = 0; i < L; i++) { 
					 cx1 = left;
					 cy1 += sty;
					 cx2 = left + Wx;
					 cy2 = cy1;

					 g->DrawLine(bluePen, cx1, cy1, cx2, cy2);
					 float ycor = Vcy - ( (cy1 - Wcy) / Wy ) * Vy;
					 ycor = ceil(100 * (ycor)) / 100.0;				 
					 g->DrawString(Convert::ToString(ycor), drawFont, drawBrush, cx1 - 30, cy1);
				 }


				 //Алгорим отрисовки заданного графика

				 point min, max; //задаем максимальные и минимальные точки от формы
				 min.x = left;
				 min.y = top;
				 max.x = rect.Width - right;
				 max.y = rect.Height - bottom;

				 bool visible1, visible2;
				 visible1, visible2 = false;

				 float 
					  y = 0, 
					  y1 = 0, 
					  y2 = 0, 
					  x = Vcx, 
					  x1, x2 = 0;

				 Pen^ blackkPen = gcnew Pen(Color::Pink); // график нашей функции
				  blackkPen->Width = 3;
				 
			      for (x1 = Wcx; x1 < Wcx + Wx; x1++){
					 point a, b;
					 a.x = x1;
					 b.x = x1 + 1;

					 if (fexists(x)) {
						 visible1 = true;
						 y = f(x);
						 y1 = Wcy - ( (y - Vcy) / Vy ) * Wy;
						 a.y = y1;
					 }

					 else visible1 = false;

					 x = ( (x1 + 1 - Wcx) / Wx ) * Vx + Vcx;

					 if (fexists(x)) 
					 {
						 visible2 = true;
						 y = f(x);
						 y2 = Wcy - ( (y - Vcy) / Vy ) * Wy;
						 b.y = y2;
					 }

					 else visible2 = false;

					x = ( (x1 + 1 - Wcx) / Wx ) * Vx + Vcx;

					 if (fexists(x)) {
						 visible2 = true;
						 y = f(x);
						 y2 = Wcy - ( (y - Vcy) / Vy ) * Wy;
						 b.y = y2;
					 }
					 else visible2 = false;

					 if (visible1 && visible2) {
						 if (clip (a, b, min, max))
							 g->DrawLine(blackkPen, a.x, a.y, b.x, b.y);
					 }

					 }

			

				 }
			 
			 
	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 float 
					 oldWx = Wx, 
					 oldWy = Wy; //старые координаты и далее соотвественно смещение на новые, при обновлении формы

				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;

				 this->Refresh();
			 }

	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {

				 Rectangle rect = Form::ClientRectangle;
				 mat R;
				 float staticc;
				 switch (e->KeyCode){


				 case Keys::W: //вверх
					 Vcy -= (Vy / Wy); 
					 break;

				 case Keys::S: //вниз
					 Vcy += (Vy / Wy);
					 break;

				 case Keys::A: //влево
					 Vcx += (Vx / Wx);
					 break;		

				 case Keys::D: //вправо
					 Vcx -= (Vx / Wx);
					 break;


				 case Keys::T :  //быстрое смещение вверх
					 Vcy -= 5 * (Vy / Wy);
					 break;

				 case Keys::G :  //быстрое смещение вниз
					 Vcy += 5 * (Vy / Wy);
					 break;

				 case Keys::F:  //быстрое смещение влево
					 Vcx += 5 * (Vx / Wx);
					 break;

				 case Keys::H :  //быстрое смещение вправо
					 Vcx -= 5 * (Vx / Wx);
					 break;



				 case Keys::I: //уменьшение относительно Oу
					 staticc = Vy; //задаем статичную переменную за ось
					 Vy /= 1.1; // уменьшаем
					 Vcy += (staticc - Vy) / 2;	
					 break;

				 case Keys::O: //масштабирование относительно Oу
					 staticc = Vy;
					 Vy *= 1.1;
					 Vcy += (staticc - Vy) / 2;	
					 break;

				 case Keys::K: //уменьшение относительно Ox
					 staticc = Vx;
					 Vx /= 1.1;
					 Vcx += (staticc - Vx) / 2;
					 break;

				 case Keys::L: //масштабирование относительно Ox
					 staticc = Vx;
					 Vx *= 1.1; 
					 Vcx += (staticc - Vx) / 2;
					 break;



				 case Keys::Q: //увеличение количества вертикальных линий
					 unit(R);
					 K++;//просто увеличение
					 break; 

				 case Keys::E: //уменьшение количества вертикальных линий
					 unit(R);
					 if (K > 1) 
						 K--; // если линий больше, чем на одну, соотв. уменьшить их
					 break; 

				 case Keys::Z: //увеличение количества горизонтальных линий 
					 unit(R);
					 L++; //просто увеличение
					 break;

				 case Keys::X: //уменьшение количества горизонтальных линий
					 unit(R);
					 if (L > 1) //если линий больше, чем на одну, соотв. уменьшить их
						 L--;
					 break;

				 case Keys::Escape:
					 Vcx = OldVcx;
					 Vcy = OldVcy;
					 Vx = OldVx;
					 Vy = OldVy;

					 K = 6;
					 L = 6;

					 shiftX = shiftY = 0;
					 break;
				 }
				 this->Refresh();
			 }

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {

				 Rectangle rect = Form::ClientRectangle;
				 left = 100;
				 right = 100;
				 top = 100;
				 bottom = 100;

				 Vcx = -5;
				 Vcy = -5;
				 Vx = 10;
				 Vy = 10;


				 Wcx = left;
				 Wcy = rect.Height - bottom;
				 Wx = rect.Width - left - right;
				 Wy = rect.Height - top - bottom;
				 OldVcx = Vcx, 
					 OldVcy = Vcy, 
					 OldVx = Vx, 
					 OldVy = Vy;

			
				 L = 6; //горизонтальные и вертикальные линии
				 K = 6;

				lines.Clear();
				 unit(T);

			 }
			 

};
}


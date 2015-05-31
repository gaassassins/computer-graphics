#pragma once


namespace My1 {

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
			this->ClientSize = System::Drawing::Size(400, 180);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {

	Graphics^ g = e->Graphics;	Rectangle rect = Form::ClientRectangle;	Rectangle smallRect;	Pen^ redPen = gcnew Pen(Color::Red);	redPen->Width = 2;	g->DrawLine( redPen, 150, 120, 330, 120);	g->DrawLine( redPen, 150, 120, 130, 110);	g->DrawLine( redPen, 130, 110, 110, 130);	g->DrawLine( redPen, 110, 130, 110, 140);	g->DrawLine( redPen, 110, 140, 120, 150);	g->DrawLine( redPen, 120, 150, 140, 150);	g->DrawLine( redPen, 140, 150, 140, 140);	g->DrawLine( redPen, 140, 140, 150, 120);	g->DrawLine( redPen, 150, 120, 160, 130);	g->DrawLine( redPen, 140, 140, 160, 140);	g->DrawLine( redPen, 140, 150, 160, 160);	g->DrawLine( redPen, 160, 160, 230, 160);	g->DrawLine( redPen, 230, 160, 260, 150);	g->DrawLine( redPen, 260, 150, 320, 150);	g->DrawLine( redPen, 320, 150, 330, 140);	g->DrawLine( redPen, 330, 140, 370, 140);	g->DrawLine( redPen, 370, 140, 370, 120);	g->DrawLine( redPen, 370, 120, 360, 110);	g->DrawLine( redPen, 360, 110, 350, 110);	g->DrawLine( redPen, 350, 110, 360, 120);	g->DrawLine( redPen, 350, 110, 330, 120);	g->DrawLine( redPen, 130, 110, 130, 90);	g->DrawLine( redPen, 130, 90, 120, 70);	g->DrawLine( redPen, 120, 70, 110, 60);	g->DrawLine( redPen, 110, 60, 100, 70);	g->DrawLine( redPen, 100, 70, 100, 80);	g->DrawLine( redPen, 100, 80, 110, 90);	g->DrawLine( redPen, 110, 90, 120, 110);	g->DrawLine( redPen, 120, 110, 120, 120);	g->DrawLine( redPen, 120, 120, 110, 110);	g->DrawLine( redPen, 110, 110, 90, 100);	g->DrawLine( redPen, 90, 100, 80, 90);	g->DrawLine( redPen, 80, 90, 80, 80);	g->DrawLine( redPen, 110, 130, 70, 130);	g->DrawLine( redPen, 70, 130, 60, 140);	g->DrawLine( redPen, 60, 140, 50, 130);	g->DrawLine( redPen, 50, 130, 50, 120);	g->DrawLine( redPen, 50, 120, 80, 70);	g->DrawLine( redPen, 80, 70, 90, 70);	g->DrawLine( redPen, 90, 70, 110, 90);	g->DrawLine( redPen, 90, 70, 110, 90);	g->DrawLine( redPen, 120, 150, 110, 160);	g->DrawLine( redPen, 110, 160, 90, 170);	g->DrawLine( redPen, 90, 170, 60, 170);	g->DrawLine( redPen, 60, 170, 70, 160);	g->DrawLine( redPen, 70, 160, 50, 160);	g->DrawLine( redPen, 50, 160, 60, 150);	g->DrawLine( redPen, 60, 150, 80, 140);	g->DrawLine( redPen, 80, 140, 90, 140);	g->DrawLine( redPen, 90, 140, 100, 130);	g->DrawLine( redPen, 140, 100, 130, 80);	g->DrawLine( redPen, 130, 80, 130, 60);	g->DrawLine( redPen, 140, 50, 140, 70);	g->DrawLine( redPen, 140, 70, 160, 90);	g->DrawLine( redPen, 150, 80, 150, 60);	g->DrawLine( redPen, 150, 60, 160, 50);	g->DrawLine( redPen, 160, 50, 180, 70);	g->DrawLine( redPen, 180, 80, 170, 70);	g->DrawLine( redPen, 160, 70, 170, 90);	g->DrawLine( redPen, 160, 50, 170, 50);	g->DrawLine( redPen, 170, 50, 190, 60);	g->DrawLine( redPen, 190, 60, 210, 50);	g->DrawLine( redPen, 210, 50, 230, 50);	g->DrawLine( redPen, 230, 50, 220, 40);	g->DrawLine( redPen, 240, 50, 230, 40);	g->DrawLine( redPen, 240, 50, 240, 40);	g->DrawLine( redPen, 250, 50, 250, 40);	g->DrawLine( redPen, 220, 30, 220, 20);	g->DrawLine( redPen, 220, 20, 230, 10);	g->DrawLine( redPen, 240, 10, 250, 30);	g->DrawLine( redPen, 250, 50, 270, 50);	g->DrawLine( redPen, 270, 50, 290, 60);	g->DrawLine( redPen, 290, 60, 300, 60);	g->DrawLine( redPen, 300, 60, 320, 40);	g->DrawLine( redPen, 320, 40, 310, 60);	g->DrawLine( redPen, 320, 40, 330, 50);	g->DrawLine( redPen, 330, 50, 330, 90);	g->DrawLine( redPen, 330, 90, 310, 70);	g->DrawLine( redPen, 310, 70, 310, 60);	g->DrawLine( redPen, 330, 80, 350, 70);	g->DrawLine( redPen, 350, 70, 360, 50);	g->DrawLine( redPen, 340, 90, 350, 80);	g->DrawLine( redPen, 350, 80, 360, 60);	g->DrawLine( redPen, 350, 90, 370, 70);	g->DrawLine( redPen, 360, 90, 370, 80);	g->DrawLine( redPen, 370, 90, 390, 100);	g->DrawLine( redPen, 390, 110, 380, 100);	g->DrawLine( redPen, 380, 100, 370, 100);	g->DrawLine( redPen, 370, 100, 380, 120);	g->DrawLine( redPen, 230, 55, 220, 60);	g->DrawLine( redPen, 240, 55, 250, 60);	g->DrawLine( redPen, 230, 70, 235, 65);	g->DrawLine( redPen, 235, 65, 240, 70);	g->DrawLine( redPen, 240, 70, 235, 75);	g->DrawLine( redPen, 235, 75, 230, 70);	g->DrawLine( redPen, 240, 70, 245, 65);	g->DrawLine( redPen, 245, 65, 250, 70);	g->DrawLine( redPen, 250, 70, 245, 75);	g->DrawLine( redPen, 245, 75, 240, 70);	g->DrawLine( redPen, 230, 80, 250, 80);	g->DrawLine( redPen, 250, 80, 250, 90);	g->DrawLine( redPen, 250, 90, 230, 90);	g->DrawLine( redPen, 230, 90, 230, 80);	g->DrawLine( redPen, 240, 90, 240, 100);	g->DrawLine( redPen, 240, 100, 230, 110);	g->DrawLine( redPen, 230, 110, 220, 115);	g->DrawLine( redPen, 220, 115, 200, 110);	g->DrawLine( redPen, 200, 110, 190, 100);	g->DrawLine( redPen, 190, 100, 190, 90);	g->DrawLine( redPen, 190, 90, 180, 90);	g->DrawLine( redPen, 190, 90, 200, 90);	g->DrawLine( redPen, 240, 100, 250, 110);	g->DrawLine( redPen, 250, 110, 260, 110);	g->DrawLine( redPen, 260, 110, 280, 100);	g->DrawLine( redPen, 280, 100, 290, 90);	g->DrawLine( redPen, 290, 90, 300, 90);	g->DrawLine( redPen, 290, 90, 280, 90);		
			 }
	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 this->Refresh();
			 }
	};
}


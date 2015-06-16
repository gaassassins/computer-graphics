// Grafica5.cpp: главный файл проекта.

#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <math.h>
#include "function.h"
#include "clip.h"
#include "Transf.h"
#include "Form1.h"


using namespace Grafica5;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Включение визуальных эффектов Windows XP до создания каких-либо элементов управления
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Создание главного окна и его запуск
	Application::Run(gcnew Form1());
	return 0;
}

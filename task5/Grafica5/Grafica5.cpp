// Grafica5.cpp: ������� ���� �������.

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
	// ��������� ���������� �������� Windows XP �� �������� �����-���� ��������� ����������
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// �������� �������� ���� � ��� ������
	Application::Run(gcnew Form1());
	return 0;
}

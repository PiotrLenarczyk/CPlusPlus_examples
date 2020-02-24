// fileGenerator.cpp : main project file.
#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
using namespace System;
using namespace std;
unsigned long long data8B[ 1 * 1024 * 1024 / 8 ];
#include "Form1.h"

using namespace fileGenerator;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Form1());
	return 0;
}

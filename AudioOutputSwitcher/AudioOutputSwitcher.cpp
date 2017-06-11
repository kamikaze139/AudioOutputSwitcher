// EndPointController.cpp : Defines the entry point for the console application.
//

#pragma comment(lib, "ole32.lib")

#include "stdafx.h"
#include "Mmdeviceapi.h"
#include "PolicyConfig.h"
#include "Propidl.h"
#include "Form1.h"

using namespace AudioOutputSwitcher;



[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	//  run it
	Application::Run(gcnew Form1());

	return 0;
}
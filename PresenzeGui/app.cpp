#include "app.h"
#include "mymainframe.h"

wxIMPLEMENT_APP(MyApp);

MyApp::MyApp()
{
}

MyApp::~MyApp()
{
}

bool MyApp::OnInit()
{
	auto frame = new MyMainFrame(_T("Gestione Personale"), wxPoint(50, 50));
	frame->Show();
	SetTopWindow(frame);

	return true;
}
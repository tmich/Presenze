#pragma once
#include <wx/wxprec.h>

//class PresenzeApp : public wxApp
//{
//public:
//	PresenzeApp();
//	~PresenzeApp();
//
//	bool OnInit() override;
//};

class MyApp : public wxApp
{
public:
	MyApp();
	~MyApp();

	bool OnInit() override;
private:

};

wxDECLARE_APP(MyApp);
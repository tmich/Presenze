#pragma once
#include <wx\wx.h>
#include <wx/artprov.h>
#include "viewdip.h"

class MyMainFrame : public wxFrame
{
public:
	MyMainFrame(const wxString& title, const wxPoint& pos);
	~MyMainFrame();

	DECLARE_EVENT_TABLE()
private:
	wxMenu * creaMenuFile();
	wxMenu * creaMenuGestionePersonale();
	wxMenu * creaMenuTurni();
	wxMenu * creaMenuHelp();
	
	wxBoxSizer * topSizer;
	ViewDip * viewDip;

	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnNuovoDip(wxCommandEvent& event);
	void OnTurni(wxCommandEvent& event);
};
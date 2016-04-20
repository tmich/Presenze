#include "stdafx.h"
#include "mymainframe.h"

MyMainFrame::MyMainFrame(const wxString & title, const wxPoint & pos, const wxSize & size)
	: wxFrame(nullptr, -1, title, pos, size)
{
	// creazione menu
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(creaMenuFile(), "&File");
	menuBar->Append(creaMenuGestionePersonale(), "&Personale");
	menuBar->Append(creaMenuTurni(), "&Turni");
	menuBar->Append(creaMenuHelp(), "&?");
	SetMenuBar(menuBar);
	
	// viste
	viewDip = new ViewDip{ this, wxID_ANY };
	//viewDip->Hide();
	//wxPanel * panel = new wxPanel{ this, -1 };
	// sizer
	//topSizer = new wxBoxSizer{ wxVERTICAL };
	//topSizer->Add(viewDip);
	////topSizer->SetSizeHints(this);
	//SetSizer(topSizer);
	
	// status bar
	CreateStatusBar();
	SetStatusText("Gestione Personale v0.1");
}

MyMainFrame::~MyMainFrame()
{
}

wxMenu * MyMainFrame::creaMenuFile()
{
	wxMenu *menuFile = new wxMenu;
	wxMenuItem *mnuItEsci = new wxMenuItem(nullptr, wxID_EXIT, "&Esci", "Chiudi il programma");
	mnuItEsci->SetBitmap(wxBitmap(wxArtProvider::GetBitmap(wxART_QUIT, wxART_MENU, wxSize(16, 15))));
	menuFile->Append(mnuItEsci);

	return menuFile;
}

wxMenu * MyMainFrame::creaMenuGestionePersonale()
{
	wxMenu *menu = new wxMenu;
	wxMenuItem * mnuItVDip = new wxMenuItem{ nullptr,wxID_ANY,"&Lista Dipendenti", "Visualizza la lista dei dipendenti" };
	mnuItVDip->SetBitmap(wxBitmap(wxArtProvider::GetBitmap(wxART_REPORT_VIEW, wxART_MENU, wxSize(16, 15))));
	menu->Append(mnuItVDip);

	wxMenuItem * mnuItNDip = new wxMenuItem(nullptr, wxID_NEW, "&Nuovo dipendente", "Aggiungi un nuovo dipendente");
	mnuItNDip->SetBitmap(wxBitmap(wxArtProvider::GetBitmap(wxART_NEW, wxART_MENU, wxSize(16, 15))));
	menu->Append(mnuItNDip);

	return menu;
}

wxMenu * MyMainFrame::creaMenuTurni()
{
	wxMenu * menu = new wxMenu;
	wxMenuItem * mnuItTabTurniSett = new wxMenuItem{ nullptr, wxID_ANY, _T("Tabella settimanale"), "Visualizza la tabella settimanale dei turni" };
	mnuItTabTurniSett->SetBitmap(wxArtProvider::GetBitmap(wxART_LIST_VIEW, wxART_MENU, wxSize(16, 15)));
	menu->Append(mnuItTabTurniSett);

	return menu;
}

wxMenu * MyMainFrame::creaMenuHelp()
{
	wxMenu *menu = new wxMenu;
	wxMenuItem * mnuItAbout = new wxMenuItem(nullptr, wxID_ABOUT, "&Informazioni...", "Informazioni di versione");
	menu->Append(mnuItAbout);

	return menu;
}

void MyMainFrame::OnQuit(wxCommandEvent & event)
{
	Close(true);
}

void MyMainFrame::OnAbout(wxCommandEvent & event)
{
	wxMessageBox("Gestione Personale v0.1",
		"Informazioni", wxOK | wxICON_INFORMATION, this);
}

void MyMainFrame::OnNuovoDip(wxCommandEvent & event)
{
	viewDip->Show();
}

BEGIN_EVENT_TABLE(MyMainFrame, wxFrame)
	EVT_MENU(wxID_EXIT, MyMainFrame::OnQuit)
	EVT_MENU(wxID_ABOUT, MyMainFrame::OnAbout)
	EVT_MENU(wxID_NEW, MyMainFrame::OnNuovoDip)
END_EVENT_TABLE()
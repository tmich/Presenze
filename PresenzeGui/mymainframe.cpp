#include "stdafx.h"
#include "mymainframe.h"

MyMainFrame::MyMainFrame(const wxString & title, const wxPoint & pos)
	: wxFrame(nullptr, -1, title, pos)
{
	// dimensioni
	SetMinClientSize(wxSize(500, 500));
	Maximize();

	// creazione menu
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(creaMenuFile(), "&File");
	menuBar->Append(creaMenuGestionePersonale(), "&Personale");
	menuBar->Append(creaMenuTurni(), "&Turni");
	menuBar->Append(creaMenuHelp(), "&?");
	SetMenuBar(menuBar);
	
	//sizer
	topSizer = new wxBoxSizer{ wxVERTICAL };

	// viste
	viewDip = new ViewDip{ this, wxID_ANY };
	pnlTurni = new PanelTurni{ this, wxID_ANY };
	viewDip->Show(false);
	pnlTurni->Show(false);
	topSizer->Add(viewDip, 1, wxEXPAND);
	topSizer->Add(pnlTurni, 1, wxEXPAND);
	
	// status bar
	CreateStatusBar();
	SetStatusText("Gestione Personale v0.1");
}

enum 
{
	ID_NUOVODIP,
	ID_LSTTURNI,
	ID_PRNTURNI
};

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

	wxMenuItem * mnuItNDip = new wxMenuItem(nullptr, ID_NUOVODIP, "&Nuovo dipendente", "Aggiungi un nuovo dipendente");
	mnuItNDip->SetBitmap(wxBitmap(wxArtProvider::GetBitmap(wxART_NEW, wxART_MENU, wxSize(16, 15))));
	menu->Append(mnuItNDip);

	return menu;
}

wxMenu * MyMainFrame::creaMenuTurni()
{
	wxMenu * menu = new wxMenu;
	wxMenuItem * mnuItTabTurniSett = new wxMenuItem{ nullptr, ID_LSTTURNI, _T("Tabella settimanale"), "Visualizza la tabella settimanale dei turni" };
	mnuItTabTurniSett->SetBitmap(wxArtProvider::GetBitmap(wxART_LIST_VIEW, wxART_MENU, wxSize(16, 15)));
	menu->Append(mnuItTabTurniSett);

	wxMenuItem * mnuItTabTurniPrnt = new wxMenuItem{ nullptr, ID_PRNTURNI, _T("Stampa settimana"), "Stampa la tabella settimanale dei turni" };
	mnuItTabTurniPrnt->SetBitmap(wxArtProvider::GetBitmap(wxART_PRINT, wxART_MENU, wxSize(16, 15)));
	menu->Append(mnuItTabTurniPrnt);

	return menu;
}

wxMenu * MyMainFrame::creaMenuHelp()
{
	wxMenu *menu = new wxMenu;
	wxMenuItem * mnuItAbout = new wxMenuItem(nullptr, wxID_ABOUT, "&Informazioni...", "Informazioni di versione");
	menu->Append(mnuItAbout);

	return menu;
}

void MyMainFrame::showPanel(wxPanel * panel)
{
	Freeze();
	panel->SetClientSize(GetClientSize());
	if (currentPanel != nullptr)
	{
		currentPanel->Hide();
	}
	panel->Show();
	Thaw();
	currentPanel = panel;
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
	showPanel(viewDip);
}

void MyMainFrame::OnTurni(wxCommandEvent & event)
{
	showPanel(pnlTurni);
}

BEGIN_EVENT_TABLE(MyMainFrame, wxFrame)
	EVT_MENU(wxID_EXIT, MyMainFrame::OnQuit)
	EVT_MENU(wxID_ABOUT, MyMainFrame::OnAbout)
	EVT_MENU(ID_NUOVODIP, MyMainFrame::OnNuovoDip)
	EVT_MENU(ID_LSTTURNI, MyMainFrame::OnTurni)
END_EVENT_TABLE()
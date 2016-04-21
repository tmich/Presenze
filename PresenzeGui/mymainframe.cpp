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
	/*viewDip = new ViewDip{ this, wxID_ANY };
	topSizer->Add(viewDip, 1, wxEXPAND);
	viewDip->Show(false);*/
	
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
	wxMenuItem * mnuItTabTurniSett = new wxMenuItem{ nullptr, wxID_FILE1, _T("Tabella settimanale"), "Visualizza la tabella settimanale dei turni" };
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
	//viewDip = new ViewDip{ nullptr, wxID_ANY };
	if (topSizer->GetChildren().size() > 0)
	{
		topSizer->Remove(0);
	}
	viewDip = new ViewDip{ this, wxID_ANY };
	topSizer->Add(viewDip, 1, wxEXPAND);
	viewDip->SetClientSize(GetClientSize());
	Refresh();
	//Update();
}

void MyMainFrame::OnTurni(wxCommandEvent & event)
{
	auto pnl = new wxPanel{ this,-1 };
	pnl->SetBackgroundColour(wxColour(*wxGREEN));
	if (topSizer->GetChildren().size() > 0)
	{
		topSizer->Remove(0);
	}
	topSizer->Add(pnl, 1, wxEXPAND);
	pnl->SetClientSize(GetClientSize());
	Refresh();
}

BEGIN_EVENT_TABLE(MyMainFrame, wxFrame)
	EVT_MENU(wxID_EXIT, MyMainFrame::OnQuit)
	EVT_MENU(wxID_ABOUT, MyMainFrame::OnAbout)
	EVT_MENU(wxID_NEW, MyMainFrame::OnNuovoDip)
	EVT_MENU(wxID_FILE1, MyMainFrame::OnTurni)
END_EVENT_TABLE()
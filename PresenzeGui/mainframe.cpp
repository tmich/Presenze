#include "mainframe.h"
#include "dipendentedlg.h"
#include "listadipendentidlg.h"

MainFrame::MainFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(900, 700), wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER)
{
	// Ribbon
	ribbonBar = new wxRibbonBar(this, -1, wxDefaultPosition, wxDefaultSize, wxRIBBON_BAR_FLOW_HORIZONTAL
		| wxRIBBON_BAR_SHOW_PAGE_LABELS
		| wxRIBBON_BAR_SHOW_PANEL_EXT_BUTTONS
		| wxRIBBON_BAR_SHOW_TOGGLE_BUTTON
	);

	homeRibbonPage = new wxRibbonPage(ribbonBar, wxID_ANY, wxT("Turni"), wxNullBitmap);
	editRibbonPage = new wxRibbonPage(ribbonBar, wxID_ANY, wxT("Dipendenti"), wxNullBitmap);

	homeRibbonPanel = new wxRibbonPanel(homeRibbonPage, wxID_ANY, wxT("Nuovo"), wxNullBitmap,
		wxDefaultPosition, wxDefaultSize,
		wxRIBBON_PANEL_NO_AUTO_MINIMISE);
	
	/*itemRibbonPanel = new wxRibbonPanel(homeRibbonPage, wxID_ANY, wxT("Data Item"),
		wxNullBitmap, wxDefaultPosition, wxDefaultSize,
		wxRIBBON_PANEL_NO_AUTO_MINIMISE);*/

	homeRibbonButtonBar = new wxRibbonButtonBar(homeRibbonPanel);
	//itemRibbonButtonBar = new wxRibbonButtonBar(itemRibbonPanel);

	homeRibbonButtonBar->AddButton(wxID_ANY, wxT("Crea"),
		wxArtProvider::GetBitmap(wxART_NEW, wxART_TOOLBAR, wxSize(16, 15)));

	homeRibbonButtonBar->Bind(wxEVT_BUTTON, [=](wxCommandEvent&) {
		DipendenteDlg *dlg = new DipendenteDlg(this, _T("Nuovo dipendente"));
		dlg->ShowModal();
	});

	//itemRibbonButtonBar->AddButton(wxID_ANY, wxT("Daftar Guru"),
	//	wxArtProvider::GetBitmap(wxART_QUESTION, wxART_TOOLBAR, wxSize(16, 15)));
	//itemRibbonButtonBar->AddButton(wxID_ANY, wxT("Tambah Guru"),
	//	wxArtProvider::GetBitmap(wxART_QUESTION, wxART_TOOLBAR, wxSize(16, 15)));
	//itemRibbonButtonBar->AddButton(wxID_ANY, wxT("Daftar Siswa"),
	//	wxArtProvider::GetBitmap(wxART_QUESTION, wxART_TOOLBAR, wxSize(16, 15)));
	//itemRibbonButtonBar->AddButton(wxID_ANY, wxT("Tambah Siswa"),
	//	wxArtProvider::GetBitmap(wxART_QUESTION, wxART_TOOLBAR, wxSize(16, 15)));

	ribbonBar->AddPageHighlight(ribbonBar->GetPageCount() - 1);
	ribbonBar->Realize();

	// set style msw provider
	ribbonBar->DismissExpandedPanel();
	ribbonBar->SetArtProvider(new wxRibbonMSWArtProvider);

	// aui notebook
	wxSize client_size = GetClientSize();

	/*auiNotebook = new wxAuiNotebook(this, wxID_ANY,
		wxPoint(client_size.x, client_size.y),
		wxSize(430, 200),
		wxAUI_NB_CLOSE_BUTTON | wxAUI_NB_SCROLL_BUTTONS);
	auiNotebook->Freeze();
	wxBitmap page_bmp = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16));

	auiNotebook->AddPage(new wxTextCtrl(auiNotebook, wxID_ANY, wxT("Some text"),
		wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxNO_BORDER),
		wxT("Home"), false, page_bmp);
	auiNotebook->AddPage(new wxTextCtrl(auiNotebook, wxID_ANY, wxT("Some text"),
		wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxNO_BORDER),
		wxT("Item 1"), false, page_bmp);

	auiNotebook->SetPageToolTip(0, "Menu utama sistem informasi akademik");
	auiNotebook->Thaw();*/

	//grid
	grid = new wxGrid(this, wxID_ANY,
		wxPoint(client_size.x, client_size.y),
		wxSize(430, 200),
		wxAUI_NB_CLOSE_BUTTON | wxAUI_NB_SCROLL_BUTTONS);

	size_t ROWS = 10;
	size_t COLS = 10;

	grid->CreateGrid(ROWS, COLS);
	for (size_t r = 0; r < ROWS; r++)
	{
		for (size_t c = 0; c < COLS; c++)
		{
			grid->SetReadOnly(r, c);
		}
	}

	wxButton *btnld = new wxButton(this, wxID_ANY, _T("Lista dipendenti"));
	btnld->Bind(wxEVT_BUTTON, [=](wxCommandEvent& evt) {
		auto ldp = new ListaDipendentiDlg(this);
		ldp->ShowModal();
	});

	// set layout
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(ribbonBar, 0, wxEXPAND);
	//sizer->Add(auiNotebook, 1, wxEXPAND);
	sizer->Add(grid, 1, wxEXPAND);
	sizer->Add(btnld);
	SetSizer(sizer);

	Centre();
}

MainFrame::~MainFrame() {}
#include "dipendentedlg.h"

DipendenteDlg::DipendenteDlg(wxWindow * parent, const wxString title)
	: wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300), wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER)
{
	lblNome = new wxStaticText(this, wxID_ANY, _T("Nome"));
	txtNome = new wxTextCtrl(this, wxID_ANY);
	lblCognome = new wxStaticText(this, wxID_ANY, _T("Cognome"));
	txtCognome = new wxTextCtrl(this, wxID_ANY);
	
	// set layout
	wxGridSizer* sizer = new wxGridSizer(3, 2, 1, 1);
	sizer->Add(lblNome);
	sizer->Add(txtNome, wxEXPAND);
	sizer->Add(lblCognome);
	sizer->Add(txtCognome, wxEXPAND);

	SetSizer(sizer);

	Centre();
}

DipendenteDlg::~DipendenteDlg()
{
}

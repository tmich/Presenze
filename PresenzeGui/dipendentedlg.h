#pragma once
#include <wx\wx.h>

class DipendenteDlg : public wxDialog
{
public:
	DipendenteDlg(wxWindow *parent, const wxString title);
	~DipendenteDlg();
private:
	wxStaticText *lblNome;
	wxStaticText *lblCognome;
	wxTextCtrl *txtNome;
	wxTextCtrl *txtCognome;
};
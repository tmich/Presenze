#pragma once
#include <wx\wx.h>
#include <wx/artprov.h>
#include "dipendente.h"

class ViewDip : public wxPanel
{
public:
	ViewDip(wxWindow * parent, int id);
	~ViewDip();

	void OnSalva(wxCommandEvent& evt);
	void OnAnnulla(wxCommandEvent& evt);
protected:
	wxButton   * btnSave;
	wxButton   * btnCancel;

	wxString   * strNome;
	wxString   * strCognome;
	wxString   * strDataNascita;
	wxTextCtrl * txtNome;
	wxTextCtrl * txtCognome;
	wxTextCtrl * txtDataNascita;
};
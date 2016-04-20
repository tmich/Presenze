#include "viewdip.h"
#include <string>
#include "dipendenterepository.h"

ViewDip::ViewDip(wxWindow * parent, int id)
	: wxPanel(parent, id)
{
	btnSave = new wxButton{ this,-1,_T("Salva") };
	btnSave->Bind(wxEVT_BUTTON, &ViewDip::OnSalva, this);
	btnCancel = new wxButton{ this,-1,_T("Annulla") };
	btnCancel->Bind(wxEVT_BUTTON, &ViewDip::OnAnnulla, this);
	strNome = new wxString();
	strCognome = new wxString();
	txtNome = new wxTextCtrl{ this, -1, wxEmptyString, wxDefaultPosition, wxSize(100, 20), 0L, wxTextValidator(wxFILTER_EMPTY, strNome) };
	txtCognome = new wxTextCtrl{ this, -1, wxEmptyString, wxDefaultPosition, wxSize(100, 20), 0L, wxTextValidator(wxFILTER_EMPTY, strCognome) };
	txtDataNascita = new wxTextCtrl{ this, -1, wxEmptyString, wxDefaultPosition, wxSize(100,20) };

	auto topSizer = new wxBoxSizer{ wxVERTICAL };
	
	auto row1 = new wxBoxSizer{ wxHORIZONTAL };
	topSizer->Add(new wxStaticText{ this,-1,_T("NUOVO DIPENDENTE") }, 0, wxALL, 5);
	row1->Add(new wxStaticText{ this, -1, _T("Nome"), wxDefaultPosition, wxSize(100, 20) });
	row1->Add(txtNome);
	topSizer->Add(row1, 0, wxALL, 5);
	auto row2 = new wxBoxSizer{ wxHORIZONTAL };
	row2->Add(new wxStaticText{ this,-1,_T("Cognome"), wxDefaultPosition, wxSize(100, 20) });
	row2->Add(txtCognome);
	topSizer->Add(row2, 0, wxALL, 5);
	auto row3 = new wxBoxSizer{ wxHORIZONTAL };
	row3->Add(new wxStaticText{ this,-1,_T("Nato/a"), wxDefaultPosition, wxSize(100, 20) });
	row3->Add(txtDataNascita);
	topSizer->Add(row3, 0, wxALL, 5);
	auto rowBtn = new wxBoxSizer{ wxHORIZONTAL };
	rowBtn->Add(btnSave);
	rowBtn->Add(btnCancel);

	topSizer->Add(rowBtn, 0, wxALL, 5);
	
	SetSizer(topSizer);
}

ViewDip::~ViewDip()
{
}

void ViewDip::OnSalva(wxCommandEvent & evt)
{
	/*if (txtNome->GetValue().Trim().IsEmpty())
	{
		wxMessageBox("Inserire il nome", "Attenzione", wxICON_EXCLAMATION, this);
		return;
	}

	if (txtCognome->GetValue().Trim().IsEmpty())
	{
		wxMessageBox("Inserire il cognome", "Attenzione", wxICON_EXCLAMATION, this);
		return;
	}

	if (txtDataNascita->GetValue().Trim().IsEmpty())
	{
		wxMessageBox("Inserire la data di nascita", "Attenzione", wxICON_EXCLAMATION, this);
		return;
	}

	std::string nome{ txtNome->GetValue().Trim().ToStdString() };
	std::string cognome{ txtCognome->GetValue().Trim().ToStdString() };
	std::string dnascita{ txtDataNascita->GetValue().Trim().ToStdString() };*/

	if (Validate() && TransferDataFromWindow())
	{
		Dipendente dip{ strNome->ToStdString(), strCognome->ToStdString() };
		dip.set_datanascita(date::datetime{ 1,4,1980 });
		DipendenteRepository repo;
		repo.add(dip);

		if (dip.get_id() > 0)
		{
			wxMessageBox("Salvato!", "Dipendente", wxICON_INFORMATION, this);
		}
		else
		{
			wxMessageBox("Si è verificato un errore", "Erroe", wxICON_ERROR, this);
		}
	}
}

void ViewDip::OnAnnulla(wxCommandEvent & evt)
{
	txtNome->Clear();
	txtCognome->Clear();
}

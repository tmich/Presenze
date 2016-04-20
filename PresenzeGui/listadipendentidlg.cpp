#include "listadipendentidlg.h"
#include "dipendenterepository.h"

ListaDipendentiDlg::ListaDipendentiDlg(wxWindow * parent)
	: wxDialog(parent, wxID_ANY, _T("Dipendenti"))
{
	//prova
	DipendenteRepository repo;
	repo.add(Dipendente("Gino", "Bianchi"));
	repo.add(Dipendente("Mario", "Rossi"));
	repo.add(Dipendente("Aristotele", "Onassis"));


	lstDip = new wxListBox(this, wxID_ANY);

	for (auto& dip : repo.all())
	{
		lstDip->AppendString(dip.get_cognome() + " " + dip.get_nome());
	}

	wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(new wxStaticText(this, wxID_ANY, _T("Lista dipendenti")));
	sizer->Add(lstDip, wxEXPAND);
	SetSizerAndFit(sizer);

	Centre();
}

ListaDipendentiDlg::~ListaDipendentiDlg()
{
}

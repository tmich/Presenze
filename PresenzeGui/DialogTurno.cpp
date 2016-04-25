#include "stdafx.h"
#include "DialogTurno.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

DialogTurno::DialogTurno(wxWindow * parent, const Dipendente& dip, const wxDateTime& dataTurno)
	: wxDialog(parent, wxID_ANY, "Turno", wxDefaultPosition, wxSize(300, 300)), dip_{dip}, data_{dataTurno}
{
	sizer = new wxBoxSizer(wxVERTICAL);
	btnOk = new wxButton(this, wxID_OK, "&Ok");
	btnCancel = new wxButton(this, wxID_CANCEL, "&Annulla");
	sizer->Add(new wxStaticText(this, wxID_ANY, dip.get_nomecompleto()));
	sizer->Add(new wxStaticText(this, wxID_ANY, dataTurno.Format("%d-%m-%Y")));
	
	cmbTipo = new wxChoice(this, wxID_ANY);
	cmbTipo->Append("TURNO");
	cmbTipo->Append("ASSENZA");
	cmbTipo->SetSelection(0);
	cmbTipo->Bind(wxEVT_CHOICE, [=](wxCommandEvent& evt) {
		if (evt.GetSelection() == 0)
		{
			cmbCausaliAssenza->Hide();
			cmbReparti->Show();
		}
		else
		{
			cmbCausaliAssenza->Show();
			cmbReparti->Hide();
		}
	});
	sizer->Add(cmbTipo);

	cmbCausaliAssenza = new wxChoice(this, wxID_ANY);
	// TODO: repository causali
	cmbCausaliAssenza->Append("Malattia");
	cmbCausaliAssenza->Append("L.104");
	cmbCausaliAssenza->Append("Maternita'");
	cmbCausaliAssenza->SetSelection(0);
	sizer->Add(cmbCausaliAssenza);

	cmbReparti = new wxChoice(this, wxID_ANY);
	cmbReparti->Append("Cassa");
	cmbReparti->Append("Banco");
	cmbReparti->Append("Sala");
	cmbReparti->SetSelection(0);
	sizer->Add(cmbReparti);

	cmbHourB = new wxComboBox(this, wxID_ANY);
	cmbMinsB = new wxComboBox(this, wxID_ANY);
	cmbHourE = new wxComboBox(this, wxID_ANY);
	cmbMinsE = new wxComboBox(this, wxID_ANY);

	for (size_t i = 0; i < 24; i++)
	{
		std::ostringstream ss;
		ss << std::setw(2) << std::setfill('0') << i;
		cmbHourB->Append(ss.str());
		cmbHourE->Append(ss.str());
	}

	for (size_t i = 0; i < 59; i++)
	{
		std::ostringstream ss;
		ss << std::setw(2) << std::setfill('0') << i;
		cmbMinsB->Append(ss.str());
		cmbMinsE->Append(ss.str());
	}
	
	auto bTimeSizer = new wxBoxSizer(wxHORIZONTAL);
	bTimeSizer->Add(new wxStaticText(this, wxID_ANY, "Inizio:"));
	bTimeSizer->Add(cmbHourB);
	bTimeSizer->Add(cmbMinsB);
	sizer->Add(bTimeSizer);

	auto eTimeSizer = new wxBoxSizer(wxHORIZONTAL);
	eTimeSizer->Add(new wxStaticText(this, wxID_ANY, "Fine:"));
	eTimeSizer->Add(cmbHourE);
	eTimeSizer->Add(cmbMinsE);
	sizer->Add(eTimeSizer);
	
	auto btnSizer = new wxBoxSizer(wxHORIZONTAL);
	btnSizer->Add(btnOk);
	btnSizer->Add(btnCancel);
	sizer->Add(btnSizer);
	
	Bind(wxEVT_BUTTON, &DialogTurno::OnOk, this, wxID_OK);

	cmbCausaliAssenza->Hide();
	SetSizer(sizer);
	Centre();
}

DialogTurno::~DialogTurno()
{
}

wxDateTime DialogTurno::getDataInizio() const
{
	int hb = atoi(cmbHourB->GetValue());
	int mb = atoi(cmbMinsB->GetValue());
	return wxDateTime(data_.GetDay(), data_.GetMonth(), data_.GetYear(), hb, mb, 0);
}

wxDateTime DialogTurno::getDataFine() const
{
	int he = atoi(cmbHourE->GetValue());
	int me = atoi(cmbMinsE->GetValue());
	return wxDateTime(data_.GetDay(), data_.GetMonth(), data_.GetYear(), he, me, 0);
}

void DialogTurno::OnCancel(wxCommandEvent & pEvent)
{
	EndModal(wxID_CANCEL);
	Destroy();
}

void DialogTurno::OnOk(wxCommandEvent & pEvent)
{
	EndModal(wxID_OK);
	Destroy();
}

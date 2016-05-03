#pragma once
#include <wx\wx.h>
#include "dipendente.h"
#include "pianificazione.h"

enum tipoturno_t
{
	TURNO,
	ASSENZA
};

class DialogTurno : public wxDialog
{
public:
	DialogTurno(wxWindow * parent, const Dipendente&, const wxDateTime&);
	DialogTurno(wxWindow * parent, const Pianificazione& pianificazione);
	virtual ~DialogTurno();

	tipoturno_t getTipo() const { return (cmbTipo->GetSelection() == 0 ? TURNO : ASSENZA); }
	wxDateTime getDataInizio() const;
	wxDateTime getDataFine() const;
	wxString getMotivazione() const { return (getTipo() == TURNO ? cmbReparti->GetStringSelection() : cmbCausaliAssenza->GetStringSelection()); }

	void OnCancel(wxCommandEvent& pEvent);
	void OnOk(wxCommandEvent& pEvent);
protected:
	DialogTurno(wxWindow * parent);
private:
	wxDateTime data_;
	Dipendente dip_;
	wxStaticText * lblNomDip;
	wxStaticText * lblData;
	wxButton * btnOk;
	wxButton * btnCancel;
	wxSizer * sizer;
	wxChoice * cmbCausaliAssenza;
	wxChoice * cmbReparti;
	wxChoice * cmbTipo;
	wxComboBox * cmbHourB;
	wxComboBox * cmbMinsB;
	wxComboBox * cmbHourE;
	wxComboBox * cmbMinsE;
};
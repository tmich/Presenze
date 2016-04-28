#pragma once
#include <wx/wx.h>
#include <wx/artprov.h>
#include <wx/grid.h>
#include <wx/calctrl.h>
#include <wx/datectrl.h>
#include <vector>
#include "dipendente.h"
#include "serviceturni.h"

using namespace std;

class PanelTurni : public wxPanel
{
public:
	PanelTurni(wxWindow * parent, int id = -1, wxSize size = wxDefaultSize);
	~PanelTurni();

	void OnCellSelected(wxGridEvent& evt);
	void VisualizzaPianificazione(int row, int col, const Presenza& pn);
	void VisualizzaPianificazione(int row, int col, const Assenza& pn);
private:
	size_t COLS = 7;
	void aggiornaGriglia(const wxDateTime& dt);
	wxCalendarCtrl * calendar;
	wxDatePickerCtrl * datepicker;
	wxGrid * grid;
	wxSizer * sizer;
	vector<Dipendente> vdipendenti;
	vector<wxDateTime> vdate;
};
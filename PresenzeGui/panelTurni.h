#pragma once
#include <wx/wx.h>
#include <wx/artprov.h>
#include <wx/grid.h>
#include <wx/calctrl.h>
#include <vector>
#include "dipendente.h"

using namespace std;

class PanelTurni : public wxPanel
{
public:
	PanelTurni(wxWindow * parent, int id = -1, wxSize size = wxDefaultSize);
	~PanelTurni();
private:
	size_t COLS = 7;
	void aggiornaGriglia(const wxDateTime& dt);
	wxCalendarCtrl * calendar;
	wxGrid * grid;
	wxSizer * sizer;
	vector<Dipendente> vdipendenti;
	vector<wxDateTime> vdate;
};
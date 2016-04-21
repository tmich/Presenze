#include "panelTurni.h"

PanelTurni::PanelTurni(wxWindow * parent, int id, wxSize size)
	:wxPanel{parent, id, wxDefaultPosition, size}
{
	vdipendenti = {
		Dipendente("Mario", "Rossi"),
		Dipendente("Carlo", "Bianchi"),
		Dipendente("Gino", "Verdi"),
		Dipendente("Eschilo", "Auritosfrate"),
		Dipendente("Teomondo", "Scrofalo")
	};

	sizer = new wxBoxSizer{ wxVERTICAL };
	calendar = new wxCalendarCtrl{ this, -1 };
	grid = new wxGrid{ this,-1 };
	grid->CreateGrid(vdipendenti.size(), COLS);
	
	grid->Bind(wxEVT_GRID_CELL_LEFT_DCLICK, [=](wxGridEvent& evt) {
		int row = evt.GetRow();
		int col = evt.GetCol();
		Dipendente d{ vdipendenti[row] };
		wxMessageBox(d.get_nomecompleto() + " per il giorno " + vdate[col].Format("%d-%m-%Y"), "Turno", wxICON_INFORMATION);
	});

	calendar->SetExtraStyle(wxCAL_SEQUENTIAL_MONTH_SELECTION);
	calendar->Bind(wxEVT_CALENDAR_SEL_CHANGED, [=](wxCalendarEvent& event) {
		aggiornaGriglia(event.GetDate());
	});
	aggiornaGriglia(calendar->GetDate());

	sizer->Add(calendar, 0, 0, 5);
	sizer->Add(grid, 0, wxEXPAND, 5);
	SetSizer(sizer);
}

PanelTurni::~PanelTurni()
{
}

void PanelTurni::aggiornaGriglia(const wxDateTime& dt)
{
	auto dt_{ dt };

	// settimanale
	vdate.clear();
	for (size_t x = 0; x < COLS; x++)
	{
		vdate.push_back(dt_);
		dt_ = dt_.Add(wxDateSpan{ 0,0,0,1 });	// aggiungo un giorno
	}

	// colonne
	for (size_t c = 0; c < vdate.size(); c++)
	{
		grid->SetColSize(c, 120);
		grid->SetColLabelValue(c, vdate[c].Format("%d-%m", wxDateTime::Local));
	}

	// righe
	for (size_t r = 0; r < vdipendenti.size(); r++)
	{
		grid->SetRowSize(r, 60);
		grid->SetRowLabelValue(r, vdipendenti[r].get_nomecompleto());

		// celle
		for (size_t c = 0; c < vdate.size(); c++)
		{	
			
			grid->SetReadOnly(r, c);
		}
	}
}

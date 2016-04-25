#include "panelTurni.h"
#include "repositorydipendente.h"
#include "DialogTurno.h"

PanelTurni::PanelTurni(wxWindow * parent, int id, wxSize size)
	:wxPanel{parent, id, wxDefaultPosition, size}
{
	RepositoryDipendente repo;
	vdipendenti = repo.all();

	sizer = new wxBoxSizer{ wxVERTICAL };
	calendar = new wxCalendarCtrl{ this, -1 };
	grid = new wxGrid{ this,-1 };
	grid->CreateGrid(vdipendenti.size(), COLS);
	grid->Bind(wxEVT_GRID_CELL_LEFT_DCLICK, &PanelTurni::OnCellSelected, this);

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

void PanelTurni::OnCellSelected(wxGridEvent & evt)
{
	int row = evt.GetRow();
	int col = evt.GetCol();
	Dipendente d(vdipendenti[row]);
	wxDateTime data(vdate[col]);
	DialogTurno dlg(GetParent(), d, data);
	
	if (dlg.ShowModal() == wxID_OK)
	{
		tipoturno_t tipoTurno = dlg.getTipo();
		wxDateTime dtIn = dlg.getDataInizio();
		wxDateTime dtFn = dlg.getDataFine();
		datetime dataInizio(dtIn.GetDay(), dtIn.GetMonth() + 1, dtIn.GetYear(), dtIn.GetHour(), dtIn.GetMinute(), 0);
		datetime dataFine(dtFn.GetDay(), dtFn.GetMonth() + 1, dtFn.GetYear(), dtFn.GetHour(), dtFn.GetMinute(), 0);
		string motivazione = dlg.getMotivazione().ToStdString();

		ServiceTurni service;
		if (tipoTurno == tipoturno_t::TURNO)
		{
			auto turno = service.PianificaTurno(d, dataInizio, dataFine, motivazione);
			//wxMessageBox("Pianificato turno: " + turno.get_inizio().to_date_string(), "Turno", wxICON_INFORMATION);
			VisualizzaPianificazione(row, col, turno);
		}
		else
		{
			auto assenza = service.PianificaAssenza(d, dataInizio, dataFine, motivazione);
			//wxMessageBox("Pianificata assenza: " + assenza.get_inizio().to_date_string(), "Assenza", wxICON_INFORMATION);
			VisualizzaPianificazione(row, col, assenza);
		}
	}
	else
	{

	}
}

void PanelTurni::VisualizzaPianificazione(int row, int col, const Presenza & pn)
{
	grid->SetCellBackgroundColour(row, col, wxColour(*wxGREEN));
	grid->SetCellValue(row, col, pn.get_reparto() + "\n" + pn.get_inizio().to_time_string() + "-" + pn.get_fine().to_time_string());
}

void PanelTurni::VisualizzaPianificazione(int row, int col, const Assenza & pn)
{
	grid->SetCellBackgroundColour(row, col, wxColour(*wxRED));
	grid->SetCellValue(row, col, pn.get_motivazione());
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

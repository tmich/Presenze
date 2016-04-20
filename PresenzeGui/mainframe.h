#pragma once
#include <wx\wx.h>
#include <wx/aui/aui.h>
#include <wx/ribbon/bar.h>
#include <wx/ribbon/buttonbar.h>
#include <wx/artprov.h>
#include <wx/grid.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);

	// Destructor
	virtual ~MainFrame();

private:
	wxAuiNotebook* auiNotebook;
	wxGrid* grid;

	// ribbon
	wxRibbonBar* ribbonBar;
	wxRibbonPage* homeRibbonPage;
	wxRibbonPage* editRibbonPage;
	wxRibbonPanel* homeRibbonPanel;
	wxRibbonPanel* itemRibbonPanel;
	wxRibbonButtonBar* homeRibbonButtonBar;
	wxRibbonButtonBar* itemRibbonButtonBar;
};
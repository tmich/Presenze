#include "mynotebook.h"

myNotebook::myNotebook(wxWindow * window, wxWindowID id)
	:wxNotebook(window, id)
{
}

myNotebook::~myNotebook()
{
}

void myNotebook::OnTabChange(wxBookCtrlEvent& event)
{
	/*wxMessageDialog* dialog = new wxMessageDialog(NULL,
		"Current Selection: " + wxString::FromDouble(event.GetSelection()) +
		"\nPrevious Selection: " + wxString::FromDouble(event.GetOldSelection()));
	dialog->ShowModal();*/
}

BEGIN_EVENT_TABLE(myNotebook, wxNotebook)
EVT_NOTEBOOK_PAGE_CHANGED(ID_NOTEBOOK, myNotebook::OnTabChange)
END_EVENT_TABLE()
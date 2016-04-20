#pragma once
#include <wx\wx.h>

class ListaDipendentiDlg : public wxDialog
{
public:
	ListaDipendentiDlg(wxWindow *parent);
	~ListaDipendentiDlg();
private:
	wxListBox *lstDip;
};
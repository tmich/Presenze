#pragma once
#include <wx/wx.h>
#include <wx/notebook.h>

enum
{
	ID_NOTEBOOK = 10
};
class myNotebook :public wxNotebook
{
public:
	myNotebook(wxWindow* window, wxWindowID id);
	~myNotebook();

	void OnTabChange(wxBookCtrlEvent& event);

	DECLARE_EVENT_TABLE()
};
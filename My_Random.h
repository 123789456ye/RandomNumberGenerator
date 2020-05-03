//Name:			My_Random.h
//Purpose:		define My_random class
//Author:		123789456ye

#ifndef _My_Random_H_
#define _My_Random_H_

#include "wx/wx.h"
#include "wx/statline.h"


enum
{
	ID_My_Random = 10001,
	ID_Ban = 10002,
	ID_Reset = 10003,
	ID_Name = 10004,
	ID_Number = 10005,
	ID_Generate = 10006
};

//class My_Random Declraration

class My_Random : public wxDialog
{
	DECLARE_CLASS(My_Random);
	DECLARE_EVENT_TABLE()
public:
	My_Random();
	My_Random(wxWindow* parent,
		wxWindowID id = ID_My_Random,
		const wxString& caption = wxT("Random number Generator"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU);

	void Init();
	void Init_List();

	bool Create(wxWindow* parent,
		wxWindowID id = ID_My_Random,
		const wxString& caption = wxT("Random number Generator"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU);

	void CreateControls();

	void SetDialogValidators();

	void SetDialogHelp();

	void OnCheckUpdate(wxUpdateUIEvent& event);
	void OnGenerateClick(wxCommandEvent& event);
	void OnResetClick(wxCommandEvent& event);
	void OnHelpClick(wxCommandEvent& event);
	void Load_List(wxCommandEvent& event);


	void SetNumber(const int& number) { Ban_Number = number; }
	int Get_Ban_Number() const { return Ban_Number; }

	void Set_Check(bool check) { Ban_Check = check; }
	bool Get_Check(bool check) const { return Ban_Check; }

	bool TransferDataToWindow();
	bool TransferDataFromWindow();

	int Ban_Number;
	bool Ban_Check;
	wxString Name, namelist[105];
};

#endif
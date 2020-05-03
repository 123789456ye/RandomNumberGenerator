//Name:			My_Random.cpp
//Purpose:		Implement My_Random.h
//Author:		123789456ye

#include "My_Random.h"
#include "wx/wx.h"
#include "wx/statline.h"
#include "wx/valtext.h"
#include "wx/valgen.h"
#include "wx\msw\spinctrl.h"
#include "wx/filedlg.h"
#include "wx/wfstream.h"
#include <wx/textfile.h>
#include <wx/txtstrm.h>


IMPLEMENT_CLASS(My_Random, wxDialog);

//Event table defination
BEGIN_EVENT_TABLE(My_Random, wxDialog)
EVT_UPDATE_UI(ID_Number, My_Random::OnCheckUpdate)
EVT_BUTTON(ID_Generate, My_Random::OnGenerateClick)
EVT_BUTTON(ID_Reset, My_Random::OnResetClick)
EVT_BUTTON(wxID_HELP, My_Random::OnHelpClick)
EVT_BUTTON(wxID_FILE,My_Random::Load_List)
END_EVENT_TABLE()

//Constructor
My_Random::My_Random()
{
	Init();
}

My_Random::My_Random(wxWindow* parent,
	wxWindowID id, const wxString& caption,
	const wxPoint& pos, const wxSize& size, long style)
{
	Init();
	Create(parent, id, caption, pos, size, style);
}

void My_Random::Init()
{
	Ban_Number = 37;
	Ban_Check = true;
	Name = wxEmptyString;
}

bool My_Random::Create(wxWindow* parent,
	wxWindowID id, const wxString& caption,
	const wxPoint& pos, const wxSize& size, long style)
{
	// dialog
	SetExtraStyle(wxWS_EX_BLOCK_EVENTS | wxDIALOG_EX_CONTEXTHELP);
	if (!wxDialog::Create(parent, id, caption, pos, size, style))
		return false;
	CreateControls();
	SetDialogHelp();
	SetDialogValidators();
	// This fits the dialog to the minimum size dictated by
	// the sizers
	GetSizer()->Fit(this);
	// This ensures that the dialog cannot be sized smaller
	// than the minimum size
	GetSizer()->SetSizeHints(this);
	Centre();
	Init_List();
	return true;
}

//Control Creation

void My_Random::CreateControls()
{
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(topSizer);

	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(boxSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	wxStaticText* descr = new wxStaticText(this, wxID_STATIC,
		wxT("Test mode."), wxDefaultPosition, wxDefaultSize, 0);
	boxSizer->Add(descr, 0, wxALIGN_LEFT | wxALL, 5);

	boxSizer->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	wxStaticText* nameLabel = new wxStaticText(this, wxID_STATIC,
		wxT("&Name:"), wxDefaultPosition, wxDefaultSize, 0);
	boxSizer->Add(nameLabel, 0, wxALIGN_LEFT | wxALL, 5);

	wxTextCtrl* nameCtrl = new wxTextCtrl(this, ID_Name, wxT(""), wxDefaultPosition, wxDefaultSize, 0);
	boxSizer->Add(nameCtrl, 0, wxGROW | wxALL, 5);

	wxBoxSizer* NumberCheckBox = new wxBoxSizer(wxHORIZONTAL);
	boxSizer->Add(NumberCheckBox, 0, wxGROW | wxALL, 5);

	wxStaticText* NumberLabel = new wxStaticText(this, wxID_STATIC,
		wxT("Ban_number:"), wxDefaultPosition, wxDefaultSize, 0);
	NumberCheckBox->Add(NumberLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	wxSpinCtrl* Numberspin = new wxSpinCtrl(this, ID_Number,
		wxEmptyString, wxDefaultPosition, wxSize(60, -1),
		wxSP_ARROW_KEYS, 1, 61, 37);
	NumberCheckBox->Add(Numberspin, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	wxCheckBox* BanCheckBox = new wxCheckBox(this, ID_Ban,
		wxT("&Ban"), wxDefaultPosition, wxDefaultSize, 0);
	BanCheckBox->SetValue(true);
	NumberCheckBox->Add(BanCheckBox, 0,
		wxALIGN_CENTER_VERTICAL | wxALL, 5);

	wxStaticLine* line = new wxStaticLine(this, wxID_STATIC,
		wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	boxSizer->Add(line, 0, wxGROW | wxALL, 5);

	wxBoxSizer* OkCancelBox = new wxBoxSizer(wxHORIZONTAL);
	boxSizer->Add(OkCancelBox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	wxButton* reset = new wxButton(this, ID_Reset, wxT("&Reset"),
		wxDefaultPosition, wxDefaultSize, 0);
	OkCancelBox->Add(reset, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	wxButton* gen = new wxButton(this, ID_Generate, wxT("&Generate"),
		wxDefaultPosition, wxDefaultSize, 0);
	OkCancelBox->Add(gen, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	wxButton* cancel = new wxButton(this, wxID_CANCEL,
		wxT("&Cancel"), wxDefaultPosition, wxDefaultSize, 0);
	OkCancelBox->Add(cancel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	wxButton* Load = new wxButton(this, wxID_FILE, wxT("&Load_list"),
		wxDefaultPosition, wxDefaultSize, 0);
	OkCancelBox->Add(Load, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	wxButton* help = new wxButton(this, wxID_HELP, wxT("&Help"),
		wxDefaultPosition, wxDefaultSize, 0);
	OkCancelBox->Add(help, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
}

void My_Random::SetDialogValidators()
{
	FindWindow(ID_Ban)->SetValidator(
		wxGenericValidator(&Ban_Check));
}

void My_Random::SetDialogHelp()
{
	wxString Ban_Number_help = wxT("Choose the number that will not be chose or not.");
	FindWindow(ID_Ban)->SetHelpText(Ban_Number_help);
	FindWindow(ID_Ban)->SetToolTip(Ban_Number_help);
}

void My_Random::OnCheckUpdate(wxUpdateUIEvent& event)
{
	wxCheckBox* CheckCtrl = (wxCheckBox*)FindWindow(ID_Ban);
	event.Enable(CheckCtrl->GetValue());
}

#include <random>
#include <ctime>
#include <iostream>
#include "wx/filedlg.h"
#include "wx/wfstream.h"

std::mt19937 gen((unsigned long long)new char);
std::uniform_int_distribution<> dis(1, 61);
void My_Random::OnGenerateClick(wxCommandEvent& event)
{
	TransferDataFromWindow();
	wxCheckBox* CheckCtrl = (wxCheckBox*)FindWindow(ID_Ban);
	int tp = dis(gen);
	if (CheckCtrl->GetValue() == true)
	{
		wxSpinCtrl* Number = (wxSpinCtrl*)FindWindow(ID_Number);
		int tmp = Number->GetValue();
		while (tp == tmp) tp = dis(gen);
	}
	Name = namelist[tp];
	TransferDataToWindow();
}

void My_Random::OnResetClick(wxCommandEvent& event)
{
	Init();
	TransferDataToWindow();
}

void My_Random::OnHelpClick(wxCommandEvent& event)
{
	wxString helpText =
		wxT("Please Choose the number you do not want to see.\n Or you can choose not to do that.\n");
	wxMessageBox(helpText,
		wxT("Personal Record Dialog Help"),
		wxOK | wxICON_INFORMATION, this);
}

bool My_Random::TransferDataToWindow()
{
	wxTextCtrl* nameCtrl = (wxTextCtrl*)FindWindow(ID_Name);
	wxSpinCtrl* NumberCtrl = (wxSpinCtrl*)FindWindow(ID_Number);
	wxCheckBox* CheckCtrl = (wxCheckBox*)FindWindow(ID_Ban);
	nameCtrl->SetValue(Name);
	NumberCtrl->SetValue(Ban_Number);
	CheckCtrl->SetValue(Ban_Check);
	return true;
}

bool My_Random::TransferDataFromWindow()
{
	wxTextCtrl* nameCtrl = (wxTextCtrl*)FindWindow(ID_Name);
	wxSpinCtrl* NumberCtrl = (wxSpinCtrl*)FindWindow(ID_Number);
	wxCheckBox* CheckCtrl = (wxCheckBox*)FindWindow(ID_Ban);
	Name = nameCtrl->GetValue();
	Ban_Number = NumberCtrl->GetValue();
	Ban_Check = CheckCtrl->GetValue();
	return true;
}

void My_Random::Init_List()
{
	wxString path = "source.txt";
	wxFileInputStream inStream(path);
	wxTextInputStream text(inStream);
	int count = 0;
	while (inStream.IsOk() && !inStream.Eof())
		namelist[++count] = text.ReadLine();
}

void My_Random::Load_List(wxCommandEvent& event)
{
	wxString caption = wxT("Choose a file");
	wxString wildcard =
		wxT("TXT files (*.txt)|*.txt");
	wxString defaultDir = wxEmptyString;
	wxString defaultFilename = "source.txt";
	wxFileDialog dialog(this, caption, defaultDir, defaultFilename,
		wildcard, wxFD_OPEN);
	if (dialog.ShowModal() == wxID_OK)
	{
		wxString path = dialog.GetPath();
		wxFileInputStream inStream(path);
		wxTextInputStream text(inStream);
		int count = 0;
		while (inStream.IsOk() && !inStream.Eof())
			namelist[++count] = text.ReadLine();
	}
}
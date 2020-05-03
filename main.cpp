//Name:			main.cpp
//Purpose:		demo for random number
//Author:		123789456ye
#include "My_Random.h"
#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "wx/statline.h"


#define __Version 1.0
//Basic defination
class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title);

	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnSetting(wxCommandEvent& event);
	enum
	{
		ID_Setting = 10010
	};
private:
	DECLARE_EVENT_TABLE()
};

DECLARE_APP(MyApp);
IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	MyFrame* frame = new MyFrame(wxT("Random num generator"));
	frame->Show(true);
	return true;
}

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
	EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
	EVT_MENU(ID_Setting, MyFrame::OnSetting)
END_EVENT_TABLE()

//implement functions

void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxString msg;
	msg.Printf(wxT("This is an exmaple developed by 123789456ye\nVersion %.1f"), __Version);

	wxMessageBox(msg, wxT("About this program"),
		wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnQuit(wxCommandEvent& event)
{
	Close();
}

void MyFrame::OnSetting(wxCommandEvent& event)
{
	My_Random random(this);
	random.ShowModal();
}

MyFrame::MyFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title)
{
	// Create a menu bar
	wxMenu* SettingMenu = new wxMenu;

	// The "About" item should be in the help menu
	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(wxID_ABOUT, wxT("&About...\tF1"),
		wxT("Show about this program"));

	SettingMenu->Append(ID_Setting, wxT("&Generator"),
		wxT("Ban a person(number)..."));
	SettingMenu->Append(wxID_EXIT, wxT("E&xit\tAlt-X"),
		wxT("Quit this program"));

	// Now append the freshly created menu to the menu bar...
	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(SettingMenu, wxT("&Generator"));
	menuBar->Append(helpMenu, wxT("&Help"));

	// ... and attach this menu bar to the frame
	SetMenuBar(menuBar);

	// UI canvas
	wxPanel* panel = new wxPanel(this, -1);
}
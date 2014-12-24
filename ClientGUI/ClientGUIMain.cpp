/***************************************************************
 * Name:      ClientGUIMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    xula (xula@vnext.vn)
 * Created:   2014-10-21
 * Copyright: xula (vnext.vn)
 * License:
 **************************************************************/

#include "ClientGUIMain.h"
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/wx.h>
#include <wx/file.h>
#include <string>
#include <iostream>

//(*InternalHeaders(ClientGUIFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

using namespace std;

const int COMMAND_SIZE = 1024;
const wxString LOCALHOST_IP = L"127.0.0.1";
const wxString PORT = L"12345";

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(ClientGUIFrame)
const long ClientGUIFrame::ID_STATICTEXT4 = wxNewId();
const long ClientGUIFrame::ID_TEXTCTRL4 = wxNewId();
const long ClientGUIFrame::ID_STATICTEXT3 = wxNewId();
const long ClientGUIFrame::ID_TEXTCTRL3 = wxNewId();
const long ClientGUIFrame::ID_BUTTON2 = wxNewId();
const long ClientGUIFrame::ID_BUTTON3 = wxNewId();
const long ClientGUIFrame::ID_STATICTEXT1 = wxNewId();
const long ClientGUIFrame::ID_CHOICE1 = wxNewId();
const long ClientGUIFrame::ID_STATICTEXT2 = wxNewId();
const long ClientGUIFrame::ID_TEXTCTRL1 = wxNewId();
const long ClientGUIFrame::ID_BUTTON1 = wxNewId();
const long ClientGUIFrame::ID_TEXTCTRL2 = wxNewId();
const long ClientGUIFrame::idMenuQuit = wxNewId();
const long ClientGUIFrame::idMenuAbout = wxNewId();
const long ClientGUIFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ClientGUIFrame,wxFrame)
    //(*EventTable(ClientGUIFrame)
    //*)
END_EVENT_TABLE()

ClientGUIFrame::ClientGUIFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(ClientGUIFrame)
    wxBoxSizer* BoxSizer4;
    wxStaticBoxSizer* StaticBoxSizer2;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer8;
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxGridSizer* GridSizer1;
    wxBoxSizer* BoxSizer9;
    wxMenuBar* MenuBar1;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    GridSizer1 = new wxGridSizer(0, 2, 0, 0);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Config"));
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Server IP Address"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    BoxSizer5->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtServerIP = new wxTextCtrl(this, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    BoxSizer5->Add(txtServerIP, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(BoxSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Port"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    BoxSizer6->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtPort = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    BoxSizer6->Add(txtPort, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(BoxSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    btnSubmit = new wxButton(this, ID_BUTTON2, _("Submit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer4->Add(btnSubmit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnCancel = new wxButton(this, ID_BUTTON3, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    BoxSizer4->Add(btnCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(BoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Source Code"));
    BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Compiler"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
    BoxSizer7->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Choice1 = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxSize(101,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    Choice1->SetSelection( Choice1->Append(_("C")) );
    Choice1->Append(_("C++"));
    Choice1->Append(_("C#"));
    Choice1->Append(_("Java"));
    Choice1->Append(_("PHP"));
    Choice1->Append(_("Visual Basic"));
    BoxSizer7->Add(Choice1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2->Add(BoxSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Examination Code"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT2"));
    BoxSizer8->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtExamCode = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    BoxSizer8->Add(txtExamCode, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2->Add(BoxSizer8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    btnSourcePath = new wxButton(this, ID_BUTTON1, _("Source File"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer9->Add(btnSourcePath, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtSourcePath = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    BoxSizer9->Add(txtSourcePath, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2->Add(BoxSizer9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(StaticBoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(GridSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    GridSizer1->Fit(this);
    GridSizer1->SetSizeHints(this);

    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ClientGUIFrame::OnbtnSubmitClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ClientGUIFrame::OnbtnCancelClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ClientGUIFrame::OnbtnSourcePathClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ClientGUIFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ClientGUIFrame::OnAbout);
    //*)
    InitializeConfig();
    SetIcon(wxICON(FRAME_ICON)); // set icon on top-left of frame
    SetLabel(wxT("Client")); // set title
}

ClientGUIFrame::~ClientGUIFrame()
{
    //(*Destroy(ClientGUIFrame)
    //*)
}

void ClientGUIFrame::InitializeConfig()
{
    txtPort->AppendText(PORT);
    txtServerIP->AppendText(LOCALHOST_IP);
}

void ClientGUIFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void ClientGUIFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg( wxT("Testing Code Application - Client GUI"));
    wxMessageBox(msg, _("About"));
}

/*
* Execute command from cmd and return to std::string
* Reference: http://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c
*/
std::string exec(char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[256];
    std::string result = "";
    while(!feof(pipe)) {
    	if(fgets(buffer, 256, pipe) != NULL)
    		result += buffer;
    }
    pclose(pipe);
    return result;
}

// Add quotes to path file/folder (for the case that it contains space ' ')
wxString AddQuotes(wxString str)
{
    str = _("\"") + str + _("\"");
    return str;
}

void ClientGUIFrame::OnbtnSubmitClick(wxCommandEvent& event)
{
    wxString sourcePath = AddQuotes(txtSourcePath->GetValue());
    wxString executionPath (L"Client.exe ");
    wxString serverIP = txtServerIP->GetValue() + _(" ");
    wxString port = txtPort->GetValue();
    wxString compiler;
    switch (Choice1->GetCurrentSelection())
    {
    case 0:
        compiler = _T(" -c ");
        break;
    case 1:
        compiler = _T(" -cpp ");
        break;
    case 2:
        compiler = _T(" -vc ");
        break;
    case 3:
        compiler = _T(" -j ");
        break;
    case 4:
        compiler = _T(" -p ");
        break;
    case 5:
        compiler = _T(" -vb ");
        break;
    default:
        break;
    }
    wxString command_str = executionPath + serverIP + port + compiler + sourcePath;
    // copy to char array
    char command_ch[COMMAND_SIZE];
    strncpy(command_ch, (const char*)command_str.mb_str(wxConvUTF8), COMMAND_SIZE - 1);
    // execute command and return to std::string
    //system(command_ch);
    std::string output_msg = exec(command_ch);
    wxString msg(output_msg.c_str(), wxConvUTF8); // convert std::string to wxString
    wxMessageBox(msg, _("Result"));
}

void ClientGUIFrame::OnbtnCancelClick(wxCommandEvent& event)
{
    Close();
}

void ClientGUIFrame::OnbtnSourcePathClick(wxCommandEvent& event)
{
    wxFileDialog *OpenDialog = new wxFileDialog(
		this, _("Choose a file to open"), wxEmptyString, wxEmptyString,
		_("Source files (*.*)|*.*"), wxFD_OPEN, wxDefaultPosition);
    // if the user open file
	if (OpenDialog->ShowModal() == wxID_OK)
	{
	    wxString currentDocPath;
		currentDocPath = OpenDialog->GetPath();
		// set path to text control
		txtSourcePath->SetValue(currentDocPath);
	}
	// clean up after ourselves
	OpenDialog->Destroy();
}

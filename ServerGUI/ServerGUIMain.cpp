/***************************************************************
 * Name:      ServerGUIMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    xula (xula@vnext.vn)
 * Created:   2014-10-22
 * Copyright: xula (vnext.vn)
 * License:
 **************************************************************/

#include "ServerGUIMain.h"
#include <wx/msgdlg.h> // msg dialog
#include <wx/dirdlg.h> // file dialog
#include <wx/xml/xml.h> // xml
#include <wx/wx.h> // for icon
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

//(*InternalHeaders(ServerGUIFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

void UpdateHistory();
void StartServer();
void ReadLogFile();
wxString AddQuotes(wxString);
std::string exec(char*);

using namespace std;

const int COMMAND_SIZE = 10000;
const wxString PORT = L"12345";
const wxString TIME_EXECUTION = L"10000";

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

//(*IdInit(ServerGUIFrame)
const long ServerGUIFrame::ID_STATICTEXT1 = wxNewId();
const long ServerGUIFrame::ID_TEXTCTRL1 = wxNewId();
const long ServerGUIFrame::ID_BUTTON3 = wxNewId();
const long ServerGUIFrame::ID_TEXTCTRL2 = wxNewId();
const long ServerGUIFrame::ID_BUTTON4 = wxNewId();
const long ServerGUIFrame::ID_TEXTCTRL3 = wxNewId();
const long ServerGUIFrame::ID_BUTTON5 = wxNewId();
const long ServerGUIFrame::ID_TEXTCTRL4 = wxNewId();
const long ServerGUIFrame::ID_BUTTON6 = wxNewId();
const long ServerGUIFrame::ID_TEXTCTRL6 = wxNewId();
const long ServerGUIFrame::ID_STATICTEXT5 = wxNewId();
const long ServerGUIFrame::ID_TEXTCTRL5 = wxNewId();
const long ServerGUIFrame::ID_BUTTON1 = wxNewId();
const long ServerGUIFrame::ID_BUTTON2 = wxNewId();
const long ServerGUIFrame::ID_PANEL1 = wxNewId();
const long ServerGUIFrame::ID_LISTCTRL1 = wxNewId();
const long ServerGUIFrame::ID_PANEL2 = wxNewId();
const long ServerGUIFrame::ID_NOTEBOOK1 = wxNewId();
const long ServerGUIFrame::idMenuQuit = wxNewId();
const long ServerGUIFrame::idMenuAbout = wxNewId();
const long ServerGUIFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ServerGUIFrame,wxFrame)
    //(*EventTable(ServerGUIFrame)
    //*)
END_EVENT_TABLE()

ServerGUIFrame::ServerGUIFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(ServerGUIFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxGridSizer* GridSizer1;
    wxGridSizer* GridSizer3;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;
    wxGridSizer* GridSizer2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    GridSizer1 = new wxGridSizer(0, 1, 0, 0);
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    GridSizer2 = new wxGridSizer(3, 2, 0, 0);
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Port"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    GridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtPort = new wxTextCtrl(Panel1, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(228,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    GridSizer2->Add(txtPort, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnSourceDir = new wxButton(Panel1, ID_BUTTON3, _("Source Directory"), wxDefaultPosition, wxSize(120,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    GridSizer2->Add(btnSourceDir, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtSourceDir = new wxTextCtrl(Panel1, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(228,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    GridSizer2->Add(txtSourceDir, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnInputDir = new wxButton(Panel1, ID_BUTTON4, _("Input Directory"), wxDefaultPosition, wxSize(120,23), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    GridSizer2->Add(btnInputDir, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtInputDir = new wxTextCtrl(Panel1, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxSize(228,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    GridSizer2->Add(txtInputDir, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnOutputDir = new wxButton(Panel1, ID_BUTTON5, _("Output Directory"), wxDefaultPosition, wxSize(122,23), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    GridSizer2->Add(btnOutputDir, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtOutputDir = new wxTextCtrl(Panel1, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxSize(228,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    GridSizer2->Add(txtOutputDir, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnCheckDir = new wxButton(Panel1, ID_BUTTON6, _("Check Point Directory"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    GridSizer2->Add(btnCheckDir, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtCheckDir = new wxTextCtrl(Panel1, ID_TEXTCTRL6, wxEmptyString, wxDefaultPosition, wxSize(228,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
    GridSizer2->Add(txtCheckDir, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText5 = new wxStaticText(Panel1, ID_STATICTEXT5, _("Maximum Time Execution (ms)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    GridSizer2->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtTimeExecution = new wxTextCtrl(Panel1, ID_TEXTCTRL5, wxEmptyString, wxDefaultPosition, wxSize(228,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    GridSizer2->Add(txtTimeExecution, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnStartServer = new wxButton(Panel1, ID_BUTTON1, _("Start Server"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    GridSizer2->Add(btnStartServer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnQuit = new wxButton(Panel1, ID_BUTTON2, _("Quit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    GridSizer2->Add(btnQuit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(GridSizer2);
    GridSizer2->Fit(Panel1);
    GridSizer2->SetSizeHints(Panel1);
    Panel2 = new wxPanel(Notebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    GridSizer3 = new wxGridSizer(0, 1, 0, 0);
    ListCtrl1 = new wxListCtrl(Panel2, ID_LISTCTRL1, wxDefaultPosition, wxSize(474,125), wxLC_REPORT, wxDefaultValidator, _T("ID_LISTCTRL1"));
    GridSizer3->Add(ListCtrl1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel2->SetSizer(GridSizer3);
    GridSizer3->Fit(Panel2);
    GridSizer3->SetSizeHints(Panel2);
    Notebook1->AddPage(Panel1, _("Config"), false);
    Notebook1->AddPage(Panel2, _("History"), false);
    GridSizer1->Add(Notebook1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
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

    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ServerGUIFrame::OnbtnSourceDirClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ServerGUIFrame::OnbtnInputDirClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ServerGUIFrame::OnbtnOutputDirClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ServerGUIFrame::OnbtnCheckDirClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ServerGUIFrame::OnbtnStartServerClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ServerGUIFrame::OnbtnQuitClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ServerGUIFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ServerGUIFrame::OnAbout);
    //*)
    InitializePaths();
    ShowHistory();
    SetIcon(wxICON(FRAME_ICON)); // set icon on top-left of frame
    SetLabel(wxT("Server")); // set title
}

ServerGUIFrame::~ServerGUIFrame()
{
    //(*Destroy(ServerGUIFrame)
    //*)
}

// Initialize directories according to current working directory
void ServerGUIFrame::InitializePaths()
{
    txtPort->AppendText(PORT);
    // set default paths
    txtSourceDir->AppendText(wxGetCwd() + _("\\Source"));
    txtInputDir->AppendText(wxGetCwd() + _("\\Input"));
    txtOutputDir->AppendText(wxGetCwd() + _("\\Output"));
    txtCheckDir->AppendText(wxGetCwd() + _("\\CheckPoint"));
    // read xml config file
    wxXmlDocument doc;
    if (!doc.Load(wxGetCwd() + wxT("\\CheckPoint\\config.xml")))
    {
        txtTimeExecution->AppendText(TIME_EXECUTION); // return default
        return;
    }
    wxXmlNode *child = doc.GetRoot()->GetChildren();
    while (child)
    {
        if (child->GetName() == L"time_execution")
        {
            wxString timeExecution = child->GetNodeContent();
            txtTimeExecution->AppendText(timeExecution);
            break;
        }
        child = child->GetNext();
    }
}

// Show test history in list view
void ServerGUIFrame::ShowHistory()
{
    ListCtrl1->InsertColumn(0, L"IP", wxLIST_FORMAT_LEFT, 100);
    ListCtrl1->InsertColumn(1, L"Message", wxLIST_FORMAT_LEFT, 200);
    ListCtrl1->InsertColumn(2, L"Result", wxLIST_FORMAT_LEFT, 50);
    ListCtrl1->InsertColumn(3, L"Time Connected", wxLIST_FORMAT_LEFT, 200);
    string line;
    ifstream logFile("result.log");
    if (logFile.is_open())
    {
        int index = 0;
        while ( getline(logFile, line))
        {
            vector<string> elements;
            string element;
            char delimiter = ',';
            stringstream ss(line);
            // split each line by ',' to ip address, message, result
            while (getline(ss, element, delimiter))
            {
                if (!element.empty())
                    elements.push_back(element);
            }
            for (unsigned int i = 0; i < elements.size(); i++)
            {
                wxString resultMsg(elements[i].c_str(), wxConvUTF8);
                if (i == 0) // add an item with value is ip adress
                    ListCtrl1->InsertItem(index, resultMsg);
                // set another properties of item (message + result)
                ListCtrl1->SetItem(index, i, resultMsg);
            }
        }
        logFile.close();
    }
}

// Turn on server
void ServerGUIFrame::StartServer()
{
    // [exe] [port] [source] [input] [output] [check_point] [time_execution]
    wxString exeFile (L"Server.exe ");
    wxString port = txtPort->GetValue() + _(" ");
    wxString sourcePath = AddQuotes(txtSourceDir->GetValue());
    wxString inputPath = AddQuotes(txtInputDir->GetValue());
    wxString outputPath = AddQuotes(txtOutputDir->GetValue());
    wxString timeExecution = txtTimeExecution->GetValue();
    wxString checkPointPath = AddQuotes(txtCheckDir->GetValue());
    wxString command_str = exeFile + port + sourcePath + inputPath + outputPath + checkPointPath + timeExecution;
    // copy to char array
    char command_ch[COMMAND_SIZE];
    strncpy(command_ch, (const char*)command_str.mb_str(wxConvUTF8), COMMAND_SIZE - 1);
    system(command_ch); // run from command line
}

// Add quotes to path file/folder (in the case it contains some spaces ' ')
wxString AddQuotes(wxString str)
{
    wxString str_quotes = _("\"") + str + _("\" ");
    return str_quotes;
}

/*
* Execute command from cmd and return to std::string
* Reference: http://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c
*/
string exec(char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    string result = "";
    while(!feof(pipe)) {
    	if(fgets(buffer, 128, pipe) != NULL)
    		result += buffer;
    }
    pclose(pipe);
    return result;
}

void ServerGUIFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void ServerGUIFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg( wxT("Testing Code Application - Server GUI"));
    wxMessageBox(msg, _("About"));
}

// Source Directory Button
void ServerGUIFrame::OnbtnSourceDirClick(wxCommandEvent& event)
{
    wxString LastDir = txtSourceDir->GetValue();
    wxDirDialog dlg(this, L"Choose source directory", LastDir, wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    if (dlg.ShowModal() == wxID_OK)
    {
        wxString currentDir = dlg.GetPath();
        txtSourceDir->SetValue(currentDir);
    }
	dlg.Destroy();
}

// Input Directory Button
void ServerGUIFrame::OnbtnInputDirClick(wxCommandEvent& event)
{
    wxString LastDir = txtInputDir->GetValue();
    wxDirDialog dlg(this, L"Choose input directory", LastDir, wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    if (dlg.ShowModal() == wxID_OK)
    {
        wxString currentDir = dlg.GetPath();
        txtInputDir->SetValue(currentDir);
    }
	dlg.Destroy();
}

// Output Directory Button
void ServerGUIFrame::OnbtnOutputDirClick(wxCommandEvent& event)
{
    wxString LastDir = txtOutputDir->GetValue();
    wxDirDialog dlg(this, L"Choose output directory", LastDir, wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    if (dlg.ShowModal() == wxID_OK)
    {
        wxString currentDir = dlg.GetPath();
		txtOutputDir->SetValue(currentDir);
    }
	dlg.Destroy();
}

// Check Point Directory Button
void ServerGUIFrame::OnbtnCheckDirClick(wxCommandEvent& event)
{
    wxString LastDir = txtCheckDir->GetValue();
    wxDirDialog dlg(this, L"Choose check point directory", LastDir, wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    if (dlg.ShowModal() == wxID_OK)
    {
        wxString currentDir = dlg.GetPath();
		txtCheckDir->SetValue(currentDir);
    }
	dlg.Destroy();
}

// Start Server Button
void ServerGUIFrame::OnbtnStartServerClick(wxCommandEvent& event)
{
    // turn on server to wait for connections ...
    StartServer();

    // display results from log file
    ListCtrl1->DeleteAllItems();
    ListCtrl1->DeleteAllColumns();
    ShowHistory();

    // display information msg box
    wxString msg = wxT("Please switch history tab to view test result.");
    wxMessageBox(msg, _("Info"));
}

// Quit Button
void ServerGUIFrame::OnbtnQuitClick(wxCommandEvent& event)
{
    Close();
}

/***************************************************************
 * Name:      ServerGUIMain.h
 * Purpose:   Defines Application Frame
 * Author:    xula (xula@vnext.vn)
 * Created:   2014-10-22
 * Copyright: xula (vnext.vn)
 * License:
 **************************************************************/

#ifndef SERVERGUIMAIN_H
#define SERVERGUIMAIN_H

//(*Headers(ServerGUIFrame)
#include <wx/listctrl.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class ServerGUIFrame: public wxFrame
{
    public:

        ServerGUIFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~ServerGUIFrame();

    private:
        void ShowHistory();
        void StartServer();
        void InitializePaths();
        //(*Handlers(ServerGUIFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnbtnSourceDirClick(wxCommandEvent& event);
        void OnbtnInputDirClick(wxCommandEvent& event);
        void OnbtnOutputDirClick(wxCommandEvent& event);
        void OnbtnCheckDirClick(wxCommandEvent& event);
        void OnbtnStartServerClick(wxCommandEvent& event);
        void OnbtnQuitClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(ServerGUIFrame)
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON3;
        static const long ID_TEXTCTRL2;
        static const long ID_BUTTON4;
        static const long ID_TEXTCTRL3;
        static const long ID_BUTTON5;
        static const long ID_TEXTCTRL4;
        static const long ID_BUTTON6;
        static const long ID_TEXTCTRL6;
        static const long ID_STATICTEXT5;
        static const long ID_TEXTCTRL5;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_PANEL1;
        static const long ID_LISTCTRL1;
        static const long ID_PANEL2;
        static const long ID_NOTEBOOK1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(ServerGUIFrame)
        wxListCtrl* ListCtrl1;
        wxNotebook* Notebook1;
        wxButton* btnStartServer;
        wxButton* btnInputDir;
        wxButton* btnQuit;
        wxTextCtrl* txtInputDir;
        wxTextCtrl* txtSourceDir;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxButton* btnOutputDir;
        wxButton* btnCheckDir;
        wxStaticText* StaticText5;
        wxTextCtrl* txtCheckDir;
        wxStatusBar* StatusBar1;
        wxTextCtrl* txtTimeExecution;
        wxButton* btnSourceDir;
        wxPanel* Panel2;
        wxTextCtrl* txtOutputDir;
        wxTextCtrl* txtPort;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // SERVERGUIMAIN_H

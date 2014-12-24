/***************************************************************
 * Name:      ClientGUIMain.h
 * Purpose:   Defines Application Frame
 * Author:    xula (xula@vnext.vn)
 * Created:   2014-10-21
 * Copyright: xula (vnext.vn)
 * License:
 **************************************************************/

#ifndef CLIENTGUIMAIN_H
#define CLIENTGUIMAIN_H

//(*Headers(ClientGUIFrame)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class ClientGUIFrame: public wxFrame
{
    public:

        ClientGUIFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~ClientGUIFrame();

    private:
        void InitializeConfig();
        //(*Handlers(ClientGUIFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnBtnCancelClick(wxCommandEvent& event);
        void OnBtnSubmitClick(wxCommandEvent& event);
        void OnBtnSourcePathClick(wxCommandEvent& event);
        void OnbtnSubmitClick(wxCommandEvent& event);
        void OnbtnCancelClick(wxCommandEvent& event);
        void OnbtnSourcePathClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(ClientGUIFrame)
        static const long ID_STATICTEXT4;
        static const long ID_TEXTCTRL4;
        static const long ID_STATICTEXT3;
        static const long ID_TEXTCTRL3;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_STATICTEXT1;
        static const long ID_CHOICE1;
        static const long ID_STATICTEXT2;
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON1;
        static const long ID_TEXTCTRL2;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(ClientGUIFrame)
        wxStaticText* StaticText2;
        wxButton* btnCancel;
        wxStaticText* StaticText1;
        wxButton* btnSubmit;
        wxStaticText* StaticText3;
        wxTextCtrl* txtSourcePath;
        wxTextCtrl* txtServerIP;
        wxStatusBar* StatusBar1;
        wxTextCtrl* txtExamCode;
        wxButton* btnSourcePath;
        wxStaticText* StaticText4;
        wxChoice* Choice1;
        wxTextCtrl* txtPort;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // CLIENTGUIMAIN_H

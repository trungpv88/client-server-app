/***************************************************************
 * Name:      ServerGUIApp.cpp
 * Purpose:   Code for Application Class
 * Author:    xula (xula@vnext.vn)
 * Created:   2014-10-22
 * Copyright: xula (vnext.vn)
 * License:
 **************************************************************/

#include "ServerGUIApp.h"

//(*AppHeaders
#include "ServerGUIMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(ServerGUIApp);

bool ServerGUIApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	ServerGUIFrame* Frame = new ServerGUIFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}

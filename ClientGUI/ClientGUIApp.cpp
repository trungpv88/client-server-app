/***************************************************************
 * Name:      ClientGUIApp.cpp
 * Purpose:   Code for Application Class
 * Author:    xula (xula@vnext.vn)
 * Created:   2014-10-21
 * Copyright: xula (vnext.vn)
 * License:
 **************************************************************/

#include "ClientGUIApp.h"

//(*AppHeaders
#include "ClientGUIMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(ClientGUIApp);

bool ClientGUIApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	ClientGUIFrame* Frame = new ClientGUIFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}

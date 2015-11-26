/***************************************************************
 * Name:      BME465_FinalProject_TextDetectionApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Michael Twardowski (Mtwardowski@my.uri.edu)
 * Created:   2015-11-25
 * Copyright: Michael Twardowski ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "BME465_FinalProject_TextDetectionApp.h"
#include "BME465_FinalProject_TextDetectionMain.h"

IMPLEMENT_APP(BME465_FinalProject_TextDetectionApp);

bool BME465_FinalProject_TextDetectionApp::OnInit()
{
    // create the main application window
    MyFrame *frame = new MyFrame(_T("BME465_FinalProject_TextDetection App"),
                                 wxPoint(50, 50), wxSize(800, 600));

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(TRUE);

    // Enable all image handlers - TIFF is among them
    ::wxInitAllImageHandlers();

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned FALSE here, the
    // application would exit immediately.
    return TRUE;

    /*
    BME465_FinalProject_TextDetectionDialog* dlg = new BME465_FinalProject_TextDetectionDialog(0L, _("wxWidgets Application Template"));
    dlg->SetIcon(wxICON(aaaa)); // To Set App Icon
    dlg->Show();
    return true; */ //p
}

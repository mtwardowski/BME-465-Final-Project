/***************************************************************
 * Name:      BME465_FinalProject_TextDetectionMain.h
 * Purpose:   Defines Application Frame
 * Author:    Michael Twardowski (Mtwardowski@my.uri.edu)
 * Created:   2015-11-25
 * Copyright: Michael Twardowski ()
 * License:
 **************************************************************/

#ifndef BME465_FINALPROJECT_TEXTDETECTIONMAIN_H
#define BME465_FINALPROJECT_TEXTDETECTIONMAIN_H

// Pre-compiler support
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#ifdef __BORLANDC__
    #pragma hdrstop
#endif


// needed to declare MyApp as the main activity
#include <wx/app.h>

#include <wx/button.h>  //p
#include <wx/statline.h> //p

#include "wx/slider.h"
#include "wx/toolbar.h"
#include "wx/utils.h"
#include "wx/image.h"
#include "wx/filedlg.h"
#include "wx/pen.h"
#include "math.h"
#include <cstdio>
#include <vector>
#include <algorithm>

#include "sliderFrame.hpp"
#include "image_processor.hpp"

// Define a new application type, each program should derive a class from wxApp
class MyApp: public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size,
            long style = wxDEFAULT_FRAME_STYLE);

    // event handlers (these functions should _not_ be virtual)


    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    void OnFilter( wxCommandEvent& event );

    void OnPaint( wxPaintEvent& event);
    void OnLoad(wxCommandEvent& WXUNUSED(event));

    void OnToGray(wxCommandEvent& event);

	// Lab 4
	void makeSlider(int sliderID, int deflt, int low, int high) ;
	void sliderHandler(void);
	void sliderWindowCloses(void);

	// Lab 5
	// Area Protoypes
	void OnAreaCalculation(wxCommandEvent& event);
	void OnLButton(wxMouseEvent& event);


	wxImage *masterImage;
    wxImage *pImage;



    // any class wishing to process wxWindows events must use this macro
    DECLARE_EVENT_TABLE()

// Lab 4
private:
	//Lab 4
	MySliderFrame *sliderFrame ;
	wxSlider *slider ;
	int sliderID ;
	int sliderValue ;

	// Lab 5
	// Area Variables
	int areaindex;
	wxPoint*areaborder;
	int pointNumber;
	double dist;
	// Area Flags
	bool bAreaCalculation;
	bool bleftDown;
	bool bRed;

};


// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------
enum
{
    // menu items
    MENU_FILE_OPEN = wxID_OPEN,
    MENU_FILE_QUIT = wxID_EXIT,
    MENU_FILTER    = 100,
    MENU_FILTER_LP = 101,
	MENU_FILTER_HP = 102,
	MENU_FILTER_NONLINEAR_MEDIAN = 104,
	MENU_FILTER_NONLINEAR_MINIMUM = 105,
	MENU_FILTER_NONLINEAR_MAXIMUM = 106,
	MENU_FILTER_EDGE = 107,
	MENU_FILTER_UNDO= 108,

	//Lab 4
	MENU_FILTER_BINARIZE = 110,
	SLIDER_ID = 500,
	BIN_SLIDER,

	//Lab 5
	ID_AreaCalculation = 300,


    ID_ToGray = 200,

    // Text Detection
    MENU_FILTER_TEXTDETECTION = 111,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    MENU_HELP_ABOUT = wxID_ABOUT
};

#endif

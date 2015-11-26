/***************************************************************
 * Name:      BME465_FinalProject_TextDetectionMain.cpp
 * Purpose:   Code for Application Frame
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

#include "BME465_FinalProject_TextDetectionMain.h"

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------
#include "resources/lp.xpm"
#include "resources/hp.xpm"
#include "resources/binary.xpm"
#include "resources/edge.xpm"
#include "resources/max.xpm"
#include "resources/min.xpm"
#include "resources/median.xpm"
#include "resources/area.xpm"

#include "resources/undo.xpm"


#include "wx/image.h"

// Lab 4
#include "sliderFrame.hpp"

wxIMPLEMENT_APP(MyApp);


// ----------------------------------------------------------------------------
// event tables and other macros for wxWindows
// ----------------------------------------------------------------------------

// the event tables connect the wxWindows events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(MENU_FILE_OPEN,  MyFrame::OnLoad)
    EVT_MENU(MENU_FILE_QUIT,  MyFrame::OnQuit)
    EVT_MENU(MENU_HELP_ABOUT, MyFrame::OnAbout)
    EVT_MENU(ID_ToGray, MyFrame::OnToGray)

    EVT_MENU(ID_ToGray, MyFrame::OnToGray)

    EVT_PAINT(MyFrame::OnPaint)

	EVT_MENU(MENU_FILTER_UNDO, MyFrame::OnFilter)

	// Lab 1
    EVT_MENU(MENU_FILTER_LP, MyFrame::OnFilter)
	EVT_MENU(MENU_FILTER_HP, MyFrame::OnFilter)

	// Lab 2
	EVT_MENU(MENU_FILTER_NONLINEAR_MEDIAN, MyFrame::OnFilter)
	EVT_MENU(MENU_FILTER_NONLINEAR_MINIMUM, MyFrame::OnFilter)
	EVT_MENU(MENU_FILTER_NONLINEAR_MAXIMUM, MyFrame::OnFilter)

	// Lab 3
	EVT_MENU(MENU_FILTER_EDGE, MyFrame::OnFilter)
	EVT_MENU(MENU_FILTER_BINARIZE, MyFrame::OnFilter)

	// Lab 4
	EVT_MENU(MENU_FILTER_BINARIZE, MyFrame::OnFilter)

	// Lab 5
	EVT_LEFT_DOWN(MyFrame::OnLButton)
	EVT_MENU(ID_AreaCalculation, MyFrame::OnAreaCalculation)


END_EVENT_TABLE()


// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
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
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------
// frame constructor
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size, long style)
       : wxFrame(NULL, -1, title, pos, size, style)
{
    // set the frame icon
    SetIcon(wxICON(mondrian));

#if wxUSE_MENUS
    // create a menu bars
    wxMenu *fileMenu = new wxMenu;
	wxMenu *helpMenu = new wxMenu;
    wxMenu *image_processMenu = new wxMenu;
    wxMenu *filterMenu = new wxMenu;
	wxMenu *NonLinMenu = new wxMenu;

    // the "About" item should be in the help menu
    fileMenu->Append(MENU_FILE_OPEN, _T("&Open...\tCtrl-O"), _T("Open a new Image"));
    fileMenu->Append(MENU_FILE_QUIT, _T("E&xit\tAlt-X"), _T("Quit this program"));

	// Creates Help Menu
    helpMenu->Append(MENU_HELP_ABOUT, _T("&About...\tF1"), _T("Show about dialog"));

	// Add linear filters to menu
    filterMenu->Append(MENU_FILTER_LP, _T("&Lowpass Filter\tAlt-L"), _T("Lowpass Filter"));
	filterMenu->Append(MENU_FILTER_HP, _T("&Highpass Filter\tAlt-H"), _T("Highpass Filter"));

	// Lab 2
	// Add Non-Linear Filters
	NonLinMenu->Append(MENU_FILTER_NONLINEAR_MEDIAN, _T("&Median Filter\tAlt-M"), _T("Median Filter"));
	NonLinMenu->Append(MENU_FILTER_NONLINEAR_MINIMUM, _T("&Minimum Filter\tAlt-K"), _T("Minimum Filter"));
	NonLinMenu->Append(MENU_FILTER_NONLINEAR_MAXIMUM, _T("&Maximum Filter\tAlt-J"), _T("Maximum Filter"));
	//Add Filter submenus to Image Processing Menu
	image_processMenu->Append(MENU_FILTER,_T("&Linear Filters"),filterMenu, _T("Filter Menu"));
	// Add Non-Linear Filter Menu to Filter Menu
	image_processMenu->Append(MENU_FILTER,_T("&Non-Linear Filters"),NonLinMenu, _T("Non-Linear Filters"));

	// Lab 3
	image_processMenu->Append(MENU_FILTER_EDGE, _T("&Edge Detection\tAlt-E"), _T("Edge Detection"));
	// Lab 3/4
	image_processMenu->Append(MENU_FILTER_BINARIZE,_T("Binarize\tAlt-B"),_T("Binarize"));


	// Lab 5
	image_processMenu->Append(ID_AreaCalculation, _T("&Area Calculation\tAlt-A"),_T("Apply Area Calculation"));

	// Lab 5 Area
	pointNumber = 99;
	areaborder = new wxPoint[pointNumber];
	areaindex=0;
	bAreaCalculation = FALSE;
	bleftDown = FALSE;
	dist = 9999;

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _T("&File"));
    menuBar->Append(image_processMenu, _T("&Image Process"));
    menuBar->Append(helpMenu, _T("&Help"));


    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_TOOLBAR
    wxToolBar *MyToolBar = new wxToolBar(this, wxID_ANY);

    MyToolBar->AddTool(MENU_FILTER_LP,lp_xpm, _T("Low Pass Filter"));
	MyToolBar->AddTool(MENU_FILTER_HP,hp_xpm, _T("High Pass Filter"));

	// Lab 2 Place Holders - Icons to be added later
	MyToolBar->AddTool(MENU_FILTER_NONLINEAR_MEDIAN,median_xpm, _T("Median Filter"));
	MyToolBar->AddTool(MENU_FILTER_NONLINEAR_MINIMUM,min_xpm, _T("Minimum Filter"));
	MyToolBar->AddTool(MENU_FILTER_NONLINEAR_MAXIMUM,max_xpm, _T("Maximum Filter"));

	// Lab 3 Place Holders - Icons to be added later
	MyToolBar->AddTool(MENU_FILTER_EDGE,edge_xpm, _T("Edge Detector"));
	MyToolBar->AddTool(MENU_FILTER_BINARIZE,binary_xpm, _T("Binarize"));

	// Lab 5 Place Holders - Icons to be added later
	MyToolBar->AddTool(ID_AreaCalculation,area_xpm,_T("Apply Area Calculation"));

	MyToolBar->AddTool(MENU_FILTER_UNDO,undo_xpm,_T("Undo"));

    MyToolBar->Realize();
    SetToolBar(MyToolBar);

#endif

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText(_T("Welcome to BME 465!"));
#endif // wxUSE_STATUSBAR

    pImage = NULL;

	// Lab 4  set the slider stuff to be empty
	sliderFrame = NULL;
	slider = NULL;

}

// Lab 4: slider frame constructor
void MyFrame::makeSlider( int sID, int deflt, int low, int high){
	if (sliderFrame != NULL){
		delete slider ;
		delete sliderFrame ;
	}
	sliderID = sID;
	sliderFrame = new MySliderFrame(_T("Slider"),wxPoint(10, 10), wxSize (200, 200));
	sliderFrame->MySliderSetParent(this);
	slider = new wxSlider(sliderFrame, SLIDER_ID, deflt, low, high, wxDefaultPosition, wxSize(160, wxDefaultCoord),wxSL_AUTOTICKS | wxSL_LABELS);
	sliderValue = slider->GetValue();
	sliderFrame->Show(TRUE);
}
void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // TRUE is to force the frame to close
    Close(TRUE);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg.Printf( _T("This is the About dialog for BME 465.\n")
                _T("Welcome to %s"), wxVERSION_STRING);

    wxMessageBox(msg, _T("About BME 465"), wxOK | wxICON_INFORMATION,this);
}
void MyFrame::OnLoad(wxCommandEvent& WXUNUSED(event))
{

    wxString fileName;
    wxString NameofFile;

    wxFileDialog fileDialog(NULL, "Choose a file to load ...", "", "", "*.bmp;*.tif;*.gif;*.jpg", wxFD_OPEN, wxDefaultPosition);
    if( fileDialog.ShowModal() == wxID_OK )

    {
        fileName = fileDialog.GetPath();
        NameofFile = fileDialog.GetFilename();
        //Update the view of main frame
        if( pImage != NULL ) delete pImage;
        pImage = new wxImage(fileName);

        if( pImage == NULL )
            wxMessageBox("File Failed to Open!", _T("Error"), wxOK | wxICON_INFORMATION, this);
        else
        {
		masterImage = pImage;
		SetTitle(fileName);
		Refresh();
        }
    }
    fileDialog.Destroy();
}

void MyFrame::OnToGray(wxCommandEvent& event)
{
    if( pImage == NULL )
    {
        wxMessageBox("Image is not loaded yet!", _T("Error"), wxOK | wxICON_INFORMATION, this);
        return;
    }

    int* buffer;
    buffer = new int[ pImage->GetWidth()*pImage->GetHeight() ];
    wxImage2grayBuffer(pImage,buffer);

    wxImage* temp;
    temp = grayBuffer2wxImage(buffer, pImage->GetWidth(),pImage->GetHeight() );
    delete pImage;
    pImage = temp;
    delete buffer;

    Refresh();
    return;
}

void MyFrame::OnPaint(wxPaintEvent& event)
{

    wxPaintDC dc(this);
	int spacingW = 0;
	int spacingH = 0;

    if( pImage == NULL ){
        event.Skip();
    }
    else{
        wxBitmap tempBitmap(*pImage);
        SetClientSize( tempBitmap.GetWidth()*1.25, tempBitmap.GetHeight()*1.25+10 );
		spacingW = ceilf((tempBitmap.GetWidth()*1.25 - tempBitmap.GetWidth())/2);
		spacingH = ceilf((tempBitmap.GetHeight()*1.25 - tempBitmap.GetHeight())/2);
        dc.DrawBitmap(tempBitmap,(int)spacingW,(int)spacingH+25, TRUE);
    }
	// Lab 5 Area
	if(bleftDown)
		pointNumber = areaindex;
	else if(dist>=0 && dist<5){
		pointNumber = areaindex;
		int idist = (int)(floor(dist));
		SetStatusText( wxString::Format("The Distance is %d", idist),0);
	}
	// Lab 5 Area
	if((areaindex >0) && (areaindex <=pointNumber))//If in area calculation mode
	{
		//wxPoint pt(even, GetLogicalPosition(dc));
		wxPoint* acborder_pt=new wxPoint[pointNumber]; //the pointd coord to be drawn
		for(int i= 0; i<areaindex;i++)
		{
			acborder_pt[i].x=dc.LogicalToDeviceX(areaborder[i].x);
			acborder_pt[i].y=dc.LogicalToDeviceY(areaborder[i].y);
		}
		dc.SetPen(*wxRED_PEN);
		//dc.DrawLine(pt.x, pt.y, acborder_pt[areaindex].x, acborder_pt[areaindex].y);
		dc.DrawLines(areaindex, acborder_pt);
		if(areaindex == pointNumber)
		{
			dc.DrawLine( acborder_pt[pointNumber-1].x, acborder_pt[pointNumber-1].y, acborder_pt[0].x, acborder_pt[0].y);
			float farea = 0;
			int area;
			int minborder = 9999;
			for(int i=0; i<pointNumber;i++){
				if(areaborder[i].x< minborder)
					minborder = areaborder[i].x;
			}
			for (int j=0; j<pointNumber - 1; j++){
				farea = ((float)((areaborder[j].x-minborder)+(areaborder[j+1].x - minborder))/2.0)*(areaborder[j+1].y-areaborder[j].y)+farea;
			}
			farea=((float)((areaborder[pointNumber-1].x-minborder)+(areaborder[0].x - minborder))/2.0)*(areaborder[0].y-areaborder[pointNumber-1].y)+farea;
			if(farea<0) farea = -farea;
			area = (int)farea;
			SetStatusText( wxString::Format("The Area is %d", area), 1);

			areaindex = 0;
			bleftDown = !bleftDown;
			bRed = FALSE;
			pointNumber = 99;
			dist = 9999;
		}
		delete acborder_pt;
	}
    return;
}

void MyFrame::OnFilter( wxCommandEvent& event )
{
        if( pImage == NULL )
        {
            wxMessageBox("Image is not loaded yet!", _T("Error"), wxOK | wxICON_INFORMATION,this);
        }
        else
        {
            wxImage *Filtered = NULL;

            switch(event.GetId())
            {
               case MENU_FILTER_LP: Filtered = LowPass(pImage); break;
			   case MENU_FILTER_HP: Filtered = HighPass(pImage); break;
			   case MENU_FILTER_NONLINEAR_MEDIAN: Filtered = NonLinear(pImage, MEDIAN); break;
			   case MENU_FILTER_NONLINEAR_MINIMUM: Filtered = NonLinear(pImage, MINIMUM); break;
			   case MENU_FILTER_NONLINEAR_MAXIMUM: Filtered = NonLinear(pImage,MAXIMUM); break;
			   case MENU_FILTER_EDGE: Filtered = Edge(pImage); break;
			   case MENU_FILTER_UNDO: Filtered = copy(masterImage); break;
			   //Lab 4
			   case MENU_FILTER_BINARIZE:{
									   makeSlider(BIN_SLIDER, 128,0,255);
									   Filtered = Binarize(masterImage,sliderValue );}
									   break;
			}

            pImage = Filtered;
         }
    Refresh();
    return;
}

//Lab 4
void MyFrame::sliderHandler(){
	sliderValue = slider->GetValue();
	switch(sliderID){
		case BIN_SLIDER: pImage = Binarize(masterImage, sliderValue); break;
	}
	Refresh();
}

// Lab 4
void MyFrame::sliderWindowCloses(void){
	sliderFrame = NULL;
	slider = NULL;
}

// Lab 5
void MyFrame::OnAreaCalculation( wxCommandEvent& WXUNUSED(even))
{
	bAreaCalculation = !bAreaCalculation;
	if( bAreaCalculation)
		SetStatusText("In Area", 1);
	else
		SetStatusText("Out of Area", 1);
	Refresh();
	return;
}

// Lab 5
void MyFrame::OnLButton( wxMouseEvent& event)
{
	wxClientDC dc(this);
	wxPoint area_pt(event.GetLogicalPosition(dc));

	SetStatusText( wxString::Format("(%d,%d)", area_pt.x,area_pt.y), 0);

	if(!bAreaCalculation)
		return;
	if( pImage == NULL)
	{
		wxMessageBox("Image is not loaded yet!", _T("Error"), wxOK | wxICON_INFORMATION, this);
		return;
	}
	areaborder[areaindex].x= area_pt.x;
	areaborder[areaindex].y= area_pt.y+27;
	if (areaindex>0)
		dist = sqrt((pow((double)(area_pt.x-areaborder[0].x),2)+pow((double)(area_pt.y+27-areaborder[0].y),2)));
	SetStatusText( wxString::Format("(%d,%d,%d)", area_pt.x, area_pt.y, (int)dist), 1);
	areaindex++;
	Refresh();
}

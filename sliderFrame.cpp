// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include "sliderFrame.hpp"
#include "BME465_FinalProject_TextDetectionApp.h"
#include "BME465_FinalProject_TextDetectionMain.h"

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

#include <iostream>
using namespace std;

#define MENU_FILTER_BINARIZE 5000

BEGIN_EVENT_TABLE(MySliderFrame, wxFrame)
	EVT_SLIDER(SLIDER_ID, MySliderFrame::OnSliderUpdate)
END_EVENT_TABLE()


MySliderFrame::
MySliderFrame(const wxString& title, const wxPoint& pos, const wxSize& size, long style)
: wxFrame(NULL, -1, title, pos, size, style) {
	binarize = new wxCheckBox(this, MENU_FILTER_BINARIZE, wxString("Check box "), wxPoint(5,40));
	binarize->Show(true);
	SetIcon(wxICON(myIcon));
}

MySliderFrame::~MySliderFrame() {
	((MyFrame *)parent)->sliderWindowCloses();
}

void MySliderFrame::MySliderSetParent(wxFrame *parent) {
	this->parent = parent;
}

void MySliderFrame::OnSliderUpdate( wxCommandEvent& event ) {
	((MyFrame *)parent)->sliderHandler();
	if (binarize->GetValue())
		cout << "checked\n";
}


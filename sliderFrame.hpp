#ifndef __SLIDER_FRAME_INCLUDE__
#define __SLIDER_FRAME_INCLUDE__
// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifdef __BORLANDC__
    #pragma hdrstop
#endif


// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers)

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/splitter.h"
#include "wx/toolbar.h"
#include "wx/utils.h"
#include "wx/image.h"
#include "wx/filedlg.h"
#include "wx/pen.h"
#include "math.h"
#include "image_processor.hpp"


class MySliderFrame : public wxFrame {

public:
    // constructors
    MySliderFrame(const wxString& title, const wxPoint& pos, const wxSize& size,
            	  long style = wxDEFAULT_FRAME_STYLE);
	~MySliderFrame();
	wxCheckBox *binarize;
	void MySliderSetParent(wxFrame *parent);
	void OnSliderUpdate( wxCommandEvent& event );

private:
	wxFrame *parent;
	int	sliderID;
	DECLARE_EVENT_TABLE()
};


#endif		//-> __SLIDER_FRAME_INCLUDE__

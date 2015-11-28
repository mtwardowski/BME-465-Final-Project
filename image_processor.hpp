// Image_processer.hpp

#ifndef IMAGE_PROCESSOR_HPP
#define IMAGE_PROCESSOR_HPP

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <vector>
#include "wx/image.h"

//Text Detection
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

//Text Detection
using namespace cv;
using namespace std;

enum
{
	MEDIAN = 104,
	MINIMUM = 105,
	MAXIMUM = 106,
};

// Definitions of the routines
void wxImage2grayBuffer(const wxImage* img, int* buffer);
wxImage* grayBuffer2wxImage(const int* buffer, int width, int height);
void wxImage2colorBuffer(const wxImage* img, int* buffer);
wxImage* colorBuffer2wxImage(const int* buffer, int width, int height);
wxImage* LowPass(wxImage *pImage);
wxImage* HighPass(wxImage *pImage);
wxImage* NonLinear(wxImage *pImage, int type);
wxImage* copy(wxImage *masterImage);
wxImage* Edge(wxImage *pImage);
wxImage* Binarize(wxImage*pImage, int threshold);

// Text Detection
wxImage* TextDetection(wxImage* pImage);
vector<Rect> detectLetters(Mat cvImg);

#endif

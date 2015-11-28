// This file provides the basic routines for image processing

#include "image_processor.hpp"
#include "BME465_FinalProject_TextDetectionApp.h"
#include "BME465_FinalProject_TextDetectionMain.h"

#include <vector> //FOR MEDIAN FILTER
#include <algorithm> //FOR SORT()

//Text Detection
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

//Text Detection
using namespace cv;
using namespace std;

// Implementation of the routines
void wxImage2grayBuffer(const wxImage* img, int* buffer)
{
    unsigned long pix_index = 0, byte_index=0;
    unsigned long buffer_len;
    unsigned char* img_buffer;

    buffer_len = img->GetWidth()* img->GetHeight();
    img_buffer = img->GetData();

    for( pix_index=0, byte_index=0; pix_index<buffer_len; pix_index++ )
    {
        int sum = 0;
        sum = img_buffer[byte_index++];
        sum += img_buffer[byte_index++];
        sum += img_buffer[byte_index++];

        buffer[pix_index] = sum/3;
    }

    return;
} // end of wxImage2grayBuffer(...)

wxImage* grayBuffer2wxImage(const int* buffer, int width, int height)
{
    unsigned long pix_index = 0, byte_index=0;
    unsigned long buffer_len;
    unsigned char* img_buffer;

    wxImage* img = new wxImage(width,height);
    buffer_len = width*height;
    img_buffer = new unsigned char[width*height*3];

    for( pix_index=0, byte_index=0; pix_index<buffer_len; pix_index++ )
    {
        img_buffer[byte_index++] = (unsigned char)buffer[pix_index];
        img_buffer[byte_index++] = (unsigned char)buffer[pix_index];
        img_buffer[byte_index++] = (unsigned char)buffer[pix_index];
    }

    img->SetData(img_buffer);

    return img;
} // end of grayBuffer2wxImage(...)
wxImage* colorBuffer2wxImage(const int* buffer, int width, int height)
{
    unsigned long pix_index = 0, byte_index=0;
    unsigned long buffer_len;
    unsigned char* img_buffer;
	double PI = 3.1415;

    wxImage* img = new wxImage(width,height);
    buffer_len = width*height;
    img_buffer = new unsigned char[width*height*3];

    for( pix_index=0, byte_index=0; pix_index<buffer_len; pix_index++ )
    {
        if(buffer[pix_index] > 0)
        {
                img_buffer[byte_index++] = 255-(unsigned char)(buffer[pix_index]*255/PI);
                img_buffer[byte_index++] = (unsigned char)(0);
                img_buffer[byte_index++] = 255-(unsigned char)(buffer[pix_index]*255/PI);
        }
        if(buffer[pix_index] < 0)
        {
                img_buffer[byte_index++] = (unsigned char)(0);
                img_buffer[byte_index++] = (unsigned char)(buffer[pix_index]*255/PI);
                img_buffer[byte_index++] = (unsigned char)(0);
        }
        if(buffer[pix_index] == 0)
        {
                img_buffer[byte_index++] = (unsigned char)(0);
                img_buffer[byte_index++] = (unsigned char)(0);
                img_buffer[byte_index++] = (unsigned char)(0);
        }


    }

    img->SetData(img_buffer);

    return img;
} // end of grayBuffer2wxImage(...)


void wxImage2colorBuffer(const wxImage* img, int* buffer)
{
    unsigned long pix_index = 0, byte_index=0;
    unsigned long buffer_len;
    unsigned char* img_buffer;

	double PI = 3.1415;
    buffer_len = img->GetWidth()* img->GetHeight();
    img_buffer = img->GetData();

    for( pix_index=0, byte_index=0; pix_index<buffer_len; pix_index++ )
    {
        int sum = 0;
        sum = img_buffer[byte_index++]*255/PI;
        sum += img_buffer[byte_index++]*255/PI;
        sum += img_buffer[byte_index++]*255/PI;

        buffer[pix_index] = 255-sum/3;
    }

    return;
}

wxImage * LowPass(wxImage *pImage)
{
    int x,y;
    int height = pImage->GetHeight();
    int width = pImage->GetWidth();
    int* pTemp;
    int* pResult;

    pTemp=new int[width*height];
    pResult=new int[width*height];
    wxImage2grayBuffer(pImage,pTemp);

    for(x=0;x<width;x++)
    {
    	for(y=0;y<height;y++)
    	{
            if(x != 0 && y != 0 && x != (width -1) && y != (height -1))
            {
    		    unsigned long index;
        		index=(unsigned long)y*width+x;
        		double value=1.0/9.0*
        			( float(pTemp[index-width-1])+float(pTemp[index-width])+float(pTemp[index-width+1])
        			 +float(pTemp[index-1])+float(pTemp[index])+float(pTemp[index+1])
        			 +float(pTemp[index+width-1])+float(pTemp[index+width])+float(pTemp[index+width+1])
        			);
        		pResult[(y)*width+(x)]=(int)(value);
   		    }
   		    else
   		    {
                pResult[y*width+x]=pTemp[y*width+x];
            }
    	}
    }

    wxImage* temp;
    temp = grayBuffer2wxImage( pResult, width,height );
    delete pResult;
    return temp;
}


wxImage * HighPass(wxImage *pImage)
{
    int x,y;
    int height = pImage->GetHeight();
    int width = pImage->GetWidth();
    int* pTemp;
    int* pResult;

    pTemp=new int[width*height];
    pResult=new int[width*height];
    wxImage2grayBuffer(pImage,pTemp);

    for(x=0;x<width;x++)
    {
    	for(y=0;y<height;y++)
    	{
            if(x != 0 && y != 0 && x != (width -1) && y != (height -1))
            {
    		    unsigned long index;
        		index=(unsigned long)y*width+x;
        		double value=1.0/9.0*
        			( float(pTemp[index-width-1])+float(pTemp[index-width])+float(pTemp[index-width+1])
        			 +float(pTemp[index-1])+float(pTemp[index])+float(pTemp[index+1])
        			 +float(pTemp[index+width-1])+float(pTemp[index+width])+float(pTemp[index+width+1])
        			);
					value = 2 * float(pTemp[index])- value;
					if (value>255)
						value = 255;
					else if (value < 0)
						value = 0;

        		pResult[(y)*width+(x)]=(int)(value);
   		    }
   		    else
   		    {
                pResult[y*width+x]=pTemp[y*width+x];
            }
    	}
    }

    wxImage* temp;
    temp = grayBuffer2wxImage( pResult, width,height );
    delete pResult;
    return temp;
}

// Lab 2 Non-LinearFilters
wxImage * NonLinear(wxImage *pImage, int type)
{
	int x,y;
    int height = pImage->GetHeight();
    int width = pImage->GetWidth();
    int* pTemp;
    int* pResult;

    pTemp=new int[width*height];
    pResult=new int[width*height];
    wxImage2grayBuffer(pImage,pTemp);

	std::vector<int> valArray ( 9 );
	double value ;
	for (x = 0; x < width; x++){
		for (y = 0; y < height; y++) {
			unsigned long index ;
			index = (unsigned long) (y * width + x ) ;
			if (y!=0 && x!=0 && x!= (width -1) && y !=(height-1) ) {
				valArray[0] = pTemp [ index - width - 1 ] ;
				valArray[ 1 ] = pTemp [ index - width ] ;
				valArray[ 2 ] = pTemp [ index - width + 1 ] ;
				valArray[ 3 ] = pTemp [ index - 1 ] ;
				valArray[ 4 ] = pTemp [ index ] ;
				valArray[ 5 ] = pTemp [ index + 1 ] ;
				valArray[ 6 ] = pTemp [ index + width - 1 ] ;
				valArray[ 7 ] = pTemp [ index + width ] ;
				valArray[ 8 ] = pTemp [ index + width + 1 ] ;
				sort ( valArray . begin ( ) , valArray . end ( ) ) ;
				switch ( type ) {
					case MEDIAN : value = valArray [ 4 ] ; break ;
					case MINIMUM : value = valArray [ 0 ] ; break ;
					case MAXIMUM : value = valArray [ 8 ] ; break ;
				}
				if ( value > 255)
					value = 255 ;
				else if ( value < 0)
					value = 0 ;
				pResult [ index ] = ( int ) value ;
			}
			else {
				pResult [ index ] = pTemp [ index ] ;
			}
		}
	}
	wxImage* temp;
    temp = grayBuffer2wxImage( pResult, width,height );
    delete pResult;
    return temp;
}
wxImage *copy(wxImage *masterImage) {
    int x,y;
	int height = masterImage->GetHeight();
	int width = masterImage->GetWidth();
	int* pTemp;
	int* pResult;

    pTemp=new int [width*height];
	pResult=new int[width*height];

    wxImage2grayBuffer(masterImage, pTemp);

	for(x=0;x<width;x++) {
		for(y=0;y<height;y++) {
			unsigned long index;
    		index=(unsigned long)y*width+x;
			pResult[index] = pTemp[index];
		}
	}

	wxImage* temp;
    temp = grayBuffer2wxImage( pResult, width,height );
    delete pResult;
    return temp;
}

wxImage *Edge(wxImage *pImage) {
	int x,y;
    int height = pImage->GetHeight();
    int width = pImage->GetWidth();
    int* pTemp;
    int* pResult;

    pTemp=new int[width*height];
    pResult=new int[width*height];
    wxImage2grayBuffer(pImage,pTemp);
	for ( x=0;x<width ; x++)
	{
		for ( y=0;y<height ; y++)
		{
			if ( y!=0 && x!=0 && x!= ( width - 1) && y!=( height-1) )
			{
				unsigned long index ;
				index=(unsigned long ) y*width+x ;
				double value=
				( abs ( pTemp [ index - width - 1]*(-1) + pTemp [ index - width+1] +
				pTemp [ index - 1]*(-2) + pTemp [ index + 1]*2 + pTemp [ index+width-1]*(-1)+pTemp [ index + width+1])+
				abs(pTemp [ index - width - 1]*(-1)+pTemp [ index - width ]*(-2) + pTemp [ index - width+1]*(-1)+pTemp
				[ index+width- 1]+pTemp [ index+width ]*2+pTemp [ index + width+1])
				);
				if ( value<0)
					value=0;
				if ( value>255)
					value=64;
				pResult [ y*width+x]=( int ) value ;
			}
			else
			{
				pResult [ y*width+x]=pTemp [ y*width+x ] ;
			}
		}
	}
	wxImage* temp;
	temp = grayBuffer2wxImage( pResult, width,height );
	delete pResult;
	return temp;
}
// Lab 4
wxImage *Binarize(wxImage *pImage, int threshold){

	int x,y;
    int height = pImage->GetHeight();
    int width = pImage->GetWidth();
    int* pTemp;
    int* pResult;

    pTemp=new int[width*height];
    pResult=new int[width*height];
    wxImage2grayBuffer(pImage,pTemp);
	for ( x=0;x<width ; x++)
	{
		for ( y=0;y<height ; y++)
		{
			unsigned long index ;
			index=y*width+x ;

			pResult [index]= (pTemp[index] >= threshold) ? 255:0;
		}
	}
	wxImage* temp;
	temp = grayBuffer2wxImage( pResult, width,height );
	delete pResult;
	return temp;
}

wxImage* TextDetection(wxImage* pImage)
{
    int* pResult;

    // Converts wxImage to cvImage
    int w = pImage->GetWidth();
    int h = pImage->GetHeight();
    int mapping[] = {0,2,1,1,2,0}; // WX(RGB) to CV(BGR)
    Mat cvRGBImg(h, w, CV_8UC3, pImage->GetData());
    Mat cvImg = Mat(h, w, CV_8UC3);
    mixChannels(&cvRGBImg, 1, &cvImg, 1, mapping, 3);

    //Detect text areas
    vector<Rect> letterBBoxes1=detectLetters(cvImg);

    //Creates new image with rectangles around text
    for(int i=0; i< letterBBoxes1.size(); i++)
        rectangle(cvImg,letterBBoxes1[i],Scalar(0,255,0),3,8,0);
    imwrite( "imgOut1.jpg", cvImg); // confirm conversion to cvImage

    // Convert cvImg to wxImage
    wxImage* temp = new wxImage(w,h,cvImg.data);
    temp->SaveFile(wxT("raw.jpg"),wxBITMAP_TYPE_JPEG); // confirms conversion to wximage
    //return temp;
}

vector<Rect> detectLetters(Mat cvImg)
{
vector<Rect> boundRect;
    Mat img_gray, img_sobel, img_threshold, element;
    cvtColor(cvImg, img_gray, CV_BGR2GRAY);
    Sobel(img_gray, img_sobel, CV_8U, 1, 0, 3, 1, 0, BORDER_DEFAULT);
    threshold(img_sobel, img_threshold, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
    element = getStructuringElement(MORPH_RECT, Size(17, 3) );
    morphologyEx(img_threshold, img_threshold, CV_MOP_CLOSE, element); //Does the trick
    vector<vector<Point> > contours;
    findContours(img_threshold, contours, 0, 1);
    vector<vector<Point> > contours_poly( contours.size() );
    for( int i = 0; i < contours.size(); i++ )
        if (contours[i].size()>100)
        {
            approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true );
            Rect appRect( boundingRect(Mat(contours_poly[i]) ));
            if (appRect.width>appRect.height)
                boundRect.push_back(appRect);
        }
    return boundRect;
}

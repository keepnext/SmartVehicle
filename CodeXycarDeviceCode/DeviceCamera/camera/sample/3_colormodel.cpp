#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main()
{			
	Mat img_color;
	Mat imgbufgray;
	Mat imgbufhls;
	Mat imgbufch[3];

	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cerr << "error cam";
		return -1;
	}

	
	while(1)
	{
		cap.read(img_color);
		if (img_color.empty()) {
			cerr << "capt empty";
			break;
		}
		
		cvtColor(img_color, imgbufgray, COLOR_BGR2GRAY);
		cvtColor(img_color, imgbufhls, COLOR_BGR2HLS);
		
		split(img_color, imgbufch);
		
		imshow("src", img_color);
		
		imshow("gray", imgbufgray);
		imshow("hls", imgbufhls);
		
		imshow("chB", imgbufch[0]);		
		imshow("chG", imgbufch[1]);		
		imshow("chR", imgbufch[2]);	
			
		
		
		if (waitKey(25) >= 0)
			break;
	}
	

	return 0;
}

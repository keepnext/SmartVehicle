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
	Mat imgbuf;

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
		
		flip(img_color, imgbuf, 0);
		transpose(img_color, imgbuf);
		
		imshow("src", img_color);
		imshow("buf", imgbuf);		
		
		
		if (waitKey(25) >= 0)
			break;
	}
	

	return 0;
}

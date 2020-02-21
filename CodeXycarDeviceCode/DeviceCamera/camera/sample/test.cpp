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

	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cerr << "error cam";
		return -1;
	}

	int iCount = 0;
	
	Mat preimage;
	Mat resimage;
	
	while(1)
	{
		cap.read(img_color);
		if (img_color.empty()) {
			cerr << "capt empty";
			break;
		}
		
		imshow("Color", img_color);
		
		if(iCount == 120)
		{
			preimage = img_color.clone();
		}
		else if(iCount == 240)
		{
			resimage = img_color - preimage;
			
			absdiff(preimage, img_color,resimage); 
		}
		iCount++;

		if (resimage.empty()) {
		}		
		else
		{
			imshow("res", resimage);
		}
		
		if (waitKey(25) >= 0)
			break;
	}
	

	return 0;
}

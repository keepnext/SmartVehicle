#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main()
{			
	Mat img_color;
	Mat img_colorgray;
	Mat imgresult;
	Mat imgCircle;
	imgCircle.create(480, 640, CV_8UC3);
	imgCircle.setTo(Scalar(0,0,0));
	
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cerr << "error cam";
		return -1;
	}
	double fps = cap.get(CAP_PROP_FPS);
	printf("fps:%.02lf\n", fps);
	while(1)
	{
		cap.read(img_color);
		if (img_color.empty()) {
			cerr << "capt empty";
			break;
		}
		
		circle(imgCircle, Point(50,50), 50, Scalar(1,1,1),-1);
		cvtColor(img_color, img_colorgray, COLOR_BGR2GRAY);
		multiply(img_color, imgCircle, imgresult);
		
		imshow("src", img_color);
		imshow("dst", imgresult);
		imshow("1", imgCircle);
		
		int c = waitKey(25);
		if (c >= 0)
		{
			printf("key = %d\n", c);
			if(c == 27) // esc
			{
				break;
			}
		}
	}
	

	return 0;
}

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
	Mat imgFirst;
	Mat imgFirstgray;
	Mat imgresult;
	bool bSetFirst = false;

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
		if(bSetFirst == false)
		{
			imgFirst = img_color.clone();
			cvtColor(imgFirst, imgFirstgray, COLOR_BGR2GRAY);
			bSetFirst = true;
		}
		
		cvtColor(img_color, img_colorgray, COLOR_BGR2GRAY);
		subtract(img_colorgray, imgFirstgray, imgresult);
		//absdiff(imgFirstgray, img_colorgray, imgresult);
		imshow("src", img_color);
		imshow("dst", imgresult);
		imshow("1", imgFirstgray);
		imshow("2", img_colorgray);
		int c = waitKey(25);
		if (c >= 0)
		{
			printf("key = %d\n", c);
			if(c == 's')
			{
				bSetFirst = false;
			}
			else if(c == 27) // esc
			{
				break;
			}
		}
	}
	

	return 0;
}

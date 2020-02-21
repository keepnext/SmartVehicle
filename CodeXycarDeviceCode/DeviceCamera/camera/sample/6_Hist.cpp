#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void calc_histo(Mat image, Mat &hist, int bins, int range_max = 256)
{
	hist = Mat(bins, 1, CV_32F, Scalar(0));
	float gap = range_max / (float)bins;

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++)
		{
			int idx = int(image.at<uchar>(i, j) / gap);
			hist.at<float>(idx)++;
		}
	}
}

void  calc_Histo(const Mat& image, Mat& hist, int bins, int range_max = 256)
{
	int		histSize[] = { bins };					
	float   range[] = { 0, (float)range_max };		
	int		channels[] = { 0 };						
	const float* ranges[] = { range };

	calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
}


void draw_histo(Mat hist, Mat &hist_img, Size size = Size(256, 200))
{
	hist_img = Mat(size, CV_8U, Scalar(255));
	float  bin = (float)hist_img.cols / hist.rows;
	normalize(hist, hist, 0, size.height, NORM_MINMAX);

	for (int i = 0; i<hist.rows; i++)
	{
		float  start_x = (i * bin);
		float  end_x = (i + 1) * bin;
		Point2f pt1(start_x, 0);
		Point2f pt2(end_x, hist.at <float>(i));

		if (pt2.y > 0)
			rectangle(hist_img, pt1, pt2, Scalar(0), -1);
	}
	flip(hist_img, hist_img, 0);
}


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
		//CV_Assert(!img_color.empty());

		Mat hist, hist_img;
		calc_Histo(img_color, hist, 256);
		draw_histo(hist, hist_img);
		imshow("src", img_color);
		imshow("dst", hist_img);
		
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

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

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


int search_valueIdx(Mat hist, int bias = 0)
{
	for (int i = 0; i < hist.rows; i++)
	{
		int idx = abs(bias - i);
		if (hist.at<float>(idx) > 0)	return idx;
	}
	return -1;
}


int main()
{			
	Mat img_color;
	Mat img_colorgray;
	
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

		Mat img_color_gray;
		cvtColor(img_color, img_color_gray, CV_BGR2GRAY);
		Mat hist, hist_dst, hist_img, hist_dst_img;
		int  histsize = 64, ranges = 256;
		calc_Histo(img_color_gray, hist, histsize, ranges);

		float bin_width = (float)ranges / histsize;
		int low_value   = (int)(search_valueIdx(hist, 0) * bin_width);
		int high_value  = (int)(search_valueIdx(hist, hist.rows)* bin_width);
		cout << "high_value = " << high_value << endl;
		cout << "low_value = " << low_value << endl;

		int d_value = high_value - low_value;				 
		Mat  dst = (img_color_gray - low_value) * (255.0 / d_value);

		calc_Histo(dst, hist_dst, histsize, ranges);
		draw_histo(hist, hist_img);
		draw_histo(hist_dst, hist_dst_img);
	
	
		imshow("src", img_color);
		imshow("dst-stretching", dst);
		imshow("img_hist", hist_img);
		imshow("dst_hist", hist_dst_img);
			
		int c = waitKey(0);
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

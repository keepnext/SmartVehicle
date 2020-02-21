#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("images/road3.jpg", IMREAD_COLOR);		// 명암도 영상 읽기
	CV_Assert(!image.empty());									// 영상파일 예외처리

	
	Mat imgproc = image.clone();
	Mat lineROI = imgproc(Rect(0, imgproc.rows/2, 
	              imgproc.cols, imgproc.rows/2)).clone();
				  
	Mat lineProc = 
	           Mat::zeros(lineROI.rows, lineROI.cols,
                    	  CV_8UC3);
						  
	Mat grayImg;
	cvtColor (lineROI, grayImg, COLOR_BGR2GRAY);
	
	Mat cannyImg;
	Mat thImg;
	
	threshold(grayImg, thImg, 100, 255, THRESH_BINARY);
	
	Canny(grayImg, cannyImg, 100, 150, 3);
	
	vector<Vec2f> lines;
	
	int threshold = 70;
	
	HoughLines(cannyImg, lines, 1,
            	CV_PI / 180, threshold);
	
	float theta_min = 40.0f * CV_PI/180.0f;
	float theta_max = 60.0f * CV_PI/180.0f;
	float theta_min2 = 110.0f * CV_PI/180.0f;
	float theta_max2 = 140.0f * CV_PI/180.0f;	
	
	
	for (int i = 0; i < lines.size(); i++)
	{		
		float rho = lines[i][0], theta = lines[i][1];
		
		Scalar color;
		bool bSearch = false;
		if(theta > theta_min && theta < theta_max)
		{
			color = Scalar(255,0,0);
			bSearch = true;
		}		
		if(theta > theta_min2 && theta < theta_max2)
		{
			color = Scalar(0,0,255);
			bSearch = true;
		}
		if(bSearch == true)
		{
			Point pt1(0, rho/sin(theta));
			Point pt2(cannyImg.cols,
			(rho - cannyImg.cols*cos(theta)/ sin(theta)));			
			line(lineProc, pt1, pt2, color, 1);
		}
	}
	
	imshow("gray", grayImg);
	imshow("canny", cannyImg);
	imshow("th", thImg);
	imshow("line", lineProc);
	
	
	

	waitKey();
	return 0;
}
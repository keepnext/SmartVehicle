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
	

	Mat cannyColor;
	Mat ROITest = lineROI.clone();
	cvtColor(cannyImg, cannyColor, COLOR_GRAY2BGR);
	ROITest = ROITest - cannyColor;
	imshow("ROI CHECK", ROITest);


	



	Point leftP[2], rightP[2], banishP;
	bool bLFound = false, bRFound = false;
	
	for (int i = 0; i < lines.size(); i++)
	{		
		float rho = lines[i][0], theta = lines[i][1];
		
		Scalar color = Scalar(0,0,255);
		bool bSearch = false;


		//Point pt11(0, rho / sin(theta)); 
		//Point pt21(ROITest.cols, (rho - ROITest.cols*cos(theta)) / sin(theta));
		//line(ROITest, pt11, pt21, color, 1);

		//Point pt11(0, rho/sin(theta));
		//Point pt21(cannyImg.cols,
		//(rho - cannyImg.cols*cos(theta)/ sin(theta)));			
		//line(lineROI, pt11, pt21, color, 1);


		if(theta > theta_min && theta < theta_max
		   && bLFound == false)
		{
			color = Scalar(255,0,0);
			bSearch = true;
			bLFound = true;
			
			Point pt1(0, rho/sin(theta));
			Point pt2(cannyImg.cols,
			(rho - cannyImg.cols*cos(theta))/ sin(theta));			
			line(lineProc, pt1, pt2, color, 4);
			leftP[0] = pt1;
			leftP[1] = pt2;

			Point pt11(0, rho / sin(theta)); 
			Point pt21(ROITest.cols, (rho - ROITest.cols*cos(theta)) / sin(theta));
			line(ROITest, pt11, pt21, color, 1);

			leftP[0] = Point(pt11);
			leftP[1] = Point(pt21);
		}		
		if(theta > theta_min2 && theta < theta_max2
		   && bRFound == false)
		{
			color = Scalar(0,0,255);
			bSearch = true;
			bRFound = true;			
			
			Point pt1(0, rho/sin(theta));
			Point pt2(cannyImg.cols,
			(rho - cannyImg.cols*cos(theta))/ sin(theta));			
			line(lineProc, pt1, pt2, color, 4);
			
			rightP[0] = pt1;
			rightP[1] = pt2;


			Point pt11(0, rho / sin(theta)); 
			Point pt21(ROITest.cols, (rho - ROITest.cols*cos(theta)) / sin(theta));
			line(ROITest, pt11, pt21, color, 1);

			rightP[0] = Point(pt11);
			rightP[1] = Point(pt21);
		}
	}

	imshow("ROI CHECK1", ROITest);
	
	float leftLineA = (float)(leftP[1].y - leftP[0].y) / (float)(leftP[1].x - leftP[0].x);
	float leftLineB = leftP[1].y - leftLineA * leftP[1].x;

	float rightLineA = (float)(rightP[1].y - rightP[0].y) / (float)(rightP[1].x - rightP[0].x);
	float rightLineB = rightP[1].y - rightLineA * rightP[1].x;

	banishP.x = (int)((rightLineB - leftLineB) / (leftLineA - rightLineA));
	banishP.y = (int)(leftLineA * banishP.x + leftLineB);
	
	
	Scalar color = Scalar(0,255,0);
		
	lineROI = lineROI + lineProc;
	imshow("ROI CHECK2", ROITest);

	cout << banishP.x << "," << banishP.y << endl;
	int Lline, Rline;
	for (int i = banishP.x * 3; i > 0; i--)
	{
	    uchar * ptr_mat = lineProc.ptr(lineProc.rows - 50);
	    if(ptr_mat[i] > 0)
	    {
	        ptr_mat[i] = 255;
	        cout << "find l:" << i / 3 << endl;
	        cout << "diff l:" << banishP.x - (i / 3) << endl;
	        Lline = banishP.x - (i / 3);
	        cv::line(lineProc, Point(i/3, 0), Point(i/3, lineProc.rows), Scalar(255,0,0), 1);

	        break;
	    }
	}

	for (int i = banishP.x * 3; i < lineProc.cols*3; i++)
	{
	    uchar * ptr_mat = lineProc.ptr(lineProc.rows - 50);
	    if(ptr_mat[i] > 0)
	    {
	        ptr_mat[i] = 255;
	        cout << "find r:" << i / 3 << endl;
	        cout << "diff r" << (i / 3) - banishP.x << endl;
	        Rline = (i / 3) - banishP.x;
	        cv::line(lineProc, Point(i/3, 0), Point(i/3, lineProc.rows), Scalar(255,0,0), 1);
	        break;
	    }
	}

	line(lineProc, banishP, Point(banishP.x, cannyImg.rows), color, 4);
	line(ROITest, banishP, banishP, color, 4);

	cout << "diff (- L, + R)" << Rline - Lline << endl;



	
	imshow("gray", grayImg);
	imshow("canny", cannyImg);
	imshow("th", thImg);
	imshow("line", lineProc);
	imshow("ROI", lineROI);
	
	
	

	waitKey();
	return 0;
}
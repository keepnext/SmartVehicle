#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

int main()
{		
	Mat img_color;

	VideoCapture cap(0);
	double fps = cap.set(CV_CAP_PROP_FPS, 1);//set the fps of video
	cout << "fps:" << fps << endl;
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
        
		cv::Mat colorImg = img_color.clone();
		cv::Mat colorImgRoi = colorImg(cv::Rect(0, colorImg.rows / 2, colorImg.cols, colorImg.rows / 2)).clone();
		Mat colorImgRoi_line = Mat::zeros(colorImgRoi.rows, colorImgRoi.cols, CV_8UC3);
		cv::Mat grayImg;
		cvtColor(colorImg, grayImg, cv::COLOR_BGR2GRAY);
		cv::Mat imageROI = grayImg(cv::Rect(0, grayImg.rows / 2, grayImg.cols, grayImg.rows / 2)).clone();
		cv::Mat cannyImg;

		cv::threshold(imageROI, imageROI, 100, 255, THRESH_BINARY);

		Canny(imageROI, cannyImg, 100, 150, 3);

		vector<Vec2f> lines;

		int threshold = 70;
		HoughLines(cannyImg, lines, 1, CV_PI / 180, threshold);

		float theta_min = 40.0f * CV_PI/180.0f;
		float theta_max = 60.0f * CV_PI/180.0f;
		float theta_min2 = 110.0f * CV_PI/180.0f;
		float theta_max2 = 140.0f * CV_PI/180.0f;
		float theta_avr = 0.f;
		float theta_deg = 0.f;

		cout << "th min : " << theta_min << endl;
		cout << "th max : " << theta_max << endl;
		cout << "th min : " << theta_min2 << endl;
		cout << "th max : " << theta_max2 << endl;

		Point leftP[2], rightP[2], banishP;
		int L = 0, R = 0;
		for (int i = 0; i < lines.size(); i++)
		{
		    float rho = lines[i][0], theta = lines[i][1];

		    Scalar color;
		    if(theta > theta_min && theta < theta_max)
		    {
		        color = Scalar(255,0,0);
		        if(L == 0)
		        {
		            L = 1;
		        }
		    }
		    else if(theta > theta_min2 && theta < theta_max2)
		    {
		        color = Scalar(0,0,255);
		        if(R == 0)
		        {
		            R = 1;
		        }
		    }
		    else
		    {
		        continue;
		    }

		    if(rho < 0)
		    {
		        //color = Scalar(0,255,0);
		        //cout << "--i : " << i << " line: (" << rho << ", " << theta << ")\n";
		    }

		    if (theta < CV_PI / 4. || theta> 3.* CV_PI / 4.) {
		    }
		    else {
		        cv::Point pt1(0, rho / sin(theta)); 
		        cv::Point pt2(colorImgRoi.cols, (rho - colorImgRoi.cols*cos(theta)) / sin(theta));
		        cv::line(colorImgRoi, pt1, pt2, color, 1);

		        if(L == 1)
		        {
		            leftP[0] = pt1;
		            leftP[1] = pt2;
		            L = 2;
		        }

		        if(R == 1)
		        {
		            rightP[0] = pt1;
		            rightP[1] = pt2;
		            R = 2;
		        }
		    }
		    cout << "i : " << i << " line: (" << rho << ", " << theta << ")\n";
		}

		float leftLineA = (float)(leftP[1].y - leftP[0].y) / (float)(leftP[1].x - leftP[0].x);
		float leftLineB = leftP[1].y - leftLineA * leftP[1].x;

		float rightLineA = (float)(rightP[1].y - rightP[0].y) / (float)(rightP[1].x - rightP[0].x);
		float rightLineB = rightP[1].y - rightLineA * rightP[1].x;

		banishP.x = (int)((rightLineB - leftLineB) / (leftLineA - rightLineA));
		banishP.y = (int)(leftLineA * banishP.x + leftLineB);


		cv::line(colorImgRoi, banishP, leftP[0], Scalar(255,255,0), 5);
		cv::line(colorImgRoi, banishP, rightP[1], Scalar(255,255,0), 5);

		cv::line(colorImgRoi, banishP, banishP, Scalar(0,255,255), 10);

		cv::line(colorImgRoi, banishP, Point(banishP.x, colorImgRoi.rows), Scalar(0,255,0), 5);


		cv::line(colorImgRoi_line, banishP, leftP[0], Scalar(255,255,0), 5);
		cv::line(colorImgRoi_line, banishP, rightP[1], Scalar(255,255,0), 5);

		cv::line(colorImgRoi_line, banishP, banishP, Scalar(0,255,255), 10);

		cout << banishP.x << "," << banishP.y << endl;
		int Lline, Rline;
		for (int i = banishP.x * 3; i > 0; i--)
		{
		    uchar * ptr_mat = colorImgRoi_line.ptr(colorImgRoi.rows - 50);
		    if(ptr_mat[i] > 0)
		    {
		        ptr_mat[i] = 255;
		        cout << "find l:" << i / 3 << endl;
		        cout << "diff l:" << banishP.x - (i / 3) << endl;
		        Lline = banishP.x - (i / 3);
		        cv::line(colorImgRoi_line, Point(i/3, 0), Point(i/3, colorImgRoi_line.rows), Scalar(255,0,0), 1);

		        break;
		    }
		}
		
		for (int i = banishP.x * 3; i < colorImgRoi.cols*3; i++)
		{
		    uchar * ptr_mat = colorImgRoi_line.ptr(colorImgRoi.rows - 50);
		    if(ptr_mat[i] > 0)
		    {
		        ptr_mat[i] = 255;
		        cout << "find r:" << i / 3 << endl;
		        cout << "diff r" << (i / 3) - banishP.x << endl;
		        Rline = (i / 3) - banishP.x;
		        cv::line(colorImgRoi_line, Point(i/3, 0), Point(i/3, colorImgRoi_line.rows), Scalar(255,0,0), 1);
		        break;
		    }
		}

		cout << "diff (- L, + R)" << Rline - Lline << endl;


		imshow("gray", grayImg);
		imshow("roi", imageROI);
		imshow("canny", cannyImg);
		imshow("color", colorImg);
		imshow("colorroi", colorImgRoi);
		imshow("line", colorImgRoi_line);

		if (waitKey(25) >= 0)
			break;
	}
	
	return 0;
}

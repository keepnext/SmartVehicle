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
        
		Mat image = img_color.clone();

		Mat image_ch[3];
		split(image, image_ch);
		Mat red_find;
		threshold(image_ch[2], red_find, 200, 255, THRESH_BINARY);
	
		Mat result = Mat::zeros(red_find.rows, red_find.cols, CV_8UC3);

		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;

		findContours( red_find, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );

		for (int i = 0; i< contours.size(); i++)
		{
		    Scalar box(  0, 0, 255 );
		    Scalar line(  255, 0, 0 );
		    //drawContours( result, contours, i, line);

			RotatedRect rrect = minAreaRect(contours[i]);
			Rect boundingrect = rrect.boundingRect();
			//cout << contours[i] << endl;
			//cout << contourArea(contours[i]) << endl;
			//cout << boundingrect.width << endl;
			
			if(boundingrect.width * 0.9 <= boundingrect.height
			   && boundingrect.width * 1.1 >= boundingrect.height)
			{
				if(boundingrect.width > 100 && boundingrect.width < 200)
				{
					rectangle(result, boundingrect, box);
				}
			}
		}

		//cout << contours.size() << endl;

		imshow("Color", img_color);
		imshow("image", red_find);
		imshow("Result", result);

		if (waitKey(25) >= 0)
			break;
	}
	
	return 0;
}

#include <opencv2/opencv.hpp>

#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main()
{
     Mat cam_data;  // 카메라에서 받아온 영상 저장     
     VideoCapture cap(0); // 웹캡 연결 (video0)
     // 1fps로 설정     
     double fps = cap.set(CV_CAP_PROP_FPS, 1);
     cout << "fps :" << fps << endl;     
     if(!cap.isOpened()) {
         cerr << "error conn fail" << endl;
	 return -1;
     }
     while(1)
     {
         cap.read(cam_data);
         if(cam_data.empty()) {
            cerr << "cam_data empty" << endl;
            break;
         }

         Mat imgproc = cam_data.clone();
         Mat imgsplit[3]; // RGB -> C1 R, G, B
         
         split(imgproc, imgsplit); B(0), G(1), R(2)

         Mat red_find_res;
         threshold(imgsplit[2], red_find_res,
                   200, 255, THRESH_BINARY);

        Mat green_find_res;
        threshold(imgsplit[1], green_find_res,
                  200, 255, THRESH_BINARY);
        Mat blue_find_res;
         threshold(imgsplit[0], blue_find_res,
                   200, 255, THRESH_BINARY);

         Mat last_find_res;
         last_find_res = red_find_res - green_find_res -                           blue_find_res;

		 Mat element = getStructuringElement(MORPH_RECT,
			 Size(ele_size * 2 + 1, ele_size * 2 + 1),
			 Point(1, 1)
		 );

		 Mat erode_res, dil_res;

		 erode(red_find_res, erode_res, element);
		 dilate(red_find_res, dil_res, element);

		 imshow("erd",erode_res);
		 imshow("dil", dil_res); 

		 int ele_size = 1;

		 Mat erode_res, dil_res;


         imshow("cam", cam_data);
         imshow("th_r_200", red_find_res);

         imshow("r", imgsplit[2]);
         imshow("g", imgsplit[1]);
         imshow("b", imgsplit[0]);

         imshow("last", last_find_res);

         if(waitKey(25) >= 0)
         {
             break;
         }
     }
     return 0;
}



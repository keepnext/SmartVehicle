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
         imshow("cam", cam_data);         
         if(waitKey(25) >= 0)
         {
             break;
         }
     }
     return 0;
}

g++ -o cam cam_test.cpp $(pkg-config --libs --cflags opencv)
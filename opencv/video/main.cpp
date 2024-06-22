#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(void)
{
	VideoCapture video("moon.mp4");

	if(video.isOpened())
	{
		cout << "width: " << video.get(CAP_PROP_FRAME_WIDTH) << endl;
		cout << "height: " << video.get(CAP_PROP_FRAME_HEIGHT) << endl;
		cout << "FPS: " << video.get(CAP_PROP_FPS) << endl;
		cout << "fps count: "<< video.get(CAP_PROP_FRAME_COUNT) << endl;
	}

	else
	{
		cout << " error! " << endl;
		return -1;
	}

	while(1)
	{
		Mat frame;
		video >> frame;
		if(frame.empty())
		{
			break;
		}
		imshow("video",frame);
		waitKey(1000 / video.get(CAP_PROP_FPS));

		if (cv::waitKey(30) >= 0){ // 按下任意键退出循环
                 break;}
	}
        video.release();
	return 0;
}


#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
using namespace std;
int main(void)
{
    Mat image = imread("cc.jpg");
    if (image.empty())
    {
        cout<<"No image data \n";
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    waitKey(0);
    return 0;
}

#include <opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main(void)
{
    Mat img = Mat::zeros(Size(768,768),CV_8UC3);//huabu
    Mat cc = imread("cc.jpg");
    if(cc.empty())
    {
        cout << "error!" << endl;
        return -1;
    }

    circle(img,Point(50,50),50,Scalar(255,255,255),-1);//full
    circle(img,Point(160,50),50,Scalar(255,255,255),3);//none

    line(img,Point(50,300),Point(50,400),Scalar(255,255,255),2,LINE_4,0);

    ellipse(img,Point(100,350),Size(100,70),0,0,100,Scalar(255,255,255),-1);

    rectangle(img,Point(50,450),Point(100,500),Scalar(255,255,255),-1);

    //Rect(left top point ,lenth,width)
    rectangle(img,Rect(50,520,100,100),Scalar(255,255,255),2);

    //putText(src,string,left down,font category,font size)
    putText(img,"i miss u",Point(200,600),2,1,Scalar(255,255,255));
    imshow("img",img);
    waitKey(0);
    return 0;
}

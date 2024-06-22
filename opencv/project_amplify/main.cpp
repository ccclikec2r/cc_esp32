#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main(void)
{
	
	Mat cc = imread("op.jpg",IMREAD_GRAYSCALE);
	if(cc.empty())
	{
		cout << " error load" << endl;
		return -1;
	}
	Mat big,small;

	//resize(src,dst,size,fx_fold,fy_fold,method)
	//method:INTER_(NEAREST,LINEAR,CUBIC,AREA...)
	resize(cc,big,Size(0,0),1.5,1.5,INTER_CUBIC);
	resize(cc,small,Size(0,0),0.5,0.5,INTER_CUBIC);

	imshow("cc",cc);
	imshow("big",big);
	imshow("small",small);

	Mat x,y,xy;

	//flip(src,dst,method)
	//method:> 0 is y,= 0 is x , <0 is both
	flip(cc,x,0);
	flip(cc,y,1);
	flip(cc,xy,-1);

	imshow("x",x);
	imshow("y",y);
	imshow("xy",xy);

	waitKey(0);
	return 0;
}

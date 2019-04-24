#include "pch.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("C:\\Users\\anton\\Downloads\\apple.jpg", 0); //Load picture

	//Mat newImg = Mat(img.rows, img.cols, CV_8UC1);

	double PI = 3.14159265;

	float cAng = 15; //Camera tilt relative to world plane in degrees

	float xFOV = 85.2;
	float yFOV = 58;

	float xRatio = xFOV / img.rows;//1920;
	float yRatio = yFOV / img.cols;//1080;


	float r = 40; //depth data
	int xPos = 800; //distance x direction to center pixel
	int yPos = 480; //distance y direction to center pixel

	int theta = xPos * xRatio;
	int phi = yPos * yRatio;

	float x = r * sin(theta*PI / 180)*cos(phi*PI / 180);
	float y = r * sin(theta*PI / 180)*sin(phi*PI / 180);
	float z = r * cos(theta*PI / 180);

	float EE[4][4] = { {1,0,0,x},{0,1,0,y},{0,0,1,z},{0,0,0,1} };
	float Cam[4][4] = {{cos(cAng*PI/180),0,sin(cAng*PI / 180),108.75}, {0,1,0,-77.7}, {-sin(cAng*PI / 180),0,cos(cAng*PI / 180),0}, {0,0,0,1} };
	float c2EE[4][4];


	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			c2EE[i][j] = 0;
		}

	// Multiplying matrix a and b and storing in array mult.
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 4; ++k)
			{
				c2EE[i][j] += Cam[i][k] * EE[k][j];
			}

	// Displaying the multiplication of two matrix.
	cout << endl << "Output Matrix: " << endl;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			cout << " " << c2EE[i][j];
			if (j == 4 - 1) {
				cout << endl;
			}
				
		}

	

	Mat obj = Mat(x,y,z);

	//Mat CamEE = Mat();


	waitKey(0);

	return 0;
}
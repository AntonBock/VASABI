#include "pch.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

vector <float> calculatePosition()
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

	float x = r * sin(theta * PI / 180) * cos(phi * PI / 180);
	float y = r * sin(theta * PI / 180) * sin(phi * PI / 180);
	float z = r * cos(theta * PI / 180);

	float Cam2Obj[4][4] = { {1,0,0,x},{0,1,0,y},{0,0,1,z},{0,0,0,1} };
	float Ee2Cam[4][4] = { {0,0.2588,0.9659,108.75},{1,0,0,0},{0,0.9659,-0.2588,-77.7},{0,0,0,1} };
	float Ee2Obj[4][4];


	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			Ee2Obj[i][j] = 0;
		}


	// Multiplying matrix a and b and storing in array mult.
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 4; ++k)
			{
				Ee2Obj[i][j] += Ee2Cam[i][k] * Cam2Obj[k][j];
			}

	// Displaying the multiplication of two matrix.
	cout << endl << "Output Matrix: " << endl;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			cout << " " << Ee2Obj[i][j];
			if (j == 4 - 1) {
				cout << endl;
			}
		}

	vector <float> Object;

	Object.clear();
	Object.push_back(Ee2Obj[0][3]);
	Object.push_back(Ee2Obj[1][3]);
	Object.push_back(Ee2Obj[2][3]);

	waitKey(0);

	return Object;
}



int main()
{
	vector <float> test;

	test = calculatePosition();

	return 0;
}
